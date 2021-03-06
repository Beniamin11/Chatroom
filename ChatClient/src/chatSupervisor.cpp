#include "../head/chatSupervisor.h"
#include <QDebug>
#include <QFile>

ChatSupervisor::ChatSupervisor( QObject *parent)
    :QObject(parent)
    ,m_conversation("")
    ,m_historyConv("")
    ,m_nickname("")
    ,m_popupTitle("Set Nickname")
    ,m_otherUser("")
    ,m_IP("")
    ,m_port(0)
    ,m_self(false)
    ,m_pmSelf(false)    
    ,m_userChange(false)
    ,m_clientReconnect(false)
    ,m_clientConnected(false)

{
    initCommands();

    m_contentModel = new contentModel(this);
    m_usersModel = new usersModel(this);
}

void ChatSupervisor::clientConnect(const QString &IP_address, const QString &port)
{
    m_IP = IP_address;
    m_port = port.toInt();
    connectToServer();
}

void ChatSupervisor::reconnect()
{
    m_clientReconnect = true;
    connectToServer();
}

void ChatSupervisor::connectToServer()
{
    socket = new QTcpSocket(this);    

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected() ));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()) );

    socket->connectToHost(m_IP, m_port);
    qDebug() <<"Connecting...";
}

void ChatSupervisor::socketConnected()
{
    qDebug() << "Connected!";

    m_clientConnected = true;
    emit connectedChanged();

    if(m_nickname == "")
        emit windowChanged(1);
    else
    {
        m_usersModel->clear();
        m_userChange = false;
        sendCommand(CommandType::Validate, m_nickname);
        m_nickname = "";        
    }
}

void ChatSupervisor::socketDisconnected()
{
    qDebug() << "Disconecting...";
    m_clientConnected = false;
    emit windowChanged(3);
}

void ChatSupervisor::socketError()
{
    qDebug() << "Error: "<< socket->errorString();

    m_clientReconnect = false;
    emit connectedChanged();
}

void ChatSupervisor::sendCommand(CommandType code, const QString &text)
{
    QString com = m_commandsMap[code] + '\n' + text;
    QString encr = encryptMessage(com);

    socket->write(encr.toStdString().c_str());
    qDebug() << "send command: " << com << " |enc: " << encr;
}

void ChatSupervisor::readyRead()
{       
    QByteArray message_read;
    while(!socket->atEnd())
        message_read = message_read + socket->read(100);

    QString temp(message_read);
    QString decrMessage = decryptMessage(temp);
    doCommand(decrMessage);

}

void ChatSupervisor::doCommand(const QString &text)
{
    QString commandCode = text.mid(0,6);
    int code = m_commandsMap.key(commandCode);

    switch(code)
    {
        case CommandType::Message: mainMessage(text); break;

        case CommandType::Set: nSet(text); break;

        case CommandType::Change: nChange(text); break;

        case CommandType::CloseMain: closeWindow(text); break;

        case CommandType::Validate: nicknameValidate(text); break;

        case CommandType::Request: requestList(text); break;

        case CommandType::OpenPmWindow: privateWindow(text); break;

        case CommandType::PM: sendPM(text); break;

        case CommandType::ClosePmWindow: closePrivateW(text); break;
    }
}

void ChatSupervisor::mainMessage(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString message = "<" + tempMessage[1] + "> " + tempMessage[2];
    for(int i = 3; i < tempMessage.length(); i++)
        message = message + '\n' + tempMessage[i];

    m_self = (tempMessage[1].compare(m_nickname) == 0);
    m_contentModel->addProperties(m_self, false);

    appendText(message);
}

void ChatSupervisor::nicknameValidate(const QString &text)
{
    QStringList tempMessage = text.split('\n');

    QString valid = tempMessage[1];
    QString nickname = tempMessage[2];

    if(valid == "OK")
    {
        qDebug() <<"valid nickname!";

        setNickname(nickname);
        emit windowChanged(2);

        if(m_userChange)
            sendCommand(CommandType::Change, nickname);
        else
        {
            sendCommand(CommandType::Set, nickname);
            if(!m_clientReconnect)
            {
                m_usersModel->clear();
            }
        }
    }
    else
    {
        m_popupTitle = "Nickname taken.Choose another";
        emit popupTitleChanged();
        emit windowChanged(1);
        qDebug() << "invalid nickname!";
    }
}

void ChatSupervisor::nSet(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString nickname = tempMessage[1];

    m_contentModel->addProperties(false, true);
    appendText("*" + nickname + " has joined the chat");
    m_usersModel->append(nickname);

    if(m_nickname == nickname)
        sendCommand(CommandType::Request, m_nickname);
}

void ChatSupervisor::nChange(const QString &text)
{
    QStringList tempMessage = text.split('\n');

    QString nickname = tempMessage[1];
    QString oldNickname = tempMessage[2];

    m_usersModel->remove(oldNickname);
    if(m_nickname.compare(nickname) == 0)
        m_usersModel->addOnTop(nickname);
    else
        m_usersModel->append(nickname);
    m_contentModel->addProperties(false, true);
    appendText("*" + oldNickname + " is now " + nickname);

    auto pos = m_currentPmList.find(oldNickname);
    if(pos != m_currentPmList.end())
    {
        pmModel* temp = m_currentPmList[oldNickname];
        m_currentPmList.erase(pos);
        m_currentPmList.insert(nickname, temp);
        m_otherUser = nickname;
        emit otherUserChanged(oldNickname);
    }
}

void ChatSupervisor::closeWindow(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString nickname = tempMessage[1];

    m_contentModel->addProperties(false, true);
    appendText("*" + nickname + " has left the room");
    m_usersModel->remove(nickname);   

    emit mainWindowClosed();
}

void ChatSupervisor::requestList(const QString &list)
{
    QStringList nicknameList = list.split('\n');

    for(quint16 i = 1; i < nicknameList.size(); ++i)
    {
        m_usersModel->append(nicknameList[i]);
    }
}

void ChatSupervisor::sendPM(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString sender = tempMessage[1];
    QString receiver = tempMessage[2];

    if( !openPmWindow(receiver) )
        m_pmSelf = (sender.compare(receiver) != 0);

    while(QRegExp("\\s*").exactMatch(tempMessage.back()))
        tempMessage.pop_back();

    QString message = tempMessage[3];
    for(int i = 4; i < tempMessage.length(); ++i)
    {        
        message = message + '\n' + tempMessage[i];
    }

    pmModel* temp = m_currentPmList[receiver];
    temp->addProperties(m_pmSelf);
    temp->append(message);    
}

void ChatSupervisor::privateWindow(const QString &text)
{
    QStringList temp = text.split('\n');
    QString key = temp[1];
    if( !openPmWindow(key) )
        emit focusPmWindow(key);
}

void ChatSupervisor::closePrivateW(const QString &text)
{
    QStringList temp = text.split('\n');
    QString otherUser = temp[1];

    auto pos = m_currentPmList.find(otherUser);
    if(pos != m_currentPmList.end())
    {
        m_closedPmList.insert(otherUser, m_currentPmList[otherUser]);
        m_currentPmList.erase(pos);
    }
}

bool ChatSupervisor::openPmWindow(const QString &key)
{
    auto pos = m_currentPmList.find(key);
    if(pos == m_currentPmList.end())
    {
        auto c_pos = m_closedPmList.find(key);
        if(c_pos == m_closedPmList.end())
        {
            pmModel* tempPM = new pmModel(this);
            m_currentPmList.insert(key, tempPM);
            emit openPrivateWindow(key);
        }
        else
        {
            m_currentPmList.insert(key, m_closedPmList[key]);
            m_closedPmList.erase(c_pos);
            emit openPrivateWindow(key);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void ChatSupervisor::appendText(const QString &text)
{
    QString currentTime = m_timestamp.currentTime().toString("hh:mm");
    QString message = breakText(text);
    m_conversation = m_conversation + currentTime + " " + text + "\n";

    if(message.contains('\n'))
    {
        QStringList temp = message.split('\n');        

        while(QRegExp("\\s*").exactMatch(temp.back()))
        {
            temp.pop_back();
        }
        m_contentModel->append(temp[0], "[" + currentTime + "]");

        for(int i = 1; i < temp.length(); i++)
        {
            m_contentModel->addProperties(m_self, false);
            m_contentModel->append(temp[i], "");
        }
    }
    else
    {
        m_contentModel->append(message, "[" + currentTime + "]" );
    }
}

QString ChatSupervisor::breakText(QString text)
{
    QFont myFont("TimesNewRoman", 13);
    QFontMetrics fm(myFont);
    int textWidth;

    textWidth = fm.width(text);
    qDebug() << "(before)  :"<< text;
    if(textWidth > m_textLength)
    {
        QString tempText;
        for(int j = 0; j < text.length(); j++)
        {
            if(text[j] == '\n')
                tempText = "";
            else
            {
                tempText = tempText + text.at(j);
                textWidth = fm.width(tempText);
                if(textWidth > m_textLength)
                {
                    text.insert(j, '\n');
                    tempText = "";
                }
            }
        }
    }
    qDebug() << "(after)   :"<< text;
    return text;
}

QObject *ChatSupervisor::getModel(const QString &otherUser)
{    
    return m_currentPmList[otherUser];
}

void ChatSupervisor::saveDataOnClosing()
{
    qDebug() << "Closing....";
    QString filename = "CompressedData.txt";
    QFile file (filename);
    if( file.open(QIODevice::WriteOnly))
    {
        QTextStream stream (&file);
        QString compressedData = compress(m_conversation);
        stream << compressedData;
    }
}

void ChatSupervisor::readSavedData()
{
    QFile file("compressedData.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error reading file!";
    }

    QTextStream stream (&file);
    QString data = stream.readAll();
    m_historyConv = decompress(data);
    qDebug() << m_historyConv;
    emit convHistoryChanged();
}

void ChatSupervisor::setNickname(const QString &nickname)
{
    qDebug() << "nickname changed: " << nickname;
    m_nickname = nickname;
    emit nicknameChanged();
}

void ChatSupervisor::setChangingUser(bool state)
{
    m_userChange = state;
    emit changingUserChanged();
}

void ChatSupervisor::setTextLength(int len)
{
    m_textLength = len;
    emit textLengthChanged();
}

void ChatSupervisor::setPopupTitle(const QString &title)
{
    m_popupTitle = title;    
}

void ChatSupervisor::setOtherUser(const QString &user)
{
    m_otherUser = user;
}

void ChatSupervisor::initCommands()
{
    m_commandsMap.insert(CommandType::Set, "$?s&*!");
    m_commandsMap.insert(CommandType::Change, "$%ch*#");
    m_commandsMap.insert(CommandType::Message, "$*me%#");
    m_commandsMap.insert(CommandType::CloseMain, "$^cl#*");
    m_commandsMap.insert(CommandType::OpenPmWindow, "$%op!^");
    m_commandsMap.insert(CommandType::ClosePmWindow, "$&cw)!");
    m_commandsMap.insert(CommandType::Validate, "$#va(*");
    m_commandsMap.insert(CommandType::Request, "$^re@&");
    m_commandsMap.insert(CommandType::PM, "$#pm%*");
}

QString ChatSupervisor::nickname() { return m_nickname; }

QString ChatSupervisor::otherUser() { return m_otherUser; }

QString ChatSupervisor::convHistory() { return m_historyConv; }

QString ChatSupervisor::popupTitle() { return m_popupTitle; }

bool ChatSupervisor::changingUser() { return m_userChange; }

bool ChatSupervisor::connected() { return m_clientConnected; }

bool ChatSupervisor::pmSelf() { return m_pmSelf; }

int ChatSupervisor::textLength() { return m_textLength; }

QObject *ChatSupervisor::content() { return m_contentModel; }

QObject *ChatSupervisor::users() { return m_usersModel; }
