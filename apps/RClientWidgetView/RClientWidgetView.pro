#-------------------------------------------------
#
# Project created by QtCreator 2015-01-17T21:29:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = RClientWidgetView
TEMPLATE = app


SOURCES += main.cpp\
        view.cpp

HEADERS  += view.h

FORMS    += view.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/rserver/release/ -lrserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/rserver/debug/ -lrserver
else:unix: LIBS += -L$$OUT_PWD/../../libs/rserver/ -lrserver

INCLUDEPATH += $$PWD/../../libs/rserver
DEPENDPATH += $$PWD/../../libs/rserver

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/rserver/release/librserver.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/rserver/debug/librserver.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/rserver/release/rserver.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/rserver/debug/rserver.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/rserver/librserver.a
