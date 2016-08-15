#-------------------------------------------------
#
# Project created by QtCreator 2016-08-04T10:51:50
#
#-------------------------------------------------

QT       += core gui  network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = M5Server
TEMPLATE = app


win32{
OS=windows
MODULE=src/module_windows
}
unix{
OS=linux
MODULE=src/module_linux
}



DESTDIR = $$PWD/../../bin/server_w
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/obj
UI_DIR = $$PWD/obj/ui_header

QMAKE_CFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-parameter


INCLUDEPATH +=global \
                            ../common\

SOURCES += main.cpp\
    ../common/Common.cpp \
        widget.cpp \
    global/GLOBAL.cpp \
    CListenClient.cpp \
    CSqlServer.cpp

HEADERS  += widget.h \
   ../common/Common.h \
    global/GLOBAL.h \
    CListenClient.h \
    CSqlServer.h

FORMS    += widget.ui
