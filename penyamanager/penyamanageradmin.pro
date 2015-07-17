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
        adminloginwindow.cpp\
        adminmainwindow.cpp \
        slowpayersview.cpp \
        admininvoicelistview.cpp \
        invoicedetailswidget.cpp \
        providermanagerview.cpp \
        adminnewprovider.cpp \
    stockmanagementwindow.cpp \
    familyitemmanagementwindow.cpp \
    adminproductitem.cpp \
    adminfamilyview.cpp \
    productexpensesview.cpp \
    providerinvoiceview.cpp \
    providerinvoicelistview.cpp \
    depositlistview.cpp \
    accountbalanceview.cpp \
    memberlistview.cpp \
    memberview.cpp

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
        objs/Reservation.h\
        objs/ReservationItem.h\
        objs/Provider.h\
        objs/ProviderInvoice.h\
        adminloginwindow.h\
        adminmainwindow.h \
        slowpayersview.h \
        admininvoicelistview.h \
        invoicedetailswidget.h \
        providermanagerview.h \
        adminnewprovider.h \
    stockmanagementwindow.h \
    familyitemmanagementwindow.h \
    adminproductitem.h \
    adminfamilyview.h \
    productexpensesview.h \
    providerinvoiceview.h \
    providerinvoicelistview.h \
    depositlistview.h \
    accountbalanceview.h \
    memberlistview.h \
    memberview.h

FORMS    += adminloginwindow.ui\
        adminmainwindow.ui \
        slowpayersview.ui \
        admininvoicelistview.ui \
        invoicedetailswidget.ui \
        providermanagerview.ui \
    adminnewprovider.ui \
    stockmanagementwindow.ui \
    familyitemmanagementwindow.ui \
    adminproductitem.ui \
    adminfamilyview.ui \
    productexpensesview.ui \
    providerinvoiceview.ui \
    providerinvoicelistview.ui \
    depositlistview.ui \
    accountbalanceview.ui \
    memberlistview.ui \
    memberview.ui
