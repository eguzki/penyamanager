//

#include "singletons.h"
#include "admininvoicelistview.h"
#include "ui_admininvoicelistview.h"

namespace PenyaManager {
    //
    AdminInvoiceListView::AdminInvoiceListView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AdminInvoiceListView),
        m_currentPage(0)
    {
        ui->setupUi(this);

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);
    }
    //
    AdminInvoiceListView::~AdminInvoiceListView()
    {
        delete ui;
    }
    //
    void AdminInvoiceListView::init()
    {

        //
        // Show
        //

        show();
    }
    //
    void AdminInvoiceListView::on_clearPushButton_clicked()
    {
        this->ui->memberIdLineEdit->clear();
    }
    //
    void AdminInvoiceListView::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void AdminInvoiceListView::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void AdminInvoiceListView::updateResults()
    {
        InvoiceListPtr pInvoiceList;
        InvoiceListStatsPtr pInvoiceListStats;
        bool ok;
        Int32 memberId = this->ui->memberIdLineEdit->text().toInt(&ok);
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        if (!ok) {
            this->ui->memberIdLineEdit->clear();
            pInvoiceList = Singletons::m_pDAO->getInvoiceList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pInvoiceListStats = Singletons::m_pDAO->getInvoiceListStats(fromDate, toDate);
        } else {
            pInvoiceList = Singletons::m_pDAO->getInvoiceListByMemberId(memberId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pInvoiceListStats = Singletons::m_pDAO->getInvoiceListByMemberIdStats(memberId, fromDate, toDate);
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceListStats->m_totalNumInvoices/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pInvoiceListStats->m_totalNumInvoices));
        this->ui->totalCountValueLabel->setText(tr("%1 €").arg(pInvoiceListStats->m_totalAmount));
        // fill invoice list
        fillInvoiceList(pInvoiceList);
    }
    //
    void AdminInvoiceListView::on_searchPushButton_clicked()
    {
        m_currentPage = 0;
        updateResults();
    }
    //
    void AdminInvoiceListView::fillInvoiceList(InvoiceListPtr pInvoiceListPtr)
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

        // fill data
        Uint32 rowCount = 0;
        for (InvoiceList::iterator iter = pInvoiceListPtr->begin(); iter != pInvoiceListPtr->end(); ++iter)
        {
            InvoicePtr pInvoicePtr = *iter;
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pInvoicePtr->m_id)));
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pInvoicePtr->m_date.toString()));
            this->ui->invoicesTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1 €").arg(pInvoicePtr->m_total)));
            this->ui->invoicesTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(pInvoicePtr->m_memberId)));
            rowCount++;
        }
    }
}

