//

#include <commons/singletons.h>
#include "admininvoicelistview.h"
#include "ui_admininvoicelistview.h"

namespace PenyaManager {
    //
    AdminInvoiceListView::AdminInvoiceListView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AdminInvoiceListView),
        m_switchCentralWidgetCallback(callback),
        m_currentPage(0),
        m_firstTime(true)
    {
        ui->setupUi(this);

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());

        this->ui->fromDateResultValueLabel->clear();
        this->ui->toDateResultValueLabel->clear();
        initializeTable();
    }
    //
    AdminInvoiceListView::~AdminInvoiceListView()
    {
        delete ui;
    }
    //
    void AdminInvoiceListView::initializeTable()
    {
        // table Header
        // table
        this->ui->invoicesTableWidget->setColumnCount(4);
        translateTable();
        Uint32 column = 0;
        this->ui->invoicesTableWidget->setColumnWidth(column++, 100);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 300);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 200);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 100);
    }
    //
    void AdminInvoiceListView::translateTable()
    {
        QStringList headers;
        headers.append(tr("Ref#"));
        headers.append(tr("Date"));
        headers.append(tr("Total"));
        headers.append(tr("Username"));
        this->ui->invoicesTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void AdminInvoiceListView::init()
    {
        if (this->m_firstTime) {
            updateResults();
        }
    }
    //
    void AdminInvoiceListView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
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
        InvoiceListResultPtr pInvoiceListResult;
        InvoiceListStatsResultPtr pInvoiceListStatsResult;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        QString memberUsernameStr = this->ui->memberIdLineEdit->text().trimmed();
        if (memberUsernameStr.isEmpty()) {
            this->ui->memberIdLineEdit->clear();
            pInvoiceListResult = Singletons::m_pDAO->getInvoiceList(fromDate, toDate, m_currentPage, Constants::kAdminInvoiceListPageCount);
            if (pInvoiceListResult->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            pInvoiceListStatsResult = Singletons::m_pDAO->getInvoiceListStats(fromDate, toDate);
            if (pInvoiceListStatsResult->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        } else {
            bool ok;
            Int32 memberUsername = memberUsernameStr.toInt(&ok);
            if (!ok) {
                Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Username not valid"), [](){});
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
                    Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Username not found"), [](){});
                    return;
                }
                pInvoiceListResult = Singletons::m_pDAO->getInvoiceListByMemberId(pMemberResultPtr->m_member->m_id, fromDate, toDate, m_currentPage, Constants::kAdminInvoiceListPageCount);
                if (pInvoiceListResult->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                pInvoiceListStatsResult = Singletons::m_pDAO->getInvoiceListByMemberIdStats(pMemberResultPtr->m_member->m_id, fromDate, toDate);
                if (pInvoiceListStatsResult->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
            }
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceListStatsResult->m_stats->m_totalNumInvoices/Constants::kAdminInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pInvoiceListStatsResult->m_stats->m_totalNumInvoices));
        this->ui->totalCountValueLabel->setText(QString("%1 €").arg(pInvoiceListStatsResult->m_stats->m_totalAmount, 0, 'f', 2));
        // fill dates used for query
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillInvoiceList(pInvoiceListResult->m_list);
    }
    //
    void AdminInvoiceListView::on_searchPushButton_clicked()
    {
        // when user pushes search, afterwards, on init() results are not updated
        this->m_firstTime = false;
        m_currentPage = 0;
        updateResults();
    }
    //
    void AdminInvoiceListView::fillInvoiceList(InvoiceListPtr pInvoiceListPtr)
    {
        // invoice table reset
        this->ui->invoicesTableWidget->clearContents();
        // internal data structure reset
        this->m_rowProductIdMap.clear();

        this->ui->invoicesTableWidget->setRowCount(pInvoiceListPtr->size());

        // fill data
        Uint32 rowCount = 0;
        for (InvoiceList::iterator iter = pInvoiceListPtr->begin(); iter != pInvoiceListPtr->end(); ++iter)
        {
            InvoicePtr pInvoicePtr = *iter;
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pInvoicePtr->m_id)));
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoicePtr->m_date.toLocalTime(), QLocale::NarrowFormat);
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(dateLocalized));
            this->ui->invoicesTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1 €").arg(pInvoicePtr->m_total, 0, 'f', 2)));
            this->ui->invoicesTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(pInvoicePtr->m_memberUsername)));
            this->m_rowProductIdMap[rowCount] = pInvoicePtr->m_id;
            rowCount++;
        }
    }
    //
    void AdminInvoiceListView::on_invoicesTableWidget_cellDoubleClicked(int row, int column)
    {
        UNUSEDPARAMETER(column);
        auto rowMap = m_rowProductIdMap.find(row);
        if (rowMap == m_rowProductIdMap.end()) {
            //this should never happen
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kInvoice,
                    QString("On invoice table list clicked, invoice id not found."));
            return;
        }
        Int32 invoiceId = rowMap->second;
        // use static global variable to pass argument
        Singletons::m_currentInvoiceId = invoiceId;

        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kInvoiceDetailsWindowKey);
    }
}

