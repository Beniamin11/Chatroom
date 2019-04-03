#include "myserver.h"
#include "encrypt.h"

MyServer::MyServer(QObject *parent)
    :QObject(parent)    
    ,m_message("")
    ,m_descriptor(0)      
    ,broadcast(false)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()) );

    commandsMap.insert(CommandType::Set, "$?s&*!");
    commandsMap.insert(CommandType::Change, "$%ch*#");
    commandsMap.insert(CommandType::Message, "$*me%#");
    commandsMap.insert(CommandType::CloseMain, "$^cl#*");    
    commandsMap.insert(CommandType::ClosePmWindow, "$&cw)!");    
    commandsMap.insert(CommandType::OpenPmWindow, "$%op!^");
    commandsMap.insert(CommandType::Validate, "$#va(*");
    commandsMap.insert(CommandType::Request, "$^re@&");
    commandsMap.insert(CommandType::PM, "$#pm%*");

    if(!server->listen(QHostAddress("10.67.132.168"), 1234))
    {
        qDebug() << "Server could not start! ";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void MyServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    clientList.push_back(socket);

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()) );
    connect(socket, SIGNAL(disconnected()), this, SLOT(remove()) );
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));

    qDebug() << "User connected: " << socket->socketDescriptor();
}

void MyServer::read()
{
    QString incMessage;

    for(QTcpSocket* instance : clientList)
    {
        if(instance->bytesAvailable() > 0)
        {
            QByteArray read;
            while(!instance->atEnd())
                read = read + instance->read(100);
            QString temp(read);
            incMessage = temp;
            m_descriptor = instance->socketDescriptor();
        }
    }
    QString decrMessage = decryptMessage(incMessage);

    doCommand(decrMessage);
    prepareToWrite();
}

void MyServer::doCommand(const QString &message)
{
    QStringList temp = message.split('\n');
    QString commandCode = temp[0];
    int code = commandsMap.key(commandCode);

    switch(code)
    {
        case CommandType::Message: mainMessage(message); break;

        case CommandType::Set: nicknameSet(message); break;

        case CommandType::Change: nicknameChanged(message); break;

        case CommandType::CloseMain: closeWindow(); break;

        case CommandType::Validate: validateNickname(message); break;

        case CommandType::Request: requestList(message); break;

        case CommandType::OpenPmWindow: privateWindow(message); break;

        case CommandType::PM: sendPM(message); break;

        case CommandType::ClosePmWindow: closePrivateWindow(message); break;
    }
}

void MyServer::mainMessage(const QString &message)
{
    broadcast = true;
    m_message = message;
}

void MyServer::validateNickname(const QString &message)
{
     QStringList temp = message.split('\n');
     QString nickname = temp[1].simplified();
     bool alreadyExists = checkForExisting(nickname);
     if(alreadyExists)
         m_message = commandsMap[CommandType::Validate] + '\n' + "NO" + '\n' + nickname;
     else             
         m_message = commandsMap[CommandType::Validate] + '\n' + "OK" + '\n' + nickname;

     broadcast = false;
}

void MyServer::nicknameSet(const QString &message)
{
    QStringList temp = message.split('\n');
    QString nickname = temp[1].simplified();
    m_message = commandsMap[CommandType::Set] + '\n' + nickname;
    broadcast = true;
    nicknameMap.insert(m_descriptor, nickname);
}

void MyServer::nicknameChanged(const QString &message)
{
    QStringList temp = message.split('\n');
    QString nickname = temp[1];
    QString oldNickname = nicknameMap[m_descriptor];

    m_message = commandsMap[CommandType::Change] + '\n' + nickname + '\n' + oldNickname;
    broadcast = true;

    auto pos = nicknameMap.find(m_descriptor);
    nicknameMap.erase(pos);
    nicknameMap.insert(m_descriptor, nickname);
}

bool MyServer::checkForExisting(const QString &nickname)
{
    for(auto existingN : nicknameMap)
    {
        if(nickname.compare(existingN) == 0)
        {
            return true;
        }
    }
    return false;
}

void MyServer::closeWindow()
{
    m_message = "";
    broadcast = false;
}

void MyServer::requestList(const QString &message)
{
    QStringList temp = message.split('\n');
    QString nickName = temp[1];
    m_message = commandsMap[CommandType::Request];
    for(auto n : nicknameMap)
        if(nickName.compare(n) != 0)
            m_message = m_message + '\n' + n;
    broadcast = false;
}

void MyServer::privateWindow(const QString &text)
{
    QStringList tempM = text.split('\n');
    QString otherUser = tempM[1];
    broadcast = false;
    m_message = commandsMap[CommandType::OpenPmWindow] + '\n' + otherUser;
}

void MyServer::sendPM(const QString &text)
{
    QStringList tempM = text.split('\n');
    QString otherUser = tempM[1];

    m_message = commandsMap[CommandType::PM] + '\n' + nicknameMap[m_descriptor] + '\n' + nicknameMap[m_descriptor];
    for(int i = 2; i < tempM.length(); ++i)
        m_message = m_message + '\n' + tempM[i];

    quint16 descriptor = nicknameMap.key(otherUser);
    for(QTcpSocket* instance : clientList)
        if(descriptor == instance->socketDescriptor())
        {
            write(instance, m_message);
        }
    m_message = commandsMap[CommandType::PM] +  '\n' + nicknameMap[m_descriptor] + '\n' + otherUser;
    for(int i = 2; i < tempM.length(); ++i)
        m_message = m_message + '\n' + tempM[i];
    broadcast = false;
}

void MyServer::closePrivateWindow(const QString &text)
{
    QStringList tempM = text.split('\n');
    QString otherUser = tempM[1];

    m_message = commandsMap[CommandType::ClosePmWindow] + '\n' + otherUser;
    broadcast = false;
}

bool MyServer::checkValidUser()
{
    for(auto user : nicknameMap)
    {
        if(nicknameMap.key(user) == m_descriptor)
            return true;
    }
    return false;
}

void MyServer::prepareToWrite()
{
    if(!broadcast)
    {
        for(QTcpSocket* instance : clientList)
        {
            if(instance->socketDescriptor() == m_descriptor)
            {                
                write(instance, m_message);                
            }
        }
    }
    else
    {
        for(QTcpSocket* instance : clientList)
        {            
            write(instance, m_message);
        }
    }
}

void MyServer::write(QTcpSocket* socket, const QString &text)
{    
    QString toSend = encryptMessage(text);
    socket->write(toSend.toStdString().c_str());
}

void MyServer::remove()
{
    auto it = clientList.begin();
    for(QTcpSocket* instance : clientList)
    {
        if(instance->state() == QAbstractSocket::UnconnectedState)                   
            break;
        ++it;
    }
    clientList.erase(it);

    if(clientList.isEmpty())
        nicknameMap.clear();
    else
    {
        QVector<quint16> currentSockets;
        for(QTcpSocket* instance : clientList)
            currentSockets.push_back(instance->socketDescriptor());

        auto pos = nicknameMap.begin();        

        for(QString user : nicknameMap)
        {
            if(!currentSockets.contains(nicknameMap.key(user)))
            {
                m_message = commandsMap[CommandType::CloseMain] + '\n' + user;
                broadcast = true;
                break;
            }
            pos++;
        }
        if(pos != nicknameMap.end())
            nicknameMap.erase(pos);
        prepareToWrite();
    }

}
