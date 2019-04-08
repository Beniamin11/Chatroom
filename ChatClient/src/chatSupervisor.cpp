#include "../head/chatSupervisor.h"
#include <QDebug>


ChatMainWindow::ChatMainWindow( QObject *parent)
    :QObject(parent)
    ,m_popupTitle("Set Nickname")    
    ,m_otherUser("")
    ,m_nickname("")
    ,m_IP("")
    ,m_port(0)
    ,m_clientConnected(false)
    ,m_clientReconnect(false)
    ,m_userChange(false)
    ,m_pmSelf(false)
    ,m_self(false)
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

    m_contentModel = new contentModel(this);
    m_usersModel = new usersModel(this);
}

void ChatMainWindow::clientConnect(const QString &IP_address, const QString &port)
{
    m_IP = IP_address;
    m_port = port.toInt();
    connectToServer();
}

void ChatMainWindow::reconnect()
{
    m_clientReconnect = true;
    connectToServer();
}

void ChatMainWindow::connectToServer()
{
    socket = new QTcpSocket(this);    

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()) );
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected() ));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()) );

    socket->connectToHost(m_IP, m_port);
    qDebug() <<"Connecting...";
}

void ChatMainWindow::socketConnected()
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

void ChatMainWindow::socketDisconnected()
{
    qDebug() << "Disconecting...";
    m_clientConnected = false;
    emit windowChanged(3);
}

void ChatMainWindow::socketError()
{
    qDebug() << "Error: "<< socket->errorString();

    m_clientReconnect = false;
    emit connectedChanged();
}

void ChatMainWindow::sendCommand(CommandType code, const QString &text)
{
    QString com = m_commandsMap[code] + '\n' + text;
    QString encr = encryptMessage(com, m_descriptor);

    socket->write(encr.toStdString().c_str());
    qDebug() << "send command: " << com << " |enc: " << encr;
}

void ChatMainWindow::readyRead()
{       
    QByteArray message_read;
    while(!socket->atEnd())
        message_read = message_read + socket->read(100);

    QString temp(message_read);
    QString decrMessage = decryptMessage(temp, m_descriptor);
    doCommand(decrMessage);

}

void ChatMainWindow::doCommand(const QString &text)
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

void ChatMainWindow::mainMessage(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString message = "<" + tempMessage[1] + "> " + tempMessage[2];
    for(int i = 3; i < tempMessage.length(); i++)
        message = message + '\n' + tempMessage[i];

    m_self = (tempMessage[1].compare(m_nickname) == 0);
    m_contentModel->addProperties(m_self, false);

    appendText(message);
}

void ChatMainWindow::nicknameValidate(const QString &text)
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

void ChatMainWindow::nSet(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString nickname = tempMessage[1];

    m_contentModel->addProperties(false, true);
    appendText("*" + nickname + " has joined the chat");
    m_usersModel->append(nickname);

    if(m_nickname == nickname)
        sendCommand(CommandType::Request, m_nickname);
}

void ChatMainWindow::nChange(const QString &text)
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

    auto pos = m_pmList.find(oldNickname);
    if(pos != m_pmList.end())
    {
        pmModel* temp = m_pmList[oldNickname];
        m_pmList.erase(pos);
        m_pmList.insert(nickname, temp);
        m_otherUser = nickname;
        emit otherUserChanged(oldNickname);
    }
}

void ChatMainWindow::closeWindow(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString nickname = tempMessage[1];

    m_contentModel->addProperties(false, true);
    appendText("*" + nickname + " has left the room");
    m_usersModel->remove(nickname);

    emit mainWindowClosed();
}

void ChatMainWindow::requestList(const QString &list)
{
    QStringList nicknameList = list.split('\n');

    for(quint16 i = 1; i < nicknameList.size(); ++i)
    {
        m_usersModel->append(nicknameList[i]);
    }
}

void ChatMainWindow::sendPM(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString sender = tempMessage[1];
    QString receiver = tempMessage[2];

    auto pos = m_pmList.find(receiver);
    if(pos == m_pmList.end())
    {
        pmModel* tempPM = new pmModel(this);
        m_pmList.insert(receiver, tempPM);
        emit openPrivateWindow(receiver);
    }
    else
        m_pmSelf = (sender.compare(receiver) != 0);

    while(QRegExp("\\s*").exactMatch(tempMessage.back()))
        tempMessage.pop_back();

    QString message = tempMessage[3];
    for(int i = 4; i < tempMessage.length(); ++i)
    {        
        message = message + '\n' + tempMessage[i];
    }

    pmModel* temp = m_pmList[receiver];
    temp->addProperties(m_pmSelf);
    temp->append(message);
}

void ChatMainWindow::privateWindow(const QString &text)
{
    QStringList temp = text.split('\n');
    QString key = temp[1];
    auto pos = m_pmList.find(key);
    if(pos == m_pmList.end())
    {
        pmModel* tempPM = new pmModel(this);
        m_pmList.insert(key, tempPM);
        emit openPrivateWindow(key);
    }
    else
    {
        emit focusPmWindow(key);
    }
}

void ChatMainWindow::closePrivateW(const QString &text)
{
    QStringList temp = text.split('\n');
    QString otherUser = temp[1];

    auto pos = m_pmList.find(otherUser);
    if(pos != m_pmList.end())
    {
        m_pmList.erase(pos);
    }
}

void ChatMainWindow::appendText(const QString &text)
{
    QString currentTime = m_timestamp.currentTime().toString("hh:mm");
    QString message = breakText(text);

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

QString ChatMainWindow::breakText(QString text)
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

QObject *ChatMainWindow::getModel(const QString &otherUser)
{
    qDebug() << "getModel("<<otherUser<<")"<< m_pmList[otherUser];
    return m_pmList[otherUser];
}

void ChatMainWindow::setNickname(const QString &nickname)
{
    qDebug() << "nickname changed: " << nickname;
    m_nickname = nickname;
    emit nicknameChanged();
}

void ChatMainWindow::setChangingUser(bool state)
{
    m_userChange = state;
    emit changingUserChanged();
}

void ChatMainWindow::setTextLength(int len)
{
    m_textLength = len;
    emit textLengthChanged();
}

void ChatMainWindow::setPopupTitle(const QString &title)
{
    m_popupTitle = title;    
}

void ChatMainWindow::setOtherUser(const QString &user)
{
    m_otherUser = user;
}

QString ChatMainWindow::nickname() { return m_nickname; }

QString ChatMainWindow::otherUser() { return m_otherUser; }

QString ChatMainWindow::popupTitle() { return m_popupTitle; }

bool ChatMainWindow::changingUser() { return m_userChange; }

bool ChatMainWindow::connected() { return m_clientConnected; }

bool ChatMainWindow::pmSelf() { return m_pmSelf; }

int ChatMainWindow::textLength() { return m_textLength; }

QObject *ChatMainWindow::content() { return m_contentModel; }

QObject *ChatMainWindow::users() { return m_usersModel; }
