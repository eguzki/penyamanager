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

TARGET = penyamanager
TEMPLATE = app

include(libs/QsLog2/QsLog.pri)
include(libs/simplecrypt/simplecrypt.pro)
include(libs/mustache/mustache.pro)

RESOURCES = penyamanager.qrc

RC_ICONS = images/alegrialogo.ico

SOURCES += main.cpp\
        commons/singletons.cpp\
        commons/dao.cpp\
        user/memberdashboardwindow.cpp\
        commons/utils.cpp\
        commons/constants.cpp\
        commons/services.cpp\
        commons/IPartner.cpp\
        commons/partnerfinder.cpp\
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
        user/loginwindow.cpp \
        commons/numitemdialog.cpp \
        user/invoicewindow.cpp \
        user/depositwindow.cpp \
        user/accountview.cpp \
        user/tablereservationview.cpp \
        user/invoicelistwindow.cpp \
        user/memberprofilegroupbox.cpp \
        user/invoicedetailswindow.cpp \
        commons/guiutils.cpp \
        commons/translationmanager.cpp \
        user/mainwindow.cpp \
        commons/familyitemwidget.cpp \
        commons/productitemwidget.cpp \
        commons/logging.cpp \
        commons/inactivityeventfilter.cpp \
        commons/dialogmanager.cpp \
        commons/passchangedialog.cpp

HEADERS  += user/memberdashboardwindow.h\
        commons/singletons.h\
        commons/dao.h\
        commons/utils.h\
        commons/constants.h\
        commons/services.h\
        commons/IPartner.h\
        commons/partnerfinder.h\
        commons/familyitemwidget.h\
        commons/productitemwidget.h\
        commons/passchangedialog.h \
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
        user/loginwindow.h \
        commons/numitemdialog.h \
        user/invoicewindow.h \
        user/depositwindow.h \
        user/accountview.h \
        user/tablereservationview.h \
        user/invoicelistwindow.h \
        user/memberprofilegroupbox.h \
        user/invoicedetailswindow.h \
        commons/guiutils.h \
        commons/translationmanager.h \
        commons/DataTypes.h \
        user/mainwindow.h \
        commons/logging.h \
        commons/inactivityeventfilter.h \
        commons/dialogmanager.h

FORMS    += user/memberdashboardwindow.ui\
        user/loginwindow.ui \
        commons/numitemdialog.ui \
        commons/passchangedialog.ui \
        user/invoicewindow.ui \
        user/depositwindow.ui \
        user/accountview.ui \
        user/tablereservationview.ui \
        user/invoicelistwindow.ui \
        user/memberprofilegroupbox.ui \
        user/invoicedetailswindow.ui \
        user/mainwindow.ui \
        commons/familyitemwidget.ui \
        commons/productitemwidget.ui

TRANSLATIONS += \
    translations/penyamanager_es.ts \
    translations/penyamanager_eu.ts
