#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QDateTime>

#include "pmmodel.h"
#include "contentModel.h"
#include "usersModel.h"


class messageHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* content READ content NOTIFY contentChanged)
    Q_PROPERTY(QObject* users READ users NOTIFY usersChanged)


public:
    explicit messageHandler(QObject *parent = 0);

    Q_INVOKABLE QObject* getModel(const QString &otherUser);


    //get
    QObject* content();
    QObject* users();


    bool checkForCommand(const QString &text);
    void parseMessage(const QString &message);
    void doCommand(const QString& text);
    void nSet(const QString &text);
    void nChange(const QString &text);
    void nicknameValidate(const QString &text);
    void closeWindow(const QString &text);
    void requestList(const QString &list);
    void sendPM(const QString& text);
    void privateWindow(const QString &text);
    void closePrivateW(const QString &text);
    void appendText(const QString &text);

signals:
    void windowChanged(int window);
    void popupTitleChanged();
    void otherUserChanged(QString otherUser);
    void mainWindowClosed();
    void openPrivateWindow(QString otherUser);
    void focusPmWindow(QString otherUser);
    void setNickname(QString nickname);

public slots:


private:
    QTime m_timestamp;
    QMap<QString, pmModel*> m_pmList;

    usersModel *m_usersModel;
    contentModel *m_contentModel;

    bool m_self;
    bool m_pmSelf;
    bool m_userChange;
    bool m_clientReconnect;

    QString m_otherUser;

};

#endif // MESSAGEHANDLER_H
