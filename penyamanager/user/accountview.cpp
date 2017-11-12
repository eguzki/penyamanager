//

#include <QMessageBox>

#include <commons/utils.h>
#include <commons/singletons.h>
#include "accountview.h"
#include "ui_accountview.h"

namespace PenyaManager {
    //
    AccountView::AccountView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AccountView),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_currentPage(0),
        m_firstTime(true),
        m_currentMemberId(-1),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelwidget->layout()->addWidget(m_pMemberProfileGroupBox);

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        initializeTable();
    }
    //
    AccountView::~AccountView()
    {
        delete ui;
    }
    //
    void AccountView::initializeTable()
    {
        // table
        this->ui->accountTableWidget->setColumnCount(4);
        QHeaderView* header = this->ui->accountTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        translateTable();
        Uint32 column = 0;
        this->ui->accountTableWidget->setColumnWidth(column++, 200);
        this->ui->accountTableWidget->setColumnWidth(column++, 200);
        this->ui->accountTableWidget->setColumnWidth(column++, 200);
        this->ui->accountTableWidget->setColumnWidth(column++, 130);
    }
    //
    void AccountView::init()
    {
        //
        // Loading User profile
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        if (this->m_firstTime || m_currentMemberId != pCurrMemberPtr->m_id) {
            updateResults();
        }
    }
    //
    void AccountView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void AccountView::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("Date"));
        headers.append(tr("Amount"));
        headers.append(tr("Balance"));
        headers.append(tr("Type"));
        this->ui->accountTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void AccountView::fillAccountData(TransactionListResultPtr pTransactionListResultPtr)
    {
        // invoice table reset
        this->ui->accountTableWidget->clearContents();

        // table
        // num rows
        this->ui->accountTableWidget->setRowCount(pTransactionListResultPtr->m_list->size());

        // fill data
        Uint32 rowCount = 0;
        for (TransactionList::iterator iter = pTransactionListResultPtr->m_list->begin(); iter != pTransactionListResultPtr->m_list->end(); ++iter)
        {
            Uint32 column = 0;
            TransactionPtr pTransactionPtr = *iter;
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pTransactionPtr->m_date, QLocale::NarrowFormat);
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_amount, 0, 'f', 2)));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_balance, 0, 'f', 2)));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(getStringFromTransactionTypeEnum(pTransactionPtr->m_type)));
            rowCount++;
        }
    }
    //
    void AccountView::on_searchButton_clicked()
    {
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        QDate toDate = this->ui->toCalendarWidget->selectedDate();
        if (fromDate > toDate)
        {
            QMessageBox::information(this, "Wrong search criteria", "From date must be before To date");
            return;
        }
        // check selected date is shown checking monthShown and yearShown
        int fromMonthShown = this->ui->fromCalendarWidget->monthShown();
        int fromYearShown = this->ui->fromCalendarWidget->yearShown();
        int toMonthShown = this->ui->toCalendarWidget->monthShown();
        int toYearShown = this->ui->toCalendarWidget->yearShown();
        if ( fromDate.month() != fromMonthShown ||
            toDate.month() != toMonthShown ||
            fromDate.year() != fromYearShown ||
            toDate.year() != toYearShown ) {
            QMessageBox::warning(this, tr("Date not selected"), tr("Select date"));
            return;
        }

        // when user pushes search, afterwards, on init() results are not updated
        this->m_firstTime = false;
        m_currentPage = 0;
        updateResults();
    }
    //
    void AccountView::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void AccountView::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void AccountView::updateResults()
    {
        TransactionListStatsResultPtr pTransactionListStatsResultPtr;
        TransactionListResultPtr pTransactionListResultPtr;
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        // fetch data
        pTransactionListResultPtr = Singletons::m_pDAO->getAccountListByMemberId(pCurrMemberPtr->m_id, fromDate, toDate, m_currentPage, Constants::kAccountListPageCount);
        if (pTransactionListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        pTransactionListStatsResultPtr = Singletons::m_pServices->getAccountListByMemberIdStats(pCurrMemberPtr->m_id, fromDate, toDate);
        if (pTransactionListStatsResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pTransactionListStatsResultPtr->m_listStats->m_totalNumTransactions/Constants::kAccountListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }

        // fill total stats view
        this->ui->totalTransactionsValueLabel->setText(QString::number(pTransactionListStatsResultPtr->m_listStats->m_totalNumTransactions));

        fillAccountData(pTransactionListResultPtr);
    }
    void AccountView::on_newinvoiceButton_clicked()
    {
        //call new invoice window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }

    void AccountView::on_tableReservationButton_clicked()
    {
        // call table reservation window
        m_switchCentralWidgetCallback(WindowKey::kTableReservationViewWindowKey);
    }

    void AccountView::on_invoicesPushButton_clicked()
    {
        // call invoices window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }

    void AccountView::on_depositsButton_clicked()
    {
        // call deposits window
        m_switchCentralWidgetCallback(WindowKey::kDepositsWindowKey);
    }

    void AccountView::on_exitButton_clicked()
    {
        // call login window on exit
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }

}


