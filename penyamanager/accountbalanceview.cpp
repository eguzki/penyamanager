//

#include "singletons.h"
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

        this->ui->fromCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        this->ui->fromDateResultValueLabel->clear();
        this->ui->toDateResultValueLabel->clear();
        this->ui->memberIdResValueLabel->setText(QString("ALL"));
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

        //
        // Show
        //

        show();
    }
    //
    void AccountBalanceView::translateTable()
    {
        // table reservation table Header
        QStringList headers;
        headers.append(tr("date"));
        headers.append(tr("memberid"));
        headers.append(tr("description"));
        headers.append(tr("amount"));
        this->ui->transactionsTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void AccountBalanceView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
    }
    //
    void AccountBalanceView::initializeTable()
    {
        // table
        this->ui->transactionsTableWidget->setColumnCount(4);
        translateTable();
        Uint32 column = 0;
        this->ui->transactionsTableWidget->setColumnWidth(column++, 200);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 100);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 300);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 100);
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
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pTransactionPtr->m_date, QLocale::NarrowFormat);
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pTransactionPtr->m_memberId)));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pTransactionPtr->m_descr));
            this->ui->transactionsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(tr("%1 €").arg(pTransactionPtr->m_amount)));
            rowCount++;
        }
    }
    //
    void AccountBalanceView::updateResults()
    {
        TransactionListPtr pTransactionListPtr;
        TransactionListStatsPtr pTransactionListStatsPtr;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        bool ok;
        Int32 memberId = this->ui->memberIdLineEdit->text().toInt(&ok);
        if (!ok) {
            this->ui->memberIdLineEdit->clear();
            this->ui->memberIdResValueLabel->setText(QString("ALL"));
            pTransactionListPtr = Singletons::m_pDAO->getAccountList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pTransactionListStatsPtr = Singletons::m_pServices->getAccountListStats(fromDate, toDate);
        } else {
            pTransactionListPtr = Singletons::m_pDAO->getAccountListByMemberId(memberId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pTransactionListStatsPtr = Singletons::m_pServices->getAccountListByMemberIdStats(memberId, fromDate, toDate);
            this->ui->memberIdResValueLabel->setText(QString::number(memberId));
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pTransactionListStatsPtr->m_totalNumTransactions/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalRowsValueLabel->setText(QString::number(pTransactionListStatsPtr->m_totalNumTransactions));
        this->ui->totalDepositsValueLabel->setText(tr("%1 €").arg(pTransactionListStatsPtr->m_totalDeposits));
        this->ui->totalInvoicesValueLabel->setText(tr("%1 €").arg(pTransactionListStatsPtr->m_totalInvoices));
        this->ui->totalBankChargesValueLabel->setText(tr("%1 €").arg(pTransactionListStatsPtr->m_totalBankCharges));
        // fill dates used for query
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_translationManager.getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill transaction list
        fillTransactionList(pTransactionListPtr);
    }
}
