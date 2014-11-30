#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T19:19:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QTPLUGIN += qsqlmysql

TARGET = penyamanager
TEMPLATE = app

SOURCES += main.cpp\
        singletons.cpp\
        ddbbhelper.cpp\
        mainwindow.cpp\
        loginwindow.cpp

HEADERS  += mainwindow.h\
        singletons.h\
        ddbbhelper.h\
        loginwindow.h

FORMS    += mainwindow.ui\
        loginwindow.ui
