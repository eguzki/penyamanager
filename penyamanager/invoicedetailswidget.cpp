//

#include "singletons.h"
#include "invoicedetailswidget.h"
#include "ui_invoicedetailswidget.h"

namespace PenyaManager {
    //
    InvoiceDetailsWidget::InvoiceDetailsWidget(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::InvoiceDetailsWidget)
    {
        ui->setupUi(this);
    }
    //
    InvoiceDetailsWidget::~InvoiceDetailsWidget()
    {
        delete ui;
    }
    //
    void InvoiceDetailsWidget::init()
    {
        // use static global variable to get invoiceId
        Int32 invoiceId = Singletons::m_currentInvoiceId;

        //
        // Loading Current Invoice
        //
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getInvoice(invoiceId);

        fillInvoiceData(pInvoicePtr);

        //
        // Show
        //

        show();
    }
    //
    void InvoiceDetailsWidget::fillInvoiceData(const InvoicePtr &pInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        this->ui->productTableWidget->setColumnCount(4);
        this->ui->productTableWidget->setRowCount(pInvoiceProductItemListPtr->size());
        // invoice table Header
        QStringList headers;
        headers.append("article");
        headers.append("price/u");
        headers.append("count");
        headers.append("total");
        this->ui->productTableWidget->setHorizontalHeaderLabels(headers);
        // invoice table reset
        this->ui->productTableWidget->clearContents();
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->productTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->productTableWidget->setItem(rowCount, 1, new QTableWidgetItem(tr("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit)));
            this->ui->productTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->productTableWidget->setItem(rowCount, 3, new QTableWidgetItem(tr("%1 €").arg(totalPrice)));
            totalInvoice += totalPrice;
            rowCount++;
        }

        //
        // Invoice Information
        //
        // ID
        this->ui->invoiceIdValueLabel->setText(QString("%1").arg(pInvoicePtr->m_id));
        // Date
        this->ui->invoiceDateValueLabel->setText(tr("%1").arg(pInvoicePtr->m_date.toString()));
        // Total
        this->ui->invoiceTotalValueLabel->setText(QString("%1 €").arg(totalInvoice));
        // memberid
        this->ui->memberIdValueLabel->setText(QString("%1").arg(pInvoicePtr->m_memberId));
    }
}

