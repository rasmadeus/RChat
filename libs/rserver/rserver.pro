#-------------------------------------------------
#
# Project created by QtCreator 2015-01-10T22:14:45
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = rserver
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
SOURCES += \
    rserver.cpp \
    clientsmodel.cpp \
    clients.cpp \
    rclient.cpp

HEADERS += \
    rserver.h \
    clientsmodel.h \
    clients.h \
    rclient.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS +=
