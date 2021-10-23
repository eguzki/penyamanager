#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T19:19:33
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += sql
QT       += widgets
QT       += network

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
        commons/timedmessagebox.cpp\
        commons/utils.cpp\
        commons/constants.cpp\
        commons/services.cpp\
        commons/IPartner.cpp\
        commons/partnerfinder.cpp\
        commons/guiutils.cpp \
        commons/translationmanager.cpp \
        commons/familyitemwidget.cpp \
        commons/productitemwidget.cpp \
        commons/logging.cpp \
        commons/inactivityeventfilter.cpp \
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
        admin/adminreservationswindow.cpp \
        admin/providerinvoiceview.cpp \
        admin/invoicedetailsview.cpp \
        admin/timedpasschangedialog.cpp \
        admin/timedfiledialog.cpp \
        admin/alertsview.cpp

HEADERS += commons/singletons.h\
        commons/dao.h\
        commons/utils.h\
        commons/constants.h\
        commons/timedmessagebox.h\
        commons/services.h\
        commons/IPartner.h\
        commons/partnerfinder.h\
        commons/DataTypes.h \
        commons/guiutils.h \
        commons/translationmanager.h \
        commons/familyitemwidget.h\
        commons/productitemwidget.h\
        commons/logging.h \
        commons/inactivityeventfilter.h \
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
        admin/adminreservationswindow.h \
        admin/providerinvoiceview.h \
        admin/invoicedetailsview.h \
        admin/timedpasschangedialog.h \
        admin/timedfiledialog.h \
        admin/alertsview.h

FORMS   += commons/familyitemwidget.ui \
        commons/productitemwidget.ui \
        admin/adminloginwindow.ui\
        admin/adminmainwindow.ui \
        admin/slowpayersview.ui \
        admin/admininvoicelistview.ui \
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
        admin/adminreservationswindow.ui \
        admin/providerinvoiceview.ui \
        admin/invoicedetailsview.ui \
        admin/timedpasschangedialog.ui \
        admin/alertsview.ui

TRANSLATIONS += \
        translations/penyamanageradmin_es.ts \
        translations/penyamanageradmin_eu.ts
