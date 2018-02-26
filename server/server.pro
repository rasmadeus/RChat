TEMPLATE = app

DESTDIR = ../../bin

QT += widgets

CONFIG += c++14
CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

include(../boost.pri)

HEADERS += \
    pch.h \
    server.h \
    session.h \
    main_view.h \
    room.h \
    message.h

SOURCES += \
    main.cpp \
    server.cpp \
    session.cpp \
    main_view.cpp \
    room.cpp \
    message.cpp

FORMS += \
    main_view.ui
