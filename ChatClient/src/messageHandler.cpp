#include "../head/messageHandler.h"

messageHandler::messageHandler(QObject *parent) : QObject(parent)
{

}



void messageHandler::parseMessage(const QString &message)
{
    bool command = checkForCommand(message);

    if(command)
    {
        qDebug() << "Command read: "<<message;
        doCommand(message);
    }
    else
    {
        qDebug() << "Message read: "<<message;

        QString t_nickname = message.mid(1,m_nickname.length());
        m_self = (t_nickname.compare(m_nickname) == 0);

        m_contentModel->addProperties(m_self, false);
        appendText(message);
    }
}

bool messageHandler::checkForCommand(const QString &text)
{
    QString tempCom = text.mid(0,m_commandsMap[0].length());

    for(auto com : m_commandsMap)
    {
        if(tempCom.contains(com))
             return true;
    }
    return false;
}

void messageHandler::doCommand(const QString &text)
{
    QString commandCode = text.mid(0,6);
    int code = m_commandsMap.key(commandCode);

    switch(code)
    {
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

void messageHandler::nicknameValidate(const QString &text)
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

void messageHandler::nSet(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString nickname = tempMessage[1];

    m_contentModel->addProperties(false, true);
    appendText("*" + nickname + " has joined the chat");
    m_usersModel->append(nickname);

    if(m_nickname == nickname)
        sendCommand(CommandType::Request, m_nickname);
}

void messageHandler::nChange(const QString &text)
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
    appendText(" *" + oldNickname + " is now " + nickname);

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

void messageHandler::closeWindow(const QString &text)
{
    QStringList tempMessage = text.split('\n');
    QString nickname = tempMessage[1];

    m_contentModel->addProperties(false, true);
    appendText(" *" + nickname + " has left the room");
    m_usersModel->remove(nickname);

    emit mainWindowClosed();
}

void messageHandler::requestList(const QString &list)
{
    QStringList nicknameList = list.split('\n');

    for(quint16 i = 1; i < nicknameList.size(); ++i)
    {
        m_usersModel->append(nicknameList[i]);
    }
}

void messageHandler::sendPM(const QString &text)
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

    pmModel* temp = m_pmList[receiver];
    QString message = tempMessage[3];

    for(int i = 4; i < tempMessage.length(); ++i)
    {
        message = message + '\n' + tempMessage[i];
    }
    temp->addProperties(m_pmSelf);
    temp->append(message);
}

void messageHandler::privateWindow(const QString &text)
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

void messageHandler::closePrivateW(const QString &text)
{
    QStringList temp = text.split('\n');
    QString otherUser = temp[1];

    auto pos = m_pmList.find(otherUser);
    if(pos != m_pmList.end())
    {
        m_pmList.erase(pos);
    }
}





QObject *messageHandler::content() { return m_contentModel; }

QObject *messageHandler::users() { return m_usersModel; }
