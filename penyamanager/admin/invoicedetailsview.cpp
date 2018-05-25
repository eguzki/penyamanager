//

#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include "invoicedetailsview.h"
#include "ui_invoicedetailsview.h"

namespace PenyaManager {
    //
    InvoiceDetailsView::InvoiceDetailsView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::InvoiceDetailsView)
    {
        ui->setupUi(this);
        initializeTable();
    }
    //
    InvoiceDetailsView::~InvoiceDetailsView()
    {
        delete ui;
    }
    //
    void InvoiceDetailsView::initializeTable()
    {
        // Table
        QHeaderView* header = this->ui->productTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        this->ui->productTableWidget->setColumnCount(5);
        translateTable();
        Uint32 column = 0;
        this->ui->productTableWidget->setColumnWidth(column++, 1);
        this->ui->productTableWidget->setColumnWidth(column++, 228);
        this->ui->productTableWidget->setColumnWidth(column++, 85);
        this->ui->productTableWidget->setColumnWidth(column++, 45);
        this->ui->productTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceDetailsView::translateTable()
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
    // called from admin framework
    void InvoiceDetailsView::init()
    {
        //
        // Loading invoice data
        // current invoice is Singletons::m_currentInvoiceId read by widget
        //
        // use static global variable to get invoiceId
        Int32 invoiceId = Singletons::m_currentInvoiceId;
        InvoiceResultPtr pInvoicePtr = Singletons::m_pDAO->getInvoice(invoiceId);
        if (pInvoicePtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoicePtr->m_pInvoice) {
            // invoice not found, should not happen
            MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
            Singletons::m_pLogger->Error(pCurrMemberPtr->m_id, PenyaManager::LogAction::kInvoice,
                    QString("unable to find expected invoice by id %1").arg(invoiceId));
            return;
        }
        fillInvoiceData(pInvoicePtr->m_pInvoice);
    }
    //
    void InvoiceDetailsView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void InvoiceDetailsView::fillInvoiceData(const InvoicePtr &pInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getAllInvoiceProductItems(pInvoicePtr->m_id);
        if (pInvoiceProductItemListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        this->ui->productTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());
        // invoice table reset
        this->ui->productTableWidget->clearContents();
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;

            // image
            QTableWidgetItem *productImage = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pInvoiceProductItemPtr->m_imagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImage->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->productTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->productTableWidget->setItem(rowCount, 0, productImage);
            this->ui->productTableWidget->setItem(rowCount, 1, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItemPtr->m_productnameEus, pInvoiceProductItemPtr->m_productnameEs)));
            this->ui->productTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_pricePerUnit, 0, 'f', 2)));
            this->ui->productTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_pricePerUnit * pInvoiceProductItemPtr->m_count;
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
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoicePtr->m_date.toLocalTime(), QLocale::NarrowFormat);
        this->ui->invoiceDateValueLabel->setText(dateLocalized);
        // LastModified
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoicePtr->m_lastModified.toLocalTime(), QLocale::NarrowFormat);
        this->ui->invoiceLastModifValueLabel->setText(dateLocalized);
        // Total
        this->ui->invoiceTotalValueLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
        // memberid
        this->ui->memberIdValueLabel->setText(QString("%1").arg(pInvoicePtr->m_memberUsername));
    }
}

