#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T13:14:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = M5Client
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    CThread.cpp

HEADERS  += widget.h \
    CThread.h

FORMS    += widget.ui
