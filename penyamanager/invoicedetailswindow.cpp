//

#include "singletons.h"
#include "invoicedetailswindow.h"
#include "ui_invoicedetailswindow.h"

namespace PenyaManager {
    //
    InvoiceDetailsWindow::InvoiceDetailsWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::InvoiceDetailsWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_pInvoiceDetailsWidget(new InvoiceDetailsWidget)
    {
        ui->setupUi(this);
        this->ui->verticalLayout->addWidget(m_pInvoiceDetailsWidget);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
    }
    //
    InvoiceDetailsWindow::~InvoiceDetailsWindow()
    {
        delete ui;
    }
    //
    void InvoiceDetailsWindow::init()
    {
        //
        // Loading User profile
        //

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        //
        // Loading invoice data
        // current invoice is Singletons::m_currentInvoiceId read by widget
        //

        this->m_pInvoiceDetailsWidget->init();

        //
        // Show
        //

        show();
    }
    //
    void InvoiceDetailsWindow::on_backPushButton_clicked()
    {
        switchWindow(WindowKey::kInvoiceListWindoKey);
    }
}

