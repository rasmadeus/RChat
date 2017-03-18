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
    main_view.h

SOURCES += \
    main.cpp \
    main_view.cpp

FORMS += \
    main_view.ui
