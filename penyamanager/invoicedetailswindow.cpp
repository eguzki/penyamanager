//

#include <QMessageBox>

#include "singletons.h"
#include "guiutils.h"
#include "invoicedetailswindow.h"
#include "ui_invoicedetailswindow.h"

namespace PenyaManager {
    //
    InvoiceDetailsWindow::InvoiceDetailsWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::InvoiceDetailsWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_pInvoiceDetailsWidget(new InvoiceDetailsWidget),
        m_switchCentralWidgetCallback(callback)
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
    }
    //
    void InvoiceDetailsWindow::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void InvoiceDetailsWindow::on_backPushButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }
    //
    void InvoiceDetailsWindow::on_printButton_clicked()
    {
        // use static global variable to get invoiceId
        Int32 invoiceId = Singletons::m_currentInvoiceId;
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;

        // Loading Current Invoice
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getInvoice(invoiceId);
        // Loading Current Invoice products
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);

        QVariantHash invoiceData;
        // Label
        invoiceData["invoiceLabel"] = tr("Invoice");
        invoiceData["memberidLabel"] = tr("Member Id");
        invoiceData["productLabel"] = tr("Product");
        invoiceData["countLabel"] = tr("Count");
        invoiceData["productTotalLabel"] = tr("Total");
        invoiceData["invoiceTotalLabel"] = tr("Invoice Total");

        // invoice general info
        invoiceData["invoiceId"] = invoiceId;
        invoiceData["memberid"] = pCurrMemberPtr->m_id;
        invoiceData["memberName"] = QString("%1 %2").arg(pCurrMemberPtr->m_name).arg(pCurrMemberPtr->m_surname);
        invoiceData["dateValue"] = pInvoicePtr->m_date;
        invoiceData["invoiceTotal"] = QString("%1 €").arg(QString::number(pInvoicePtr->m_total, 'f', 2));

        // invoice products info
        QVariantList productList;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QVariantHash productData;
            productData["productName"] = pInvoiceProductItemPtr->m_productname;
            productData["productCount"] = pInvoiceProductItemPtr->m_count;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            productData["productTotal"] = QString("%1 €").arg(QString::number(totalPrice, 'f', 2));
            productList.push_back(productData);
        }
        invoiceData["products"] = productList;
        // print invoice
        GuiUtils::printInvoice(invoiceData, pCurrMemberPtr->m_id, invoiceId);
        QMessageBox::information(this, tr("Print Invoice"), tr("Invoice #%1 sent to printer").arg(QString::number(invoiceId)));
    }
}


