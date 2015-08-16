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
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES +=  confmain.cpp \
            utils.cpp \
            constants.cpp \
            libs/simplecrypt.cpp

HEADERS  += constants.h \
            utils.h \
            libs/simplecrypt.h
