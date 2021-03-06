#ifndef ChatServer_H
#define ChatServer_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QVector>
#include <QMap>


using std::string;

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);

    enum CommandType {Set = 1, Change, CloseMain, Validate,
                      Request, Message, OpenPmWindow, PM, ClosePmWindow};

    void doCommand(const QString &message);
    void mainMessage(const QString &message);
    void validateNickname(const QString &message);
    void nicknameSet(const QString &message);
    void nicknameChanged(const QString &message);
    void closeWindow();
    void requestList(const QString &nickName);
    void prepareToWrite();
    void write(QTcpSocket *socket, const QString &text);
    void privateWindow(const QString &text);
    void sendPM(const QString &text);
    void closePrivateWindow(const QString &text);

    bool checkValidUser();
    bool checkUserToRemove();
    bool checkForExisting(const QString &text);   

    void initCommands();
public slots:
    void newConnection();    
    void read();
    void remove();

private:
    QTcpServer *server;    
    QString m_message;    
    QString toBeWritten;

    QVector<QTcpSocket*> clientList;
    QMap<quint16, QString> nicknameMap;
    QMap<int, QString> commandsMap;

    quint16 m_descriptor;    
    bool broadcast;
};

#endif // ChatServer_H
