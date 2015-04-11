//

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
    }
}
