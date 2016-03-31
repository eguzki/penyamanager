#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T19:19:33
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QTPLUGIN += qsqlmysql

QMAKE_CXXFLAGS += -std=c++11

TARGET = penyamanageradmin
TEMPLATE = app

include(libs/QsLog2/QsLog.pri)
include(libs/simplecrypt/simplecrypt.pro)
include(libs/mustache/mustache.pro)

RESOURCES = penyamanager.qrc

RC_ICONS = images/alegrialogo.ico

SOURCES += adminmain.cpp\
        commons/singletons.cpp\
        commons/dao.cpp\
        commons/utils.cpp\
        commons/constants.cpp\
        commons/services.cpp\
        commons/IPartner.cpp\
        commons/partnerfinder.cpp\
        commons/numitemdialog.cpp \
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
        admin/adminloginwindow.cpp\
        admin/adminmainwindow.cpp \
        admin/slowpayersview.cpp \
        admin/admininvoicelistview.cpp \
        commons/invoicedetailswidget.cpp \
        admin/providermanagerview.cpp \
        admin/adminnewprovider.cpp \
        admin/stockmanagementwindow.cpp \
        admin/familyitemmanagementwindow.cpp \
        admin/adminproductitem.cpp \
        admin/adminfamilyview.cpp \
        admin/productexpensesview.cpp \
        admin/providerinvoiceview.cpp \
        admin/providerinvoicelistview.cpp \
        admin/depositlistview.cpp \
        admin/accountbalanceview.cpp \
        admin/memberlistview.cpp \
        admin/memberview.cpp \
        admin/passchangedialog.cpp \
        commons/guiutils.cpp \
        commons/translationmanager.cpp \
    admin/adminreservationswindow.cpp

HEADERS  += commons/singletons.h\
        commons/dao.h\
        commons/utils.h\
        commons/constants.h\
        commons/services.h\
        commons/IPartner.h\
        commons/partnerfinder.h\
        commons/numitemdialog.h \
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
        admin/adminloginwindow.h\
        admin/adminmainwindow.h \
        admin/slowpayersview.h \
        admin/admininvoicelistview.h \
        commons/invoicedetailswidget.h \
        admin/providermanagerview.h \
        admin/adminnewprovider.h \
        admin/stockmanagementwindow.h \
        admin/familyitemmanagementwindow.h \
        admin/adminproductitem.h \
        admin/adminfamilyview.h \
        admin/productexpensesview.h \
        admin/providerinvoiceview.h \
        admin/providerinvoicelistview.h \
        admin/depositlistview.h \
        admin/accountbalanceview.h \
        admin/memberlistview.h \
        admin/memberview.h \
        admin/passchangedialog.h \
        commons/guiutils.h \
        commons/DataTypes.h \
        commons/translationmanager.h \
    admin/adminreservationswindow.h

FORMS    += admin/adminloginwindow.ui\
        admin/adminmainwindow.ui \
        admin/slowpayersview.ui \
        admin/admininvoicelistview.ui \
        commons/invoicedetailswidget.ui \
        commons/numitemdialog.ui \
        admin/providermanagerview.ui \
        admin/adminnewprovider.ui \
        admin/stockmanagementwindow.ui \
        admin/familyitemmanagementwindow.ui \
        admin/adminproductitem.ui \
        admin/adminfamilyview.ui \
        admin/productexpensesview.ui \
        admin/providerinvoiceview.ui \
        admin/providerinvoicelistview.ui \
        admin/depositlistview.ui \
        admin/accountbalanceview.ui \
        admin/memberlistview.ui \
        admin/memberview.ui \
        admin/passchangedialog.ui \
    admin/adminreservationswindow.ui

TRANSLATIONS += \
        translations/penyamanageradmin_es.ts \
        translations/penyamanageradmin_eu.ts
