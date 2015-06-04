//

#include "admininvoicedetails.h"
#include "ui_admininvoicedetails.h"

namespace PenyaManager {
    //
    AdminInvoiceDetails::AdminInvoiceDetails(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AdminInvoiceDetails)
    {
        ui->setupUi(this);
    }
    //
    AdminInvoiceDetails::~AdminInvoiceDetails()
    {
        delete ui;
    }
    //
    void AdminInvoiceDetails::init()
    {

        //
        // Show
        //

        show();
    }
}
