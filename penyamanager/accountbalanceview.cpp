//

#include "singletons.h"
#include "accountbalanceview.h"
#include "ui_accountbalanceview.h"

namespace PenyaManager {
    //
    AccountBalanceView::AccountBalanceView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AccountBalanceView)
    {
        ui->setupUi(this);

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        this->ui->fromDateResultValueLabel->clear();
        this->ui->toDateResultValueLabel->clear();

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
    void AccountBalanceView::initializeTable()
    {
        // table
        this->ui->transactionsTableWidget->setColumnCount(5);

        // invoice table Header
        QStringList headers;
        headers.append("date");
        headers.append("memberid");
        headers.append("description");
        headers.append("amount");
        headers.append("balance");
        this->ui->transactionsTableWidget->setHorizontalHeaderLabels(headers);
        Uint32 column = 0;
        this->ui->transactionsTableWidget->setColumnWidth(column++, 200);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 100);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 300);
        this->ui->transactionsTableWidget->setColumnWidth(column++, 100);
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
    void AccountBalanceView::on_printPushButton_clicked()
    {
        // TODO
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
        // deposit table reset
        this->ui->transactionsTableWidget->clearContents();
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
            pTransactionListPtr = Singletons::m_pDAO->getAccountList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pTransactionListStatsPtr = Singletons::m_pServices->getAccountListStats(fromDate, toDate);
        } else {
            pTransactionListPtr = Singletons::m_pDAO->getAccountListByMemberId(memberId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pTransactionListStatsPtr = Singletons::m_pServices->getAccountListByMemberIdStats(memberId, fromDate, toDate);
        }
    }
}
