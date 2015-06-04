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
        // when central widget is empty, takecentralwidget can lead to core dump
        if (this->centralWidget()) {
            // takeCentralWidget removes central widget. When setting new one, current one is not deleted
            this->takeCentralWidget();
        }
        this->hide();
        // call admin main window
        IPartner* pAdminLoginPartner = Singletons::m_pParnetFinder->getPartner(WindowKey::kAdminLoginWindowKey);
        pAdminLoginPartner->init();
    }
    //
    void AdminMainWindow::on_slow_payers_button_triggered()
    {
        // when central widget is empty, takecentralwidget can lead to core dump
        if (this->centralWidget()) {
            // takeCentralWidget removes central widget. When setting new one, current one is not deleted
            this->takeCentralWidget();
        }
        // call slow payers window
        IPartner* pSlowPayersPartner = Singletons::m_pParnetFinder->getPartner(WindowKey::kAdminSlowPayersWindowKey);
        pSlowPayersPartner->init();
        this->setCentralWidget(pSlowPayersPartner);
    }
    //
    void AdminMainWindow::on_invoice_list_button_triggered()
    {
        // when central widget is empty, takecentralwidget can lead to core dump
        if (this->centralWidget()) {
            // takeCentralWidget removes central widget. When setting new one, current one is not deleted
            this->takeCentralWidget();
        }
        // call invoice list window
        IPartner* pInvoiceListView = Singletons::m_pParnetFinder->getPartner(WindowKey::kAdminInvoiceListWindowKey);
        pInvoiceListView->init();
        this->setCentralWidget(pInvoiceListView);
    }
}
