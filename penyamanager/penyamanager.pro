#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T19:19:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QTPLUGIN += qsqlmysql

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
        IPartner.cpp\
        partnerfinder.cpp\
        objs/Transaction.cpp\
        objs/Invoice.cpp\
        objs/Deposit.cpp\
        objs/Member.cpp\
        objs/ProductFamily.cpp\
        objs/ProductItem.cpp\
        objs/InvoiceProductItem.cpp\
        objs/Reservation.cpp\
        objs/ReservationItem.cpp\
        objs/Provider.cpp\
        objs/ProviderInvoice.cpp\
        loginwindow.cpp \
        numitemdialog.cpp \
        invoicewindow.cpp \
        depositwindow.cpp \
        accountview.cpp \
        tablereservationview.cpp \
        invoicelistwindow.cpp \
        invoicedetailswidget.cpp \
        memberprofilegroupbox.cpp \
    invoicedetailswindow.cpp

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
        objs/Deposit.h\
        objs/Member.h\
        objs/ProductFamily.h\
        objs/ProductItem.h\
        objs/InvoiceProductItem.h\
        objs/Reservation.h\
        objs/ReservationItem.h\
        objs/Provider.h\
        objs/ProviderInvoice.h\
        loginwindow.h \
        numitemdialog.h \
        invoicewindow.h \
        depositwindow.h \
        accountview.h \
        tablereservationview.h \
        invoicelistwindow.h \
        invoicedetailswidget.h \
        memberprofilegroupbox.h \
    invoicedetailswindow.h

        FORMS    += mainwindow.ui\
        loginwindow.ui \
        numitemdialog.ui \
        invoicewindow.ui \
        depositwindow.ui \
        accountview.ui \
        tablereservationview.ui \
        invoicelistwindow.ui \
        invoicedetailswidget.ui \
        memberprofilegroupbox.ui \
    invoicedetailswindow.ui
