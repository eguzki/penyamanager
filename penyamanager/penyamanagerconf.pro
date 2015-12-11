#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T00:57:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = penyamanagerconf
CONFIG   += console
CONFIG   -= app_bundle

!win32 {
    QMAKE_CXXFLAGS += -std=c++11
}

TEMPLATE = app

RC_ICONS = images/alegrialogo.ico

include(libs/simplecrypt/simplecrypt.pro)

SOURCES +=  confmain.cpp \
            utils.cpp \
            constants.cpp

HEADERS  += constants.h \
            utils.h
