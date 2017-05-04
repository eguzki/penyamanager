//

#include <QMessageBox>
#include <QsLog.h>

#include "guiutils.h"
#include "constants.h"
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
        initializeTable();
    }
    //
    InvoiceDetailsWidget::~InvoiceDetailsWidget()
    {
        delete ui;
    }
    //
    void InvoiceDetailsWidget::initializeTable()
    {
        this->ui->productTableWidget->setColumnCount(5);
        translateTable();
        Uint32 column = 0;
        this->ui->productTableWidget->setColumnWidth(column++, 100);
        this->ui->productTableWidget->setColumnWidth(column++, 200);
        this->ui->productTableWidget->setColumnWidth(column++, 100);
        this->ui->productTableWidget->setColumnWidth(column++, 60);
        this->ui->productTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceDetailsWidget::translateTable()
    {
        // table Header
        QStringList headers;
        headers.append(tr("icon"));
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append("#");
        headers.append(tr("total"));
        this->ui->productTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void InvoiceDetailsWidget::init()
    {
        // use static global variable to get invoiceId
        Int32 invoiceId = Singletons::m_currentInvoiceId;

        //
        // Loading Current Invoice
        //
        InvoiceResultPtr pInvoicePtr = Singletons::m_pDAO->getInvoice(invoiceId);
        if (pInvoicePtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (pInvoicePtr->m_pInvoice) {
            // invoice not found, should not happen
            QLOG_ERROR() << QString("[WARN] unable to find expected invoice by id: %1").arg(invoiceId);
            return;
        }

        fillInvoiceData(pInvoicePtr->m_pInvoice);
        show();
    }
    //
    void InvoiceDetailsWidget::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void InvoiceDetailsWidget::fillInvoiceData(const InvoicePtr &pInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        this->ui->productTableWidget->setRowCount(pInvoiceProductItemListPtr->size());
        // invoice table reset
        this->ui->productTableWidget->clearContents();
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;

            // image
            QTableWidgetItem *productImage = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pInvoiceProductItemPtr->m_imagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImage->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->productTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->productTableWidget->setItem(rowCount, 0, productImage);
            this->ui->productTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->productTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2)));
            this->ui->productTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->productTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            totalInvoice += totalPrice;
            rowCount++;
        }

        //
        // Invoice Information
        //
        // ID
        this->ui->invoiceIdValueLabel->setText(QString("%1").arg(pInvoicePtr->m_id));
        // Date
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_date, QLocale::NarrowFormat);
        this->ui->invoiceDateValueLabel->setText(dateLocalized);
        // LastModified
        dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_lastModified, QLocale::NarrowFormat);
        this->ui->invoiceLastModifValueLabel->setText(dateLocalized);
        // Total
        this->ui->invoiceTotalValueLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
        // memberid
        this->ui->memberIdValueLabel->setText(QString("%1").arg(pInvoicePtr->m_memberId));
    }
}

