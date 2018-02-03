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

CONFIG += c++11

TEMPLATE = app

RC_ICONS = images/alegrialogo.ico

include(libs/simplecrypt/simplecrypt.pro)
include(libs/QsLog2/QsLog.pri)

SOURCES +=  confmain.cpp \
            commons/utils.cpp \
            commons/constants.cpp

HEADERS  += commons/constants.h \
            commons/utils.h
