//

#include <QMessageBox>

#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include "invoicewindow.h"
#include "ui_invoicewindow.h"

namespace PenyaManager {
    //
    InvoiceWindow::InvoiceWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::InvoiceWindow),
        m_currentPage(0),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        initializeTable();
    }
    //
    InvoiceWindow::~InvoiceWindow()
    {
        delete ui;
    }
    //
    void InvoiceWindow::initializeTable()
    {
        // table
        this->ui->invoiceProductTableWidget->setColumnCount(4);
        translateTable();
        Uint32 column = 0;
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 231);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 83);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 45);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceWindow::init()
    {
        //
        // Loading User profile
        //
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMember);

        //
        // Loading Current Invoice
        //
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("No active invoice found. User id: %1").arg(pCurrMember->m_id));
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        m_currentPage = 0;
        fillInvoiceData(pCurrMember, pInvoiceResultPtr->m_pInvoice);
    }
    //
    void InvoiceWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void InvoiceWindow::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append(tr("count"));
        headers.append(tr("total"));
        this->ui->invoiceProductTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void InvoiceWindow::on_backPushButton_clicked()
    {
        // Go to dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void InvoiceWindow::on_confirmPushButton_clicked()
    {
        // Close invoice
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("No active invoice found. User id: %1").arg(pCurrMember->m_id));
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }

        // Update member balance
        bool ok = Singletons::m_pServices->closeInvoice(pCurrMember->m_id, pInvoiceResultPtr->m_pInvoice->m_id);
        if (!ok) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("Error closing invoice. InvoiceId: %1").arg(pInvoiceResultPtr->m_pInvoice->m_id));
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                QString("InvoiceId: %1").arg(pInvoiceResultPtr->m_pInvoice->m_id));

        printInvoice(pCurrMember, pInvoiceResultPtr->m_pInvoice);

        // call dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void InvoiceWindow::fillInvoiceData(const MemberPtr &pMemberPtr, const InvoicePtr &pInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id, m_currentPage, Constants::kInvoiceWindowProductListPageCount);
        if (pInvoiceProductItemListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(pInvoicePtr->m_id);
        if (invoiceProductItemStatsResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)invoiceProductItemStatsResultPtr->m_stats->m_totalProducts/Constants::kInvoiceWindowProductListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }

        // invoice table reset
        this->ui->invoiceProductTableWidget->clearContents();

        this->ui->invoiceProductTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());

        //fill data
        Uint32 rowCount = 0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2)));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            this->ui->invoiceProductTableWidget->setRowHeight(rowCount, 35);
            rowCount++;
        }

        //
        // Invoice Information
        //
        // ID
        this->ui->invoiceIdInfoLabel->setText(QString("%1").arg(pInvoicePtr->m_id));
        // Date
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_date, QLocale::NarrowFormat);
        this->ui->invoiceDateInfoLabel->setText(dateLocalized);
        // Total
        Float totalInvoice = invoiceProductItemStatsResultPtr->m_stats->m_totalAmount;
        this->ui->invoiceTotalInfoLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
        // new balance
        Float newBalance = pMemberPtr->m_balance;
        newBalance -= totalInvoice;
        this->ui->newBalanceInfoLabel->setText(QString("%1 €").arg(newBalance, 0, 'f', 2));
    }
    //
    void InvoiceWindow::printInvoice(const MemberPtr &pMemberPtr, const InvoicePtr &pInvoicePtr)
    {
        // Loading Current Invoice
        // Loading Current Invoice products
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getAllInvoiceProductItems(pInvoicePtr->m_id);
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
        invoiceData["invoiceId"] = pInvoicePtr->m_id;
        invoiceData["memberid"] = pMemberPtr->m_username;
        invoiceData["memberName"] = QString("%1 %2 %3").arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname1).arg(pMemberPtr->m_surname2);
        // invoice date is invoice creation date
        // Can be old (e.g. an unclosed invoice created some days ago)
        // print current date
        invoiceData["dateValue"] = QDateTime::currentDateTime();

        // invoice products info
        QVariantList productList;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QVariantHash productData;
            productData["productName"] = pInvoiceProductItemPtr->m_productname;
            productData["productCount"] = pInvoiceProductItemPtr->m_count;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            totalInvoice += totalPrice;
            productData["productTotal"] = QString("%1 €").arg(totalPrice, 0, 'f', 2);
            productList.push_back(productData);
        }
        invoiceData["products"] = productList;
        // computed invoice total value
        invoiceData["invoiceTotal"] = QString("%1 €").arg(totalInvoice, 0, 'f', 2);
        // print invoice
        GuiUtils::printInvoice(invoiceData, pMemberPtr->m_id, pInvoicePtr->m_id);
        QMessageBox::information(this, tr("Print Invoice"), tr("Invoice #%1 sent to printer").arg(QString::number(pInvoicePtr->m_id)));
    }
    //
    void InvoiceWindow::on_prevPagePushButton_clicked()
    {
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            QMessageBox::critical(this, tr("No active invoice found."), tr("Program will exit"));
            qApp->exit(0);
            return;
        }
        m_currentPage--;
        fillInvoiceData(pCurrMember, pInvoiceResultPtr->m_pInvoice);
    }
    //
    void InvoiceWindow::on_nextPagePushButton_clicked()
    {
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            QMessageBox::critical(this, tr("No active invoice found."), tr("Program will exit"));
            qApp->exit(0);
            return;
        }
        m_currentPage++;
        fillInvoiceData(pCurrMember, pInvoiceResultPtr->m_pInvoice);
    }
}

