//

#include <QMessageBox>

#include <commons/singletons.h>
#include <commons/guiutils.h>
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
        // use static global variable to get invoiceId
        Int32 invoiceId = Singletons::m_currentInvoiceId;
        InvoiceResultPtr pInvoicePtr = Singletons::m_pDAO->getInvoice(invoiceId);
        if (pInvoicePtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pInvoicePtr->m_pInvoice) {
            // invoice not found, should not happen
            QLOG_ERROR() << QString("[ERROR] unable to find expected invoice by id: %1").arg(invoiceId);
            return;
        }

        this->m_pInvoiceDetailsWidget->init(pInvoicePtr);
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
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getInvoice(invoiceId);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            // member not found, should not happen
            QLOG_WARN() << QString("Unable to find expected invoice by id: %1").arg(invoiceId);
            return;
        }
        // Loading Current Invoice products
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getAllInvoiceProductItems(pInvoiceResultPtr->m_pInvoice->m_id);
        if (pInvoiceProductItemListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }

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
        invoiceData["memberid"] = pCurrMemberPtr->m_username;
        invoiceData["memberName"] = QString("%1 %2 %3").arg(pCurrMemberPtr->m_name).arg(pCurrMemberPtr->m_surname1).arg(pCurrMemberPtr->m_surname2);
        invoiceData["dateValue"] = pInvoiceResultPtr->m_pInvoice->m_date;
        invoiceData["invoiceTotal"] = QString("%1 €").arg(pInvoiceResultPtr->m_pInvoice->m_total, 0, 'f', 2);

        // invoice products info
        QVariantList productList;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QVariantHash productData;
            productData["productName"] = pInvoiceProductItemPtr->m_productname;
            productData["productCount"] = pInvoiceProductItemPtr->m_count;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            productData["productTotal"] = QString("%1 €").arg(totalPrice, 0, 'f', 2);
            productList.push_back(productData);
        }
        invoiceData["products"] = productList;
        // print invoice
        GuiUtils::printInvoice(invoiceData, pCurrMemberPtr->m_id, invoiceId);
        QMessageBox::information(this, tr("Print Invoice"), tr("Invoice #%1 sent to printer").arg(QString::number(invoiceId)));
    }
}

