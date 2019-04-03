#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QDateTime>

#include "pmmodel.h"
#include "ContentModel.h"
#include "UsersModel.h"
#include "encrypt.h"

class ChatMainWindow : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString popupTitle READ popupTitle WRITE setPopupTitle NOTIFY popupTitleChanged)
    Q_PROPERTY(QString otherUser READ otherUser WRITE setOtherUser NOTIFY otherUserChanged)

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool changingUser READ changingUser WRITE setChangingUser NOTIFY changingUserChanged)
    Q_PROPERTY(bool pmSelf  READ pmSelf  NOTIFY pmSelfChanged)

    Q_PROPERTY(QObject* content READ content NOTIFY contentChanged)
    Q_PROPERTY(QObject* users READ users NOTIFY usersChanged)

public:
    explicit ChatMainWindow(QObject* parent = 0);

    enum CommandType {Set, Change, CloseMain, Validate, Request, OpenPmWindow, PM, ClosePmWindow, Message};
    Q_ENUMS(CommandType)

    Q_INVOKABLE void clientConnect(const QString &IP_address, const QString &port);
    Q_INVOKABLE void reconnect();
    Q_INVOKABLE QObject* getModel(const QString &otherUser);

    //get
    QObject* content();
    QObject* users();

    QString popupTitle();
    QString nickname();
    QString otherUser();

    bool changingUser();
    bool connected();
    bool pmSelf();

    void doCommand(const QString& text);
    void mainMessage(const QString &text);
    void nSet(const QString &text);
    void nChange(const QString &text);
    void nicknameValidate(const QString &text);
    void closeWindow(const QString &text);
    void requestList(const QString &list);
    void sendPM(const QString& text);
    void privateWindow(const QString &text);
    void closePrivateW(const QString &text);
    void appendText(const QString &text);

    void connectToServer();

public slots:
    void setNickname(const QString &nickname);
    void setChangingUser(bool state);
    void setPopupTitle(const QString &title);
    void setOtherUser(const QString &user);

    void sendCommand(CommandType code, const QString &text);
    void readyRead();
    void socketDisconnected();
    void socketConnected();
    void socketError();

signals:
    void nicknameChanged();
    void changingUserChanged();
    void popupTitleChanged();
    void otherUserChanged(QString other);

    void openPrivateWindow(QString other);
    void focusPmWindow(QString other);
    void pmSelfChanged(QString other);
    void windowChanged(int wind);
    void mainWindowClosed();
    void contentChanged();
    void usersChanged();
    void connectedChanged();

private:
    QTcpSocket *socket;

    QString m_nickname;
    QString m_popupTitle;
    QString m_otherUser;
    QString m_IP;    

    QTime m_timestamp;

    QMap<int, QString> m_commandsMap;
    QMap<QString, pmModel*> m_pmList;

    usersModel *m_usersModel;
    contentModel *m_contentModel;

    int m_port;
    int m_descriptor;

    bool m_self;
    bool m_pmSelf;
    bool m_userChange;
    bool m_clientReconnect;
    bool m_clientConnected;
};


#endif // CHATMAINWINDOW_H
