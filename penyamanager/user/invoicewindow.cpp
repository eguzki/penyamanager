//

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
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 228);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 85);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 45);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceWindow::init()
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

        //
        // Loading Current Invoice
        //
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("no active invoice found. userid %1").arg(pCurrMemberPtr->m_id));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        m_currentPage = 0;
        fillInvoiceData(pCurrMemberPtr, pInvoiceResultPtr->m_pInvoice);
    }
    //
    void InvoiceWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
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
    void InvoiceWindow::on_confirmPushButton_clicked()
    {
        // Close invoice
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("no active invoice found. userid %1").arg(pCurrMemberPtr->m_id));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // Update member balance
        bool ok = Singletons::m_pServices->closeInvoice(pInvoiceResultPtr->m_pInvoice);
        if (!ok) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("error closing invoice. invoiceId %1").arg(pInvoiceResultPtr->m_pInvoice->m_id));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                QString("invoiceId %1").arg(pInvoiceResultPtr->m_pInvoice->m_id));

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
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(pInvoicePtr->m_id);
        if (invoiceProductItemStatsResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
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
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 0, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItemPtr->m_productnameEus, pInvoiceProductItemPtr->m_productnameEs)));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_currentPricePerUnit, 0, 'f', 2)));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_currentPricePerUnit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            this->ui->invoiceProductTableWidget->setRowHeight(rowCount, 35);
            totalInvoice += totalPrice;
            rowCount++;
        }

        //
        // Invoice Information
        //
        // Date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoicePtr->m_date.toLocalTime(), QLocale::NarrowFormat);
        this->ui->invoiceDateInfoLabel->setText(dateLocalized);
        // Total
        this->ui->invoiceTotalInfoLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
        // new balance
        Float newBalance = pMemberPtr->m_balance;
        newBalance -= totalInvoice;
        this->ui->newBalanceInfoLabel->setText(QString("%1 €").arg(newBalance, 0, 'f', 2));
    }
    //
    void InvoiceWindow::on_prevPagePushButton_clicked()
    {
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Unexpected error. Contact administrator"), [](){});
            return;
        }
        m_currentPage--;
        fillInvoiceData(pCurrMemberPtr, pInvoiceResultPtr->m_pInvoice);
    }
    //
    void InvoiceWindow::on_nextPagePushButton_clicked()
    {
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Unexpected error. Contact administrator"), [](){});
            qApp->exit(0);
            return;
        }
        m_currentPage++;
        fillInvoiceData(pCurrMemberPtr, pInvoiceResultPtr->m_pInvoice);
    }
    //
    void InvoiceWindow::on_newinvoiceButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void InvoiceWindow::on_tableReservationButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kTableReservationViewWindowKey);
    }
    //
    void InvoiceWindow::on_invoicesPushButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }
    //
    void InvoiceWindow::on_accountButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kAccountViewWindowKey);
    }
    //
    void InvoiceWindow::on_depositsButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kDepositsWindowKey);
    }
    //
    void InvoiceWindow::on_exitButton_clicked()
    {
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
}

