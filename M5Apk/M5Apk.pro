#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T23:28:38
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

android: ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

BIN_OS=bin_apk


android: DESTDIR = $$PWD/../../bin/apk
DESTDIR = $$PWD/../../bin/apk
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/obj
UI_DIR = $$PWD/obj/ui_header

QMAKE_CFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-parameter

!include($$PWD/global/Global.pri ) {error(" Couldn't find the Global.pri file! ")}
TARGET = M5Apk
TEMPLATE = app

INCLUDEPATH +=$$PWD/option \
              $$PWD/product_list

SOURCES += main.cpp\
        widget.cpp \
#    StageFirst.cpp \
#    StageLogin.cpp \
#    StageStart.cpp \
#    LayerLoading.cpp
    LayerLoading.cpp \
    StageFirst.cpp \
    StageLogin.cpp \
    StageStart.cpp \
    option/ItemOption.cpp \
    option/LayerOption.cpp \
    LayerBlock.cpp \
    StageChangePassword.cpp \
    StageOption.cpp \
    StageRegister.cpp \
    product_list/InterfaceView.cpp \
    product_list/Item4View.cpp \
    product_list/ItemZooming.cpp \
    product_list/Layer4View.cpp \
    product_list/LayerZoomView.cpp

HEADERS  += widget.h \
#    StageFirst.h \
#    StageLogin.h \
#    StageStart.h \
#    LayerLoading.h
    LayerLoading.h \
    StageFirst.h \
    StageLogin.h \
    StageStart.h \
    option/ItemOption.h \
    option/LayerOption.h \
    LayerBlock.h \
    StageChangePassword.h \
    StageOption.h \
    StageRegister.h \
    product_list/InterfaceView.h \
    product_list/Item4View.h \
    product_list/ItemZooming.h \
    product_list/Layer4View.h \
    product_list/LayerZoomView.h

FORMS    += widget.ui \
#    StageFirst.ui \
#    StageLogin.ui \
#    StageStart.ui \
#    LayerLoading.ui
    LayerLoading.ui \
    StageFirst.ui \
    StageLogin.ui \
    StageStart.ui \
    option/ItemOption.ui \
    StageChangePassword.ui \
    StageRegister.ui \
    product_list/Item4View.ui \
    LayerBlock.ui

CONFIG += mobility
MOBILITY =

RESOURCES += \
    pic.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

