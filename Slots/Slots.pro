#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T20:28:07
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Slots
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    slots.cpp \
    info.cpp

HEADERS  += mainwindow.h \
    slots.h \
    info.h

FORMS    += mainwindow.ui

RESOURCES += \
    source.qrc
