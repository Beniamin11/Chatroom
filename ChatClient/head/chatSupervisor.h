#ifndef ChatSupervisor_H
#define ChatSupervisor_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QDateTime>
#include <QFontMetrics>
#include <memory>

#include "pmModel.h"
#include "contentModel.h"
#include "usersModel.h"
#include "encrypt.h"
#include "lzw.h"

class ChatSupervisor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString popupTitle READ popupTitle WRITE setPopupTitle NOTIFY popupTitleChanged)
    Q_PROPERTY(QString otherUser READ otherUser WRITE setOtherUser NOTIFY otherUserChanged)
    Q_PROPERTY(QString convHistory READ convHistory NOTIFY convHistoryChanged)

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool changingUser READ changingUser WRITE setChangingUser NOTIFY changingUserChanged)
    Q_PROPERTY(bool pmSelf  READ pmSelf  NOTIFY pmSelfChanged)
    Q_PROPERTY(int textLength READ textLength WRITE setTextLength NOTIFY textLengthChanged)

    Q_PROPERTY(QObject* content READ content NOTIFY contentChanged)
    Q_PROPERTY(QObject* users READ users NOTIFY usersChanged)

public:
    explicit ChatSupervisor(QObject* parent = nullptr);

    enum CommandType {Set, Change, CloseMain, Validate, Request, OpenPmWindow, PM, ClosePmWindow, Message};
    Q_ENUMS(CommandType)

    Q_INVOKABLE void clientConnect(const QString &IP_address, const QString &port);
    Q_INVOKABLE void reconnect();
    Q_INVOKABLE QObject* getModel(const QString &otherUser);
    Q_INVOKABLE void saveDataOnClosing();
    Q_INVOKABLE void readSavedData();

    //get
    QObject* content();
    QObject* users();

    QString popupTitle();
    QString nickname();
    QString otherUser();
    QString convHistory();

    bool changingUser();
    bool connected();
    bool pmSelf();
    int textLength();

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
    bool openPmWindow(const QString &key);

    void connectToServer();
    void initCommands();

    QString breakText(QString text);

public slots:
    void setNickname(const QString &nickname);
    void setChangingUser(bool state);
    void setTextLength(int len);
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
    void convHistoryChanged();
    void otherUserChanged(QString other);

    void openPrivateWindow(QString other);
    void focusPmWindow(QString other);
    void pmSelfChanged(QString other);
    void windowChanged(int wind);
    void mainWindowClosed();
    void contentChanged();
    void usersChanged();
    void connectedChanged();
    void textLengthChanged();

private:
    QTcpSocket *socket;

    QString m_conversation;
    QString m_historyConv;
    QString m_nickname;
    QString m_popupTitle;
    QString m_otherUser;
    QString m_IP;    

    QTime m_timestamp;

    QMap<int, QString> m_commandsMap;
    QMap<QString, pmModel*> m_currentPmList;
    QMap<QString, pmModel*> m_closedPmList;

    usersModel *m_usersModel;
    contentModel *m_contentModel;

    int m_port;
    int m_textLength;    

    bool m_self;
    bool m_pmSelf;
    bool m_userChange;
    bool m_clientReconnect;
    bool m_clientConnected;
};


#endif // ChatSupervisor_H
