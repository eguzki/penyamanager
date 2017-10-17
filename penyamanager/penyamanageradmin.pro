#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T19:19:33
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += sql
QT       += widgets

QTPLUGIN += qsqlmysql

CONFIG += c++11

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
        commons/invoicedetailswidget.cpp \
        commons/guiutils.cpp \
        commons/translationmanager.cpp \
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
        objs/ProviderInvoiceProductItem.cpp\
        admin/adminloginwindow.cpp\
        admin/adminmainwindow.cpp \
        admin/slowpayersview.cpp \
        admin/admininvoicelistview.cpp \
        admin/providermanagerview.cpp \
        admin/adminnewprovider.cpp \
        admin/stockmanagementwindow.cpp \
        admin/familyitemmanagementwindow.cpp \
        admin/adminproductitem.cpp \
        admin/adminfamilyview.cpp \
        admin/productexpensesview.cpp \
        admin/newproviderinvoiceview.cpp \
        admin/providerinvoicelistview.cpp \
        admin/depositlistview.cpp \
        admin/accountbalanceview.cpp \
        admin/memberlistview.cpp \
        admin/memberview.cpp \
        admin/passchangedialog.cpp \
        admin/adminreservationswindow.cpp \
        admin/providerinvoiceview.cpp \
        commons/familyitemwidget.cpp \
        commons/productitemwidget.cpp

HEADERS += commons/singletons.h\
        commons/dao.h\
        commons/utils.h\
        commons/constants.h\
        commons/services.h\
        commons/IPartner.h\
        commons/partnerfinder.h\
        commons/numitemdialog.h \
        commons/DataTypes.h \
        commons/invoicedetailswidget.h \
        commons/guiutils.h \
        commons/translationmanager.h \
        commons/familyitemwidget.h\
        commons/productitemwidget.h\
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
        objs/ProviderInvoiceProductItem.h\
        admin/adminloginwindow.h\
        admin/adminmainwindow.h \
        admin/slowpayersview.h \
        admin/admininvoicelistview.h \
        admin/providermanagerview.h \
        admin/adminnewprovider.h \
        admin/stockmanagementwindow.h \
        admin/familyitemmanagementwindow.h \
        admin/adminproductitem.h \
        admin/adminfamilyview.h \
        admin/productexpensesview.h \
        admin/newproviderinvoiceview.h \
        admin/providerinvoicelistview.h \
        admin/depositlistview.h \
        admin/accountbalanceview.h \
        admin/memberlistview.h \
        admin/memberview.h \
        admin/passchangedialog.h \
        admin/adminreservationswindow.h \
        admin/providerinvoiceview.h \

FORMS   += admin/adminloginwindow.ui\
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
        admin/providerinvoicelistview.ui \
        admin/depositlistview.ui \
        admin/newproviderinvoiceview.ui \
        admin/accountbalanceview.ui \
        admin/memberlistview.ui \
        admin/memberview.ui \
        admin/passchangedialog.ui \
        admin/adminreservationswindow.ui \
        admin/providerinvoiceview.ui \
        commons/familyitemwidget.ui \
        commons/productitemwidget.ui

TRANSLATIONS += \
        translations/penyamanageradmin_es.ts \
        translations/penyamanageradmin_eu.ts
