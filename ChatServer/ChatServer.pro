#-------------------------------------------------
#
# Project created by QtCreator 2019-03-04T15:21:25
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = ChatServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    encrypt.cpp

HEADERS += \
    myserver.h \
    encrypt.h
