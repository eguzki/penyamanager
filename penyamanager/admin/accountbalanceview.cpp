//
#include <commons/singletons.h>
#include <commons/guiutils.h>
#include <objs/Transaction.h>

#include "accountbalanceview.h"
#include "ui_accountbalanceview.h"

namespace PenyaManager {
    //
    AccountBalanceView::AccountBalanceView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AccountBalanceView),
        m_currentPage(0),
        m_firstTime(true)
    {
        ui->setupUi(this);

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        this->ui->fromDateResultValueLabel->clear();
        this->ui->toDateResultValueLabel->clear();
        this->ui->memberIdResValueLabel->setText(tr("ALL"));
        this->ui->totalRowsValueLabel->clear();

        initializeTable();
    }
    //
    AccountBalanceView::~AccountBalanceView()
    {
        delete ui;
    }
    //
    void AccountBalanceView::init()
    {
        if (this->m_firstTime) {
            updateResults();
        }
    }
    //
    void AccountBalanceView::translateTable()
    {
        // table reservation table Header
        QStringList headers;
        headers.append(tr("date"));
        headers.append(tr("username"));
        headers.append(tr("description"));
        headers.append(tr("amount"));
        headers.append(tr("type"));
        this->ui->transactionsTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void AccountBalanceView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    void AccountBalanceView::initializeTable()
    {
        // table
        this->ui->transactionsTableWidget->setColumnCount(5);
        translateTable();
        Uint32 column = 0;
        this->ui->transactionsTableWidget->setColumnWidth(column++, 200);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 100);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 300);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 200);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 200);
    }
    //
    void AccountBalanceView::on_searchPushButton_clicked()
    {
        // when user pushes search, afterwards, on init() results are not updated
        this->m_firstTime = false;
        m_currentPage = 0;
        updateResults();
    }
    //
    void AccountBalanceView::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void AccountBalanceView::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void AccountBalanceView::on_clearPushButton_clicked()
    {
        this->ui->memberIdLineEdit->clear();
    }
    //
    void AccountBalanceView::fillTransactionList(TransactionListPtr pTransactionListPtr)
    {
        // num rows
        this->ui->transactionsTableWidget->setRowCount(pTransactionListPtr->size());
        // table reset
        this->ui->transactionsTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (TransactionList::iterator iter = pTransactionListPtr->begin(); iter != pTransactionListPtr->end(); ++iter)
        {
            Uint32 column = 0;
            TransactionPtr pTransactionPtr = *iter;
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pTransactionPtr->m_date.toLocalTime(), QLocale::NarrowFormat);
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pTransactionPtr->m_memberUsername)));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(GuiUtils::getTransactionDescr(pTransactionPtr->m_descr, pTransactionPtr->m_type)));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_amount, 0, 'f', 2)));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(getStringFromTransactionTypeEnum(pTransactionPtr->m_type)));
            rowCount++;
        }
    }
    //
    void AccountBalanceView::updateResults()
    {
        TransactionListResultPtr pTransactionListResultPtr;
        TransactionListStatsResultPtr pTransactionListStatsResultPtr;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        QString usernameStr = this->ui->memberIdLineEdit->text().trimmed();
        if (usernameStr.isEmpty()) {
            this->ui->memberIdLineEdit->clear();
            this->ui->memberIdResValueLabel->setText(tr("ALL"));
            pTransactionListResultPtr = Singletons::m_pDAO->getAccountList(fromDate, toDate, m_currentPage, Constants::kAdminAccountListPageCount);
            if (pTransactionListResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            pTransactionListStatsResultPtr = Singletons::m_pServices->getAccountListStats(fromDate, toDate);
            if (pTransactionListStatsResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        } else {
            bool ok;
            Int32 memberUsername = usernameStr.toInt(&ok);
            if (!ok) {
                this->ui->memberIdLineEdit->clear();
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Username not valid"), [](){});
                return;
            } else {
                MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(memberUsername);
                if (pMemberResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                if (!pMemberResultPtr->m_member)
                {
                    // User could not be found
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Username not found"), [](){});
                    return;
                }
                pTransactionListResultPtr = Singletons::m_pDAO->getAccountListByMemberId(pMemberResultPtr->m_member->m_id, fromDate, toDate, m_currentPage, Constants::kAdminAccountListPageCount);
                if (pTransactionListResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                pTransactionListStatsResultPtr = Singletons::m_pServices->getAccountListByMemberIdStats(pMemberResultPtr->m_member->m_id, fromDate, toDate);
                if (pTransactionListStatsResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                this->ui->memberIdResValueLabel->setText(QString::number(memberUsername));
            }
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pTransactionListStatsResultPtr->m_listStats->m_totalNumTransactions/Constants::kAdminAccountListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalRowsValueLabel->setText(QString::number(pTransactionListStatsResultPtr->m_listStats->m_totalNumTransactions));
        this->ui->totalDepositsValueLabel->setText(QString("%1 €").arg(pTransactionListStatsResultPtr->m_listStats->m_totalDeposits, 0, 'f', 2));
        this->ui->totalInvoicesValueLabel->setText(QString("%1 €").arg(pTransactionListStatsResultPtr->m_listStats->m_totalInvoices, 0, 'f', 2));
        this->ui->totalBankChargesValueLabel->setText(QString("%1 €").arg(pTransactionListStatsResultPtr->m_listStats->m_totalBankCharges, 0, 'f', 2));
        // fill dates used for query
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill transaction list
        fillTransactionList(pTransactionListResultPtr->m_list);
    }
}
