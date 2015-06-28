//

#include <QDebug>
#include <QMessageBox>

#include "singletons.h"
#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

namespace PenyaManager {
    //
    AdminMainWindow::AdminMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AdminMainWindow)
    {
        ui->setupUi(this);

        this->connect(this->ui->actionExit, &QAction::triggered, std::bind(&AdminMainWindow::on_exit_button_triggered, this));
        this->connect(this->ui->actionSlow_payers, &QAction::triggered, std::bind(&AdminMainWindow::on_slow_payers_button_triggered, this));
        this->connect(this->ui->actionInvoice_list, &QAction::triggered, std::bind(&AdminMainWindow::on_invoice_list_button_triggered, this));
        this->connect(this->ui->actionManage_providers, &QAction::triggered, std::bind(&AdminMainWindow::on_manage_providers_button_triggered, this));
        this->connect(this->ui->actionManage_Stock, &QAction::triggered, std::bind(&AdminMainWindow::on_manage_stock_button_triggered, this));
        this->connect(this->ui->actionManage_family_items, &QAction::triggered, std::bind(&AdminMainWindow::on_manage_family_items_button_triggered, this));
    }
    //
    AdminMainWindow::~AdminMainWindow()
    {
        delete ui;
    }
    //
    void AdminMainWindow::init()
    {
        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(0);
            return;
        }

        show();
    }
    //
    void AdminMainWindow::on_exit_button_triggered()
    {
        // call admin login window
        hide();
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(WindowKey::kAdminLoginWindowKey);
        pPartner->init();
    }
    //
    void AdminMainWindow::on_slow_payers_button_triggered()
    {
        // call slow payers window
        switchCentralWidget(WindowKey::kAdminSlowPayersWindowKey);
    }
    //
    void AdminMainWindow::on_invoice_list_button_triggered()
    {
        // call invoice list window
        switchCentralWidget(WindowKey::kAdminInvoiceListWindowKey);
    }
    //
    void AdminMainWindow::on_manage_providers_button_triggered()
    {
        // call provider manager window
        switchCentralWidget(WindowKey::kAdminProviderWindowKey);
    }
    //
    void AdminMainWindow::on_manage_stock_button_triggered()
    {
        // call stock list window
        switchCentralWidget(WindowKey::kStockManagementWindowKey);
    }
    //
    void AdminMainWindow::on_manage_family_items_button_triggered()
    {
        // call family item management window
        switchCentralWidget(WindowKey::kFamilyItemManagementWindowKey);
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
    }
}
