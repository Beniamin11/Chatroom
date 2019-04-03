#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>
#include <memory>

#include "chatSupervisor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChatMainWindow chat;
    QQmlApplicationEngine engine;

    qmlRegisterType<ChatMainWindow>("ChatWindow", 1, 0, "ChatWindow");

    engine.rootContext()->setContextProperty("cmw", &chat);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

