#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <qqml.h>
#include <memory>

#include "chatSupervisor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChatSupervisor chat;
    QQmlApplicationEngine engine;

    qmlRegisterType<ChatSupervisor>("ChatWindow", 1, 0, "ChatWindow");
    engine.rootContext()->setContextProperty("cmw", &chat);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.setWindowIcon(QIcon(":/res/icon.png"));

    return app.exec();
}

