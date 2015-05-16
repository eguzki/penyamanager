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

TARGET = penyamanageradmin
TEMPLATE = app

RESOURCES = penyamanager.qrc

SOURCES += adminmain.cpp\
        singletons.cpp\
        dao.cpp\
        utils.cpp\
        constants.cpp\
        services.cpp\
        partnerfinder.cpp\
        objs/Transaction.cpp\
        objs/Invoice.cpp\
        objs/Deposit.cpp\
        objs/Member.cpp\
        objs/ProductFamily.cpp\
        objs/ProductItem.cpp\
        objs/InvoiceProductItem.cpp\
        objs/TableReservation.cpp\
        objs/LunchTable.cpp\
        adminloginwindow.cpp\
        admon_screen.cpp\
        memberselect.cpp

HEADERS  += singletons.h\
        dao.h\
        utils.h\
        constants.h\
        services.h\
        IPartner.h\
        partnerfinder.h\
        objs/Transaction.h\
        objs/Invoice.h\
        objs/Deposit.h\
        objs/Member.h\
        objs/ProductFamily.h\
        objs/ProductItem.h\
        objs/InvoiceProductItem.h\
        objs/TableReservation.h\
        objs/LunchTable.h\
        adminloginwindow.h\
        admon_screen.h\
        memberselect.h

FORMS    += adminloginwindow.ui\
        admon_screen.ui\
        memberselect.ui
