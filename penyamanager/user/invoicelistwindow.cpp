//

#include <commons/singletons.h>
#include <commons/guiutils.h>
#include "invoicelistwindow.h"
#include "ui_invoicelistwindow.h"

namespace PenyaManager {
    //
    InvoiceListWindow::InvoiceListWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::InvoiceListWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_currentPage(0),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        QTableView *view = this->ui->fromCalendarWidget->findChild<QTableView*>("qt_calendar_calendarview");
        if (view)
        {
            QPalette pal = view->palette();
            pal.setColor(QPalette::Base, QColor(189,189,189));
            view->setPalette(pal);
        }
        view = this->ui->toCalendarWidget->findChild<QTableView*>("qt_calendar_calendarview");
        if (view)
        {
            QPalette pal = view->palette();
            pal.setColor(QPalette::Base, QColor(189,189,189));
            view->setPalette(pal);
        }

        initializeTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
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
        QHeaderView* header = this->ui->invoicesTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        this->ui->invoicesTableWidget->setColumnCount(2);
        translateTable();
        Uint32 column = 0;
        this->ui->invoicesTableWidget->setColumnWidth(column++, 358);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 100);
    }
    //
    void InvoiceListWindow::init()
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

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // set maximum selectable date
        this->ui->fromCalendarWidget->setMaximumDate(toInitialDate);
        this->ui->toCalendarWidget->setMaximumDate(toInitialDate);
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);
        bool shouldUpdate = true;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        if (fromDate != fromIntialDate) {
            // since dates are different, selectionChanged event will be triggered
            this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
            shouldUpdate = false;
        }
        QDate toDate = this->ui->toCalendarWidget->selectedDate();
        if (toDate != toInitialDate) {
            // since dates are different, selectionChanged event will be triggered
            this->ui->toCalendarWidget->setSelectedDate(toInitialDate);
            shouldUpdate = false;
        }
        if (shouldUpdate) {
            updateResults();
        }
    }
    //
    void InvoiceListWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
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
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        pInvoiceListStatsResult = Singletons::m_pDAO->getInvoiceListByMemberIdStats(pCurrMemberPtr->m_id, fromDate, toDate);
        if (pInvoiceListStatsResult->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceListStatsResult->m_stats->m_totalNumInvoices/Constants::kInvoiceListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }

        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pInvoiceListStatsResult->m_stats->m_totalNumInvoices));
        this->ui->totalCountValueLabel->setText(QString("%1 €").arg(pInvoiceListStatsResult->m_stats->m_totalAmount, 0, 'f', 2));
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
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoicePtr->m_date.toLocalTime(), QLocale::NarrowFormat);
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(dateLocalized));
            this->ui->invoicesTableWidget->item(rowCount, 0)->setTextAlignment(Qt::AlignCenter);
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoicePtr->m_total, 0, 'f', 2)));
            this->ui->invoicesTableWidget->item(rowCount, 1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            this->m_rowProductIdMap[rowCount] = pInvoicePtr->m_id;
            rowCount++;
        }
    }
    //
    void PenyaManager::InvoiceListWindow::on_invoicesTableWidget_cellPressed(int row, int column)
    {
        UNUSEDPARAMETER(column);
        auto rowMap = m_rowProductIdMap.find(row);
        if (rowMap == m_rowProductIdMap.end()) {
            //this should never happen
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kInvoice,
                    QString("On invoice table list clicked, product id not found."));
            return;
        }
        Int32 invoiceId = rowMap->second;
        // use static global variable to pass argument
        Singletons::m_currentInvoiceId = invoiceId;

        // call invoice details window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceDetailsWindowKey);
    }
    //
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
    //
    void InvoiceListWindow::on_fromCalendarWidget_selectionChanged()
    {
        selectionChanged();
    }
    //
    void InvoiceListWindow::on_toCalendarWidget_selectionChanged()
    {
        selectionChanged();
    }
    //
    void InvoiceListWindow::selectionChanged()
    {
        // By default, the selected date is the current date.
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        QDate toDate = this->ui->toCalendarWidget->selectedDate();
        if (fromDate > toDate)
        {
            Singletons::m_pDialogManager->infoMessageBox(this, tr("'From' date must be before 'To' date"), [](){});
            return;
        }

        m_currentPage = 0;
        updateResults();
    }
}

