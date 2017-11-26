//

#include <QDebug>
#include <QMessageBox>

#include <commons/singletons.h>
#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

namespace PenyaManager {
    //
    AdminMainWindow::AdminMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AdminMainWindow)
    {
        ui->setupUi(this);
    }
    //
    AdminMainWindow::~AdminMainWindow()
    {
        delete ui;
    }
    //
    void AdminMainWindow::on_actionExit_triggered()
    {
        // call admin login window
        hide();
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(WindowKey::kAdminLoginWindowKey);
        pPartner->init();
        pPartner->show();
    }
    //
    void AdminMainWindow::on_actionSlow_payers_triggered()
    {
        // call slow payers window
        switchCentralWidget(WindowKey::kAdminSlowPayersWindowKey);
    }
    //
    void AdminMainWindow::on_actionInvoice_list_triggered()
    {
        // call invoice list window
        switchCentralWidget(WindowKey::kAdminInvoiceListWindowKey);
    }
    //
    void AdminMainWindow::on_actionManage_providers_triggered()
    {
        // call provider manager window
        switchCentralWidget(WindowKey::kAdminProviderWindowKey);
    }
    //
    void AdminMainWindow::on_actionManage_Stock_triggered()
    {
        // call stock list window
        switchCentralWidget(WindowKey::kStockManagementWindowKey);
    }
    //
    void AdminMainWindow::on_actionManage_family_items_triggered()
    {
        // call family item management window
        switchCentralWidget(WindowKey::kFamilyItemManagementWindowKey);
    }
    //
    void AdminMainWindow::on_actionProduct_consumption_triggered()
    {
        // call family item management window
        switchCentralWidget(WindowKey::kProductExpensesViewKey);
    }
    //
    void AdminMainWindow::on_actionProvider_invoice_triggered()
    {
        Singletons::m_currentProductId = -1;
        // call provider invoice window
        switchCentralWidget(WindowKey::kNewProviderInvoiceViewKey);
    }
    //
    void AdminMainWindow::on_actionProvider_invoice_list_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kProviderInvoiceListViewKey);
    }
    //
    void AdminMainWindow::on_actionDeposit_Check_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kAdminDepositListViewKey);
    }
    //
    void AdminMainWindow::on_actionAccount_Balance_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kAdminAccountBalanceViewKey);
    }
    //
    void AdminMainWindow::on_actionMember_management_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kMemberListViewWindowKey);
    }
    //
    void AdminMainWindow::on_actionManager_reservations_triggered()
    {
        // call reservation window
        switchCentralWidget(WindowKey::kAdminReservationViewKey);
    }
    //
    void AdminMainWindow::switchCentralWidget(WindowKey key)
    {
        // when central widget is empty, takecentralwidget can lead to core dump
        if (this->centralWidget()) {
            // takeCentralWidget removes central widget. When setting new one, current one is not deleted
            this->takeCentralWidget();
        }
        // call invoice list window
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(key);
        pPartner->init();
        this->setCentralWidget(pPartner);
        pPartner->show();
    }
}
