TEMPLATE = app

DESTDIR = ../../bin

QT += widgets

CONFIG += console c++14
CONFIG -= app_bundle

CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

include(../boost.pri)

HEADERS += \
    pch.h \
    main_view.h \
    server.h \
    client.h \
    message.h

SOURCES += \
    main.cpp \
    main_view.cpp \
    server.cpp \
    client.cpp \
    message.cpp

FORMS += \
    main_view.ui
