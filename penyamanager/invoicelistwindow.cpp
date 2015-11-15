//

#include "singletons.h"
#include "invoicelistwindow.h"
#include "ui_invoicelistwindow.h"

namespace PenyaManager {
    //
    InvoiceListWindow::InvoiceListWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::InvoiceListWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_currentPage(0),
        m_firstTime(true)
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
    }
    //
    InvoiceListWindow::~InvoiceListWindow()
    {
        delete ui;
    }
    //
    void InvoiceListWindow::init()
    {
        //
        // Loading User profile
        //

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        if (this->m_firstTime) {
            updateResults();
        }

        //
        // Show
        //

        show();
    }
    //
    void InvoiceListWindow::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void InvoiceListWindow::on_searchPushButton_clicked()
    {
        // when user pushes search, afterwards, on init() results are not updated
        this->m_firstTime = false;
        m_currentPage = 0;
        updateResults();
    }
    //
    void InvoiceListWindow::on_backPushButton_clicked()
    {
        switchWindow(WindowKey::kMainWindowKey);
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
        InvoiceListPtr pInvoiceList;
        InvoiceListStatsPtr pInvoiceListStats;
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        pInvoiceList = Singletons::m_pDAO->getInvoiceListByMemberId(pCurrMemberPtr->m_id, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
        pInvoiceListStats = Singletons::m_pDAO->getInvoiceListByMemberIdStats(pCurrMemberPtr->m_id, fromDate, toDate);
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceListStats->m_totalNumInvoices/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pInvoiceListStats->m_totalNumInvoices));
        this->ui->totalCountValueLabel->setText(tr("%1 €").arg(pInvoiceListStats->m_totalAmount));
        // fill dates used for query
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(fromDate);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_translationManager.getLocale().toString(toDate.addDays(-1));
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillInvoiceList(pInvoiceList);
    }
    //
    void InvoiceListWindow::fillInvoiceList(InvoiceListPtr pInvoiceListPtr)
    {
        // table
        this->ui->invoicesTableWidget->setColumnCount(4);
        this->ui->invoicesTableWidget->setRowCount(pInvoiceListPtr->size());

        // invoice table Header
        QStringList headers;
        headers.append("Ref#");
        headers.append("Date");
        headers.append("Total");
        headers.append("idMember");
        this->ui->invoicesTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->invoicesTableWidget->setColumnWidth(0, 100);
        this->ui->invoicesTableWidget->setColumnWidth(1, 300);
        this->ui->invoicesTableWidget->setColumnWidth(2, 200);
        this->ui->invoicesTableWidget->setColumnWidth(3, 100);
        // invoice table reset
        this->ui->invoicesTableWidget->clearContents();
        // internal data structure reset
        this->m_rowProductIdMap.clear();

        // fill data
        Uint32 rowCount = 0;
        for (InvoiceList::iterator iter = pInvoiceListPtr->begin(); iter != pInvoiceListPtr->end(); ++iter)
        {
            InvoicePtr pInvoicePtr = *iter;
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pInvoicePtr->m_id)));
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pInvoicePtr->m_date.toString()));
            this->ui->invoicesTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1 €").arg(pInvoicePtr->m_total)));
            this->ui->invoicesTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(pInvoicePtr->m_memberId)));
            this->m_rowProductIdMap[rowCount] = pInvoicePtr->m_id;
            rowCount++;
        }
    }
    //
    void InvoiceListWindow::on_invoicesTableWidget_cellDoubleClicked(int row, int column)
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
        switchWindow(WindowKey::kInvoiceDetailsWindowKey);
    }
}

