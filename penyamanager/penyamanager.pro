#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T19:19:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QTPLUGIN += qsqlmysql

#QMAKE_CXXFLAGS += -std=gnu++0x
QMAKE_CXXFLAGS += -std=c++11

TARGET = penyamanager
TEMPLATE = app

RESOURCES = penyamanager.qrc

SOURCES += main.cpp\
        singletons.cpp\
        dao.cpp\
        mainwindow.cpp\
        utils.cpp\
        constants.cpp\
        services.cpp\
        partnerfinder.cpp\
        objs/Transaction.cpp\
        objs/Invoice.cpp\
        objs/Member.cpp\
        objs/ProductFamily.cpp\
        objs/ProductItem.cpp\
        objs/InvoiceProductItem.cpp\
        loginwindow.cpp \
    numitemdialog.cpp \
    invoicewindow.cpp

HEADERS  += mainwindow.h\
        singletons.h\
        dao.h\
        utils.h\
        constants.h\
        services.h\
        IPartner.h\
        partnerfinder.h\
        objs/Transaction.h\
        objs/Invoice.h\
        objs/Member.h\
        objs/ProductFamily.h\
        objs/ProductItem.h\
        objs/InvoiceProductItem.h\
        loginwindow.h \
    numitemdialog.h \
    invoicewindow.h

FORMS    += mainwindow.ui\
        loginwindow.ui \
    numitemdialog.ui \
    invoicewindow.ui
