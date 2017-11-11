//

#include <QMessageBox>
#include <commons/singletons.h>
#include "invoicelistwindow.h"
#include "ui_invoicelistwindow.h"

namespace PenyaManager {
    //
    InvoiceListWindow::InvoiceListWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::InvoiceListWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_currentPage(0),
        m_firstTime(true),
        m_currentMemberId(-1),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);

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
    InvoiceListWindow::~InvoiceListWindow()
    {
        delete ui;
    }
    //
    void InvoiceListWindow::initializeTable()
    {
        // table
        this->ui->invoicesTableWidget->setColumnCount(2);
        QHeaderView* header = this->ui->invoicesTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        translateTable();
        Uint32 column = 0;
        this->ui->invoicesTableWidget->setColumnWidth(column++, 360);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceListWindow::init()
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
    void InvoiceListWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void InvoiceListWindow::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("Date"));
        headers.append(tr("Total"));
        this->ui->invoicesTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void InvoiceListWindow::on_searchPushButton_clicked()
    {
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        QDate toDate = this->ui->toCalendarWidget->selectedDate();
        if (fromDate > toDate)
        {
            QMessageBox::information(this, tr("Wrong search criteria"), tr("From date must be before To date"));
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
    void InvoiceListWindow::on_backPushButton_clicked()
    {
        // Go to dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void InvoiceListWindow::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void InvoiceListWindow::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void InvoiceListWindow::updateResults()
    {
        InvoiceListResultPtr pInvoiceListResult;
        InvoiceListStatsResultPtr pInvoiceListStatsResult;
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        pInvoiceListResult = Singletons::m_pDAO->getInvoiceListByMemberId(pCurrMemberPtr->m_id, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
        if (pInvoiceListResult->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        pInvoiceListStatsResult = Singletons::m_pDAO->getInvoiceListByMemberIdStats(pCurrMemberPtr->m_id, fromDate, toDate);
        if (pInvoiceListStatsResult->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceListStatsResult->m_stats->m_totalNumInvoices/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pInvoiceListStatsResult->m_stats->m_totalNumInvoices));
        this->ui->totalCountValueLabel->setText(QString("%1 €").arg(pInvoiceListStatsResult->m_stats->m_totalAmount, 0, 'f', 2));
        // fill dates used for query
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_translationManager.getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillInvoiceList(pInvoiceListResult->m_list);
    }
    //
    void InvoiceListWindow::fillInvoiceList(InvoiceListPtr pInvoiceListPtr)
    {
        // invoice table reset
        this->ui->invoicesTableWidget->clearContents();

        // table
        this->ui->invoicesTableWidget->setRowCount(pInvoiceListPtr->size());

        // internal data structure reset
        this->m_rowProductIdMap.clear();

        // fill data
        Uint32 rowCount = 0;
        for (InvoiceList::iterator iter = pInvoiceListPtr->begin(); iter != pInvoiceListPtr->end(); ++iter)
        {
            InvoicePtr pInvoicePtr = *iter;
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_date, QLocale::NarrowFormat);
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(dateLocalized));
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoicePtr->m_total, 0, 'f', 2)));
            this->m_rowProductIdMap[rowCount] = pInvoicePtr->m_id;
            rowCount++;
        }
    }
    //
    void PenyaManager::InvoiceListWindow::on_invoicesTableWidget_cellClicked(int row, int column)
    {
        UNUSEDPARAMETER(column);
        auto rowMap = m_rowProductIdMap.find(row);
        if (rowMap == m_rowProductIdMap.end()) {
            //this should never happen
            qDebug() << "[ERROR] invoiceID not found and should be in the map";
            return;
        }
        Int32 invoiceId = rowMap->second;
        // use static global variable to pass argument
        Singletons::m_currentInvoiceId = invoiceId;

        // call invoice details window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceDetailsWindowKey);
    }
    //
    void InvoiceListWindow::on_exitButton_2_clicked()
    {
        // call login window on exit
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
    void InvoiceListWindow::on_exitButton_clicked()
    {
        // call login window on exit
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
    void InvoiceListWindow::on_newinvoiceButton_clicked()
    {
        //call new invoice window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    void InvoiceListWindow::on_tableReservationButton_clicked()
    {
        // call table reservation window
        m_switchCentralWidgetCallback(WindowKey::kTableReservationViewWindowKey);
    }
    void InvoiceListWindow::on_accountButton_clicked()
    {
        // call account window
        m_switchCentralWidgetCallback(WindowKey::kAccountViewWindowKey);
    }
    void InvoiceListWindow::on_depositsButton_clicked()
    {
        // call deposits window
        m_switchCentralWidgetCallback(WindowKey::kDepositsWindowKey);
    }


}

