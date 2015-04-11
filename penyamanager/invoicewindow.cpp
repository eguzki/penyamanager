//

#include <QMessageBox>

#include "constants.h"
#include "singletons.h"
#include "invoicewindow.h"
#include "ui_invoicewindow.h"

namespace PenyaManager {
    //
    InvoiceWindow::InvoiceWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::InvoiceWindow)
    {
        ui->setupUi(this);
    }
    //
    InvoiceWindow::~InvoiceWindow()
    {
        delete ui;
    }
    //
    void InvoiceWindow::init()
    {
        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(0);
            return;
        }

        //
        // Show
        //

        show();
    }
    //
    void InvoiceWindow::on_backPushButton_clicked()
    {

    }
    //
    void InvoiceWindow::on_confirmPushButton_clicked()
    {
        hide();
        // call login window on exit
        IPartner* pLoginWindow = Singletons::m_pParnetFinder->getPartner(Constants::kLoginWindowKey);
        pLoginWindow->init();
    }
}

