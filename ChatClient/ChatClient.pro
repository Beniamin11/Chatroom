TEMPLATE = app

QT += qml quick widgets

SOURCES += \
    src/pmModel.cpp \
    main.cpp \
    src/encrypt.cpp \
    src/chatSupervisor.cpp \
    src/usersModel.cpp \
    src/contentModel.cpp \
    src/lzw.cpp

HEADERS += \
    head/pmModel.h \
    head/encrypt.h \
    head/chatSupervisor.h \
    head/contentModel.h \
    head/usersModel.h \
    head/lzw.h

RESOURCES += qml.qrc \

# Additional import path used to resolve QML modules in Qt Creator's code model

win32:INCLUDEPATH += ./head

DISTFILES += res/*.qml \
    main.qml \

# Default rules for deployment.
# include(deployment.pri)

