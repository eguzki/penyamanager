/********************************************************************************
** Form generated from reading UI file 'adminmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINMAINWINDOW_H
#define UI_ADMINMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminMainWindow
{
public:
    QAction *actionMember_management;
    QAction *actionNew_member;
    QAction *actionInvoice_list;
    QAction *actionSlowPayersExport;
    QAction *actionSlowPayersPrint;
    QAction *actionSlowPayersResetAccount;
    QAction *actionProvider_invoice;
    QAction *actionProduct_consumption;
    QAction *actionManage_family_items;
    QAction *actionManage_providers;
    QAction *actionManage_Stock;
    QAction *actionDeposit_Check;
    QAction *actionAccount_Balance;
    QAction *actionExit;
    QAction *actionSlow_payers;
    QAction *actionProvider_invoice_list;
    QAction *actionManager_reservations;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuMembers;
    QMenu *menuInvoices;
    QMenu *menuStock;
    QMenu *menuAccount;
    QMenu *menuMain;
    QMenu *menuProviders;
    QMenu *menuReservations;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminMainWindow)
    {
        if (AdminMainWindow->objectName().isEmpty())
            AdminMainWindow->setObjectName(QStringLiteral("AdminMainWindow"));
        AdminMainWindow->resize(1280, 1024);
        AdminMainWindow->setMinimumSize(QSize(1280, 1024));
        AdminMainWindow->setMaximumSize(QSize(1280, 1024));
        actionMember_management = new QAction(AdminMainWindow);
        actionMember_management->setObjectName(QStringLiteral("actionMember_management"));
        actionNew_member = new QAction(AdminMainWindow);
        actionNew_member->setObjectName(QStringLiteral("actionNew_member"));
        actionInvoice_list = new QAction(AdminMainWindow);
        actionInvoice_list->setObjectName(QStringLiteral("actionInvoice_list"));
        actionSlowPayersExport = new QAction(AdminMainWindow);
        actionSlowPayersExport->setObjectName(QStringLiteral("actionSlowPayersExport"));
        actionSlowPayersPrint = new QAction(AdminMainWindow);
        actionSlowPayersPrint->setObjectName(QStringLiteral("actionSlowPayersPrint"));
        actionSlowPayersResetAccount = new QAction(AdminMainWindow);
        actionSlowPayersResetAccount->setObjectName(QStringLiteral("actionSlowPayersResetAccount"));
        actionProvider_invoice = new QAction(AdminMainWindow);
        actionProvider_invoice->setObjectName(QStringLiteral("actionProvider_invoice"));
        actionProduct_consumption = new QAction(AdminMainWindow);
        actionProduct_consumption->setObjectName(QStringLiteral("actionProduct_consumption"));
        actionManage_family_items = new QAction(AdminMainWindow);
        actionManage_family_items->setObjectName(QStringLiteral("actionManage_family_items"));
        actionManage_providers = new QAction(AdminMainWindow);
        actionManage_providers->setObjectName(QStringLiteral("actionManage_providers"));
        actionManage_Stock = new QAction(AdminMainWindow);
        actionManage_Stock->setObjectName(QStringLiteral("actionManage_Stock"));
        actionDeposit_Check = new QAction(AdminMainWindow);
        actionDeposit_Check->setObjectName(QStringLiteral("actionDeposit_Check"));
        actionAccount_Balance = new QAction(AdminMainWindow);
        actionAccount_Balance->setObjectName(QStringLiteral("actionAccount_Balance"));
        actionExit = new QAction(AdminMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSlow_payers = new QAction(AdminMainWindow);
        actionSlow_payers->setObjectName(QStringLiteral("actionSlow_payers"));
        actionProvider_invoice_list = new QAction(AdminMainWindow);
        actionProvider_invoice_list->setObjectName(QStringLiteral("actionProvider_invoice_list"));
        actionManager_reservations = new QAction(AdminMainWindow);
        actionManager_reservations->setObjectName(QStringLiteral("actionManager_reservations"));
        centralwidget = new QWidget(AdminMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        AdminMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 25));
        menuMembers = new QMenu(menubar);
        menuMembers->setObjectName(QStringLiteral("menuMembers"));
        menuInvoices = new QMenu(menubar);
        menuInvoices->setObjectName(QStringLiteral("menuInvoices"));
        menuStock = new QMenu(menubar);
        menuStock->setObjectName(QStringLiteral("menuStock"));
        menuAccount = new QMenu(menubar);
        menuAccount->setObjectName(QStringLiteral("menuAccount"));
        menuMain = new QMenu(menubar);
        menuMain->setObjectName(QStringLiteral("menuMain"));
        menuProviders = new QMenu(menubar);
        menuProviders->setObjectName(QStringLiteral("menuProviders"));
        menuReservations = new QMenu(menubar);
        menuReservations->setObjectName(QStringLiteral("menuReservations"));
        AdminMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        AdminMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMain->menuAction());
        menubar->addAction(menuMembers->menuAction());
        menubar->addAction(menuInvoices->menuAction());
        menubar->addAction(menuStock->menuAction());
        menubar->addAction(menuAccount->menuAction());
        menubar->addAction(menuProviders->menuAction());
        menubar->addAction(menuReservations->menuAction());
        menuMembers->addAction(actionMember_management);
        menuMembers->addSeparator();
        menuMembers->addAction(actionSlow_payers);
        menuInvoices->addAction(actionInvoice_list);
        menuStock->addAction(actionProduct_consumption);
        menuStock->addAction(actionManage_family_items);
        menuStock->addAction(actionManage_Stock);
        menuAccount->addAction(actionDeposit_Check);
        menuAccount->addAction(actionAccount_Balance);
        menuMain->addAction(actionExit);
        menuProviders->addAction(actionManage_providers);
        menuProviders->addAction(actionProvider_invoice);
        menuProviders->addAction(actionProvider_invoice_list);
        menuReservations->addAction(actionManager_reservations);

        retranslateUi(AdminMainWindow);

        QMetaObject::connectSlotsByName(AdminMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminMainWindow)
    {
        AdminMainWindow->setWindowTitle(QApplication::translate("AdminMainWindow", "Penyamanager Application Manager", 0));
        actionMember_management->setText(QApplication::translate("AdminMainWindow", "Member management", 0));
        actionNew_member->setText(QApplication::translate("AdminMainWindow", "New member", 0));
        actionInvoice_list->setText(QApplication::translate("AdminMainWindow", "Invoice list", 0));
        actionSlowPayersExport->setText(QApplication::translate("AdminMainWindow", "Export", 0));
        actionSlowPayersPrint->setText(QApplication::translate("AdminMainWindow", "Print", 0));
        actionSlowPayersResetAccount->setText(QApplication::translate("AdminMainWindow", "Reset Account", 0));
        actionProvider_invoice->setText(QApplication::translate("AdminMainWindow", "New provider invoice", 0));
        actionProduct_consumption->setText(QApplication::translate("AdminMainWindow", "Product Consumption", 0));
        actionManage_family_items->setText(QApplication::translate("AdminMainWindow", "Manage Families/Goods", 0));
        actionManage_providers->setText(QApplication::translate("AdminMainWindow", "Manage Providers", 0));
        actionManage_Stock->setText(QApplication::translate("AdminMainWindow", "Stock List", 0));
        actionDeposit_Check->setText(QApplication::translate("AdminMainWindow", "Deposit Check", 0));
        actionAccount_Balance->setText(QApplication::translate("AdminMainWindow", "Account Balance", 0));
        actionExit->setText(QApplication::translate("AdminMainWindow", "Exit", 0));
        actionSlow_payers->setText(QApplication::translate("AdminMainWindow", "Slow payers", 0));
        actionProvider_invoice_list->setText(QApplication::translate("AdminMainWindow", "Provider Invoice List", 0));
        actionManager_reservations->setText(QApplication::translate("AdminMainWindow", "Manage reservations", 0));
        menuMembers->setTitle(QApplication::translate("AdminMainWindow", "Members", 0));
        menuInvoices->setTitle(QApplication::translate("AdminMainWindow", "Invoices", 0));
        menuStock->setTitle(QApplication::translate("AdminMainWindow", "Items", 0));
        menuAccount->setTitle(QApplication::translate("AdminMainWindow", "Account", 0));
        menuMain->setTitle(QApplication::translate("AdminMainWindow", "Main", 0));
        menuProviders->setTitle(QApplication::translate("AdminMainWindow", "Providers", 0));
        menuReservations->setTitle(QApplication::translate("AdminMainWindow", "Reservations", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminMainWindow: public Ui_AdminMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINMAINWINDOW_H
