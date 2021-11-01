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
        commons/dao.cpp \
        commons/dao_member.cpp \
        commons/dao_invoice.cpp \
        commons/dao_account.cpp \
        commons/dao_oven.cpp \
        commons/dao_fireplace.cpp \
        commons/dao_lunchtable.cpp \
        commons/dao_productfamily.cpp \
        commons/dao_product.cpp \
        commons/dao_invoice_product.cpp \
        commons/dao_deposit.cpp \
        commons/dao_provider.cpp \
        commons/dao_provider_invoice.cpp \
        commons/dao_provider_invoices_product.cpp \
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
        user/memberdashboardwindow.cpp\
        user/loginwindow.cpp \
        user/timednumitemdialog.cpp \
        user/depositwindow.cpp \
        user/accountview.cpp \
        user/tablereservationview.cpp \
        user/invoicelistwindow.cpp \
        user/memberprofilegroupbox.cpp \
        user/invoicedetailswindow.cpp \
        user/mainwindow.cpp \

HEADERS  += commons/singletons.h\
        commons/dao.h\
        commons/timedmessagebox.h\
        commons/utils.h\
        commons/constants.h\
        commons/services.h\
        commons/IPartner.h\
        commons/partnerfinder.h\
        commons/familyitemwidget.h\
        commons/productitemwidget.h\
        commons/guiutils.h \
        commons/translationmanager.h \
        commons/DataTypes.h \
        commons/logging.h \
        commons/inactivityeventfilter.h \
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
        objs/Transaction.h\
        user/memberdashboardwindow.h\
        user/loginwindow.h \
        user/timednumitemdialog.h \
        user/depositwindow.h \
        user/accountview.h \
        user/tablereservationview.h \
        user/invoicelistwindow.h \
        user/memberprofilegroupbox.h \
        user/invoicedetailswindow.h \
        user/mainwindow.h

FORMS    += commons/familyitemwidget.ui \
        commons/productitemwidget.ui \
        user/memberdashboardwindow.ui\
        user/loginwindow.ui \
        user/timednumitemdialog.ui \
        user/depositwindow.ui \
        user/accountview.ui \
        user/tablereservationview.ui \
        user/invoicelistwindow.ui \
        user/memberprofilegroupbox.ui \
        user/invoicedetailswindow.ui \
        user/mainwindow.ui

TRANSLATIONS += \
    translations/penyamanager_es.ts \
    translations/penyamanager_eu.ts
