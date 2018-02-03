//

#include <commons/utils.h>
#include <commons/singletons.h>
#include <commons/guiutils.h>
#include "accountview.h"
#include "ui_accountview.h"

namespace PenyaManager {
    //
    AccountView::AccountView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AccountView),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_currentPage(0),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelwidget->layout()->addWidget(m_pMemberProfileGroupBox);

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
        this->ui->accountTableWidget->setColumnWidth(column++, 228);
        this->ui->accountTableWidget->setColumnWidth(column++, 120);
        this->ui->accountTableWidget->setColumnWidth(column++, 120);
        this->ui->accountTableWidget->setColumnWidth(column++, 152);
    }
    //
    void AccountView::init()
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
    void AccountView::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
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
            TransactionPtr pTransactionPtr = *iter;
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pTransactionPtr->m_date.toLocalTime(), QLocale::NarrowFormat);
            this->ui->accountTableWidget->setItem(rowCount, 0, new QTableWidgetItem(dateLocalized));
            this->ui->accountTableWidget->item(rowCount, 0)->setTextAlignment(Qt::AlignCenter);
            this->ui->accountTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_amount, 0, 'f', 2)));
            this->ui->accountTableWidget->item(rowCount, 1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            this->ui->accountTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_balance, 0, 'f', 2)));
            this->ui->accountTableWidget->item(rowCount, 2)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            this->ui->accountTableWidget->setItem(rowCount, 3, new QTableWidgetItem(getStringFromTransactionTypeEnum(pTransactionPtr->m_type)));
            this->ui->accountTableWidget->item(rowCount, 3)->setTextAlignment(Qt::AlignCenter);
            rowCount++;
        }
    }
    //
    void AccountView::selectionChanged()
    {
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
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        pTransactionListStatsResultPtr = Singletons::m_pServices->getAccountListByMemberIdStats(pCurrMemberPtr->m_id, fromDate, toDate);
        if (pTransactionListStatsResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
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
    //
    void AccountView::on_fromCalendarWidget_selectionChanged()
    {
        selectionChanged();
    }
    //
    void AccountView::on_toCalendarWidget_selectionChanged()
    {
        selectionChanged();
    }
}
