//

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
        m_currentPage(0),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        initializeTable();
    }
    //
    InvoiceDetailsWindow::~InvoiceDetailsWindow()
    {
        delete ui;
    }
    //
    void InvoiceDetailsWindow::initializeTable()
    {
        // Table
        QHeaderView* header = this->ui->productTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        this->ui->productTableWidget->setColumnCount(4);
        translateTable();
        Uint32 column = 0;
        this->ui->productTableWidget->setColumnWidth(column++, 228);
        this->ui->productTableWidget->setColumnWidth(column++, 85);
        this->ui->productTableWidget->setColumnWidth(column++, 45);
        this->ui->productTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceDetailsWindow::translateTable()
    {
        // table Header
        QStringList headers;
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append(tr("count"));
        headers.append(tr("total"));
        this->ui->productTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void InvoiceDetailsWindow::init()
    {
        //
        // Loading User profile
        //
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_pCurrMember->m_id);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kDashboard,
                    QString("Unable to find owner by id %1").arg(Singletons::m_pCurrMember->m_id));
            return;
        }

        MemberPtr pCurrMemberPtr = pMemberResultPtr->m_member;
        Singletons::m_pCurrMember = pCurrMemberPtr;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);
        m_currentPage = 0;
        updateResults();
    }
    //
    void InvoiceDetailsWindow::updateResults()
    {
        //
        // Loading invoice data
        // current invoice is Singletons::m_currentInvoiceId read by widget
        //
        // use static global variable to get invoiceId
        Int32 invoiceId = Singletons::m_currentInvoiceId;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getInvoice(invoiceId);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            // invoice not found, should not happen
            MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
            Singletons::m_pLogger->Error(pCurrMemberPtr->m_id, PenyaManager::LogAction::kInvoice,
                    QString("unable to find expected invoice by id %1").arg(invoiceId));
            return;
        }
        //
        // Product List
        //
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoiceResultPtr->m_pInvoice->m_id, m_currentPage, Constants::kInvoiceDetailsWindowProductListPageCount);
        if (pInvoiceProductItemListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(pInvoiceResultPtr->m_pInvoice->m_id);
        if (invoiceProductItemStatsResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)invoiceProductItemStatsResultPtr->m_stats->m_totalProducts/Constants::kInvoiceDetailsWindowProductListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }

        //
        // Invoice Information
        //
        // Date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoiceResultPtr->m_pInvoice->m_date.toLocalTime(), QLocale::NarrowFormat);
        this->ui->invoiceDateValueLabel->setText(dateLocalized);
        // LastModified
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoiceResultPtr->m_pInvoice->m_lastModified.toLocalTime(), QLocale::NarrowFormat);
        this->ui->invoiceLastModifValueLabel->setText(dateLocalized);
        // fill items
        fillInvoiceData(pInvoiceProductItemListResultPtr);
    }
    //
    void InvoiceDetailsWindow::fillInvoiceData(const InvoiceProductItemListResultPtr &pInvoiceProductItemListResultPtr)
    {
        // invoice table reset
        this->ui->productTableWidget->clearContents();

        this->ui->productTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;

            this->ui->productTableWidget->setItem(rowCount, 0, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItemPtr->m_productnameEus, pInvoiceProductItemPtr->m_productnameEs)));
            this->ui->productTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_pricePerUnit, 0, 'f', 2)));
            this->ui->productTableWidget->item(rowCount, 1)->setTextAlignment(Qt::AlignCenter);
            this->ui->productTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            this->ui->productTableWidget->item(rowCount, 2)->setTextAlignment(Qt::AlignCenter);
            // Closed invoice, show total price of the items on closing moment
            Float totalPrice = pInvoiceProductItemPtr->m_pricePerUnit * pInvoiceProductItemPtr->m_count;
            this->ui->productTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            this->ui->productTableWidget->item(rowCount, 3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            this->ui->productTableWidget->setRowHeight(rowCount, 35);
            totalInvoice += totalPrice;
            rowCount++;
        }
        // Total
        this->ui->invoiceTotalValueLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
    }
    //
    void InvoiceDetailsWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
        translateTable();
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
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            // member not found, should not happen
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("unable to find expected invoice. invoiceId %1").arg(invoiceId));
            return;
        }
        // Loading Current Invoice products
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getAllInvoiceProductItems(pInvoiceResultPtr->m_pInvoice->m_id);
        if (pInvoiceProductItemListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
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
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoiceResultPtr->m_pInvoice->m_date, QLocale::NarrowFormat);
        invoiceData["dateValue"] = dateLocalized;
        invoiceData["invoiceTotal"] = QString("%1 €").arg(pInvoiceResultPtr->m_pInvoice->m_total, 0, 'f', 2);

        // invoice products info
        QVariantList productList;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QVariantHash productData;
            productData["productName"] = Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItemPtr->m_productnameEus, pInvoiceProductItemPtr->m_productnameEs);
            productData["productCount"] = pInvoiceProductItemPtr->m_count;
            // Closed invoice, show total price of the items on closing moment
            Float totalPrice = pInvoiceProductItemPtr->m_pricePerUnit * pInvoiceProductItemPtr->m_count;
            productData["productTotal"] = QString("%1 €").arg(totalPrice, 0, 'f', 2);
            productList.push_back(productData);
        }
        invoiceData["products"] = productList;
        // print invoice
        GuiUtils::printInvoice(invoiceData, pCurrMemberPtr->m_id, invoiceId);
        Singletons::m_pDialogManager->infoMessageBox(this, tr("Invoice sent to printer"), [](){});
        // no code should be added after infoMessageBox
    }
    //
    void InvoiceDetailsWindow::on_newinvoiceButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void InvoiceDetailsWindow::on_tableReservationButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kTableReservationViewWindowKey);
    }
    //
    void InvoiceDetailsWindow::on_invoicesPushButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }
    //
    void InvoiceDetailsWindow::on_accountButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kAccountViewWindowKey);
    }
    //
    void InvoiceDetailsWindow::on_depositsButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kDepositsWindowKey);
    }
    //
    void InvoiceDetailsWindow::on_exitButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
    //
    void InvoiceDetailsWindow::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void InvoiceDetailsWindow::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
}

