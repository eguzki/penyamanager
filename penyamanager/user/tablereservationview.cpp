//

#include <QPushButton>

#include <commons/utils.h>
#include <commons/singletons.h>
#include <commons/guiutils.h>
#include "tablereservationview.h"
#include "ui_tablereservationview.h"

namespace PenyaManager {
    // Rules:
    // * One member, one reservation in a given (day, reservationtype {lunch, dinner})
    // * Reservations can be done only for the current week days
    // * Reservations are available since Monday 06:00AM till Sunday 23:59PM
    // * Reservations can be cancelled

    //
    TableReservationView::TableReservationView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::TableReservationView),
        m_currentPage(0),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);

        QTableView *view = this->ui->calendarWidget->findChild<QTableView*>("qt_calendar_calendarview");
        if (view)
        {
            QPalette pal = view->palette();
            pal.setColor(QPalette::Base, QColor(189,189,189));
            view->setPalette(pal);
        }

        // reservation type
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        // reservation item
        this->ui->reservationItemButtonGroup->setId(this->ui->tablePushButton, static_cast<Int32>(ReservationItemType::LunchTableType));
        this->ui->reservationItemButtonGroup->setId(this->ui->ovenPushButton, static_cast<Int32>(ReservationItemType::OvenType));
        this->ui->reservationItemButtonGroup->setId(this->ui->fireplacePushButton, static_cast<Int32>(ReservationItemType::FireplaceType));

        initializeTable();
        this->ui->calendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    TableReservationView::~TableReservationView()
    {
        delete ui;
    }
    //
    void TableReservationView::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
        translateTable();
        this->ui->calendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    void TableReservationView::translateTable()
    {
        // table reservation table Header
        QStringList headers;
        headers.append(tr("Name"));
        headers.append(tr("Size"));
        headers.append(tr("Reserved By Guest"));
        headers.append(tr("# reserved"));
        headers.append("");
        this->ui->tableReservationTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void TableReservationView::initializeTable()
    {
        // table
        QHeaderView* header = this->ui->tableReservationTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        this->ui->tableReservationTableWidget->setColumnCount(5);
        translateTable();
        Uint32 column = 0;
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 190);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 50);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 125);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 85);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 175);
    }
    //
    void TableReservationView::init()
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

        //
        // Initial state
        //
        initializeTableReservations();
    }
    //
    void TableReservationView::initializeTableReservations()
    {
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 11), QTime(0,0)); // when reservations cannot be done
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 11), QTime(7,0)); // monday after deadline
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 17), QTime(7,0)); // sunday (same day min and max)
        // this date should be localized
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QDate nowDate = nowDateTime.date();

        // initially show hidden. Table will not be filled.
        this->ui->pagingWidget->setHidden(true);

        this->ui->calendarWidget->setSelectedDate(nowDate);
        // set minimum selectable date
        this->ui->calendarWidget->setMinimumDate(nowDate);
        QDate lastDay = nowDate.addDays(7 - nowDate.dayOfWeek());
        // set maximum selectable date
        this->ui->calendarWidget->setMaximumDate(lastDay);

        // check if it is Monday, before 06:00AM
        if (nowDate.dayOfWeek() == 1 && nowDateTime.time().hour() < 6) {
            // monday before deadline, user cannot select for reservation
            this->ui->calendarWidget->setSelectionMode(QCalendarWidget::NoSelection);
            // reservation type (lunch,dinner) buttons
            this->ui->lunchButton->setEnabled(false);
            this->ui->dinnerButton->setEnabled(false);
            // reservation item buttons
            this->ui->tablePushButton->setEnabled(false);
            this->ui->ovenPushButton->setEnabled(false);
            this->ui->fireplacePushButton->setEnabled(false);

        } else {
            // reservation type (lunch,dinner) buttons
            this->ui->lunchButton->setEnabled(true);
            this->ui->dinnerButton->setEnabled(true);
            this->ui->lunchButton->setCheckable(true);
            this->ui->dinnerButton->setCheckable(true);
            // http://blubbqt.blogspot.com.es/2015/04/uncheck-all-buttons-in-qbuttongroup.html
            this->ui->reservationTypeButtonGroup->setExclusive(false);
            this->ui->lunchButton->setChecked(false);
            this->ui->dinnerButton->setChecked(false);
            this->ui->reservationTypeButtonGroup->setExclusive(true);
            this->ui->calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
            // reservation item buttons
            this->ui->tablePushButton->setEnabled(true);
            this->ui->ovenPushButton->setEnabled(true);
            this->ui->fireplacePushButton->setEnabled(true);
            this->ui->tablePushButton->setCheckable(true);
            this->ui->ovenPushButton->setCheckable(true);
            this->ui->fireplacePushButton->setCheckable(true);
            // http://blubbqt.blogspot.com.es/2015/04/uncheck-all-buttons-in-qbuttongroup.html
            this->ui->reservationItemButtonGroup->setExclusive(false);
            this->ui->tablePushButton->setChecked(false);
            this->ui->ovenPushButton->setChecked(false);
            this->ui->fireplacePushButton->setChecked(false);
            this->ui->reservationItemButtonGroup->setExclusive(true);
            }
        // fill empty data
        MemberPtr pMemberPtr = Singletons::m_pCurrMember;
        ReservationItemListStatsPtr pReservationItemListStatsPtr(new ReservationItemListStats);
        pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats);
        fillReservationsItems(pMemberPtr, ReservationListPtr(new ReservationList), ReservationItemListPtr(new ReservationItemList),
                              pReservationItemListStatsPtr);
    }
    //
    void TableReservationView::fillReservationsItems(const MemberPtr &pMemberPtr, const ReservationListPtr &pReservationListPtr, const ReservationItemListPtr &pReservationItemListPtr,
                                                     const ReservationItemListStatsPtr &pReservationItemListStatsPtr)
    {
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pReservationItemListStatsPtr->m_listStats->m_totalNum/Constants::kReservationListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }

        // table reset
        this->ui->tableReservationTableWidget->clearContents();

        // table
        this->ui->tableReservationTableWidget->setRowCount(pReservationItemListPtr->size());

        bool hasReservation = false;
        // create map structure for easy and efficient lookup
        ReservationMap tableReservationMap;
        prepareTableReservationMap(tableReservationMap, pReservationListPtr, pMemberPtr, hasReservation);

        Uint32 rowCount = 0;
        // fill data
        for (ReservationItemList::iterator iter = pReservationItemListPtr->begin(); iter != pReservationItemListPtr->end(); ++iter) {
            ReservationItemPtr pReservationItemPtr = *iter;
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString("%1 %2").arg(GetStringFromReservationItemTypeEnum(pReservationItemPtr->m_itemType, true)).arg(pReservationItemPtr->m_itemName)));
            this->ui->tableReservationTableWidget->item(rowCount, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(pReservationItemPtr->m_guestNum)));
            this->ui->tableReservationTableWidget->item(rowCount, 1)->setTextAlignment(Qt::AlignCenter);
            auto tableReservationMapItem = tableReservationMap.find(pReservationItemPtr->m_idItem);
            // not showing action buttons when: a)has reservation for unreserved tables and b)reservation of other members
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                if (!(hasReservation)) {
                    // show reservation action
                    // only when there is no reserved table for this (date, reservationType)
                    QPushButton *pReservationButton = new QPushButton(tr("Reserve"), this->ui->tableReservationTableWidget);
                    this->connect(pReservationButton, &QPushButton::clicked, std::bind(&TableReservationView::onReservedButton_clicked, this, pReservationItemPtr->m_idItem));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 4, pReservationButton);
                }
            } else {
                // this table is reserved
                ReservationPtr pReservationPtr = tableReservationMapItem->second;
                this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(pReservationPtr->m_guestNum)));
                this->ui->tableReservationTableWidget->item(rowCount, 3)->setTextAlignment(Qt::AlignCenter);
                // do not show cancel when reservation is from Admin
                if (pReservationPtr->m_isAdmin)
                {
                    // mark row as reserved by admin
                    this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem("-"));
                    this->ui->tableReservationTableWidget->item(rowCount, 2)->setTextAlignment(Qt::AlignCenter);
                } else {
                    this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pReservationPtr->m_memberUsername)));
                    this->ui->tableReservationTableWidget->item(rowCount, 2)->setTextAlignment(Qt::AlignCenter);
                    if (pReservationPtr->m_idMember == pMemberPtr->m_id) {
                        // show cancel button action
                        QPushButton *pCancelButton = new QPushButton(tr("Cancel"), this->ui->tableReservationTableWidget);
                        this->connect(pCancelButton, &QPushButton::clicked, std::bind(&TableReservationView::onCancelButton_clicked, this, pReservationPtr->m_reservationId));
                        this->ui->tableReservationTableWidget->setCellWidget(rowCount, 4, pCancelButton);
                    }
                }

            }
            // SET ROW HEIGHT
            this->ui->tableReservationTableWidget->setRowHeight(rowCount, 41);
            rowCount++;
        }
    }
    //
    void TableReservationView::fillFireplaceReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch fireplace reservation data
        ReservationListResultPtr pFireplaceReservationListResultPtr = Singletons::m_pDAO->getFireplaceReservation(reservationType, nowDate);
        if (pFireplaceReservationListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // fetch fireplace data
        ReservationItemListResultPtr pFireplaceListResultPtr = Singletons::m_pDAO->getFireplaceList(m_currentPage, Constants::kReservationListPageCount);
        if (pFireplaceListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        ReservationItemListStatsPtr pFireplaceListStatsPtr = Singletons::m_pDAO->getFireplaceListStats();
        if (pFireplaceListStatsPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // fill fireplace data
        fillReservationsItems(pMemberPtr, pFireplaceReservationListResultPtr->m_list, pFireplaceListResultPtr->m_list, pFireplaceListStatsPtr);
    }
    //
    void TableReservationView::fillOvenReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch oven reservation data
        ReservationListResultPtr pOvenReservationListResultPtr = Singletons::m_pDAO->getOvenReservation(reservationType, nowDate);
        if (pOvenReservationListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // fetch oven data
        ReservationItemListResultPtr pOvenListResultPtr = Singletons::m_pDAO->getOvenList(m_currentPage, Constants::kReservationListPageCount);
        if (pOvenListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // fetch oven list stats
        ReservationItemListStatsPtr pOvenListStatsPtr = Singletons::m_pDAO->getOvenListStats();
        if (pOvenListStatsPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // fill oven data
        fillReservationsItems(pMemberPtr, pOvenReservationListResultPtr->m_list, pOvenListResultPtr->m_list, pOvenListStatsPtr);
    }
    //
    void TableReservationView::fillTableReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch table reservation data
        ReservationListResultPtr pTableReservationListResultPtr = Singletons::m_pDAO->getTableReservation(reservationType, nowDate);
        if (pTableReservationListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // fetch tables data
        ReservationItemListResultPtr pTableListResultPtr = Singletons::m_pDAO->getLunchTableList(m_currentPage, Constants::kReservationListPageCount);
        if (pTableListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // fetch table list stats
        ReservationItemListStatsPtr pTableListStatsPtr = Singletons::m_pDAO->getLunchTableListStats();
        if (pTableListStatsPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // fill table data
        fillReservationsItems(pMemberPtr, pTableReservationListResultPtr->m_list, pTableListResultPtr->m_list, pTableListStatsPtr);
    }
    //
    void TableReservationView::prepareTableReservationMap(ReservationMap &tableReservationMap, const ReservationListPtr &pReservationListPtr, const MemberPtr &pMemberPtr, bool &hasReservation)
    {
        hasReservation = false;
        for (auto iter = pReservationListPtr->begin(); iter != pReservationListPtr->end(); ++iter)
        {
            ReservationPtr pReservationPtr = *iter;
            tableReservationMap[pReservationPtr->m_idItem] = pReservationPtr;
            // has reservation when reservation is not Admin
            if (pReservationPtr->m_idMember == pMemberPtr->m_id && !pReservationPtr->m_isAdmin)
            {
                hasReservation = true;
            }
        }
    }
    //
    void TableReservationView::on_calendarWidget_clicked(const QDate &date)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        int reservationTypeInt = this->ui->reservationTypeButtonGroup->checkedId();
        if (reservationTypeInt == -1) {
            return;
        }

        ReservationType reservationType = static_cast<ReservationType>(reservationTypeInt);
        m_currentPage = 0;


        int reservationItemTypeInt = this->ui->reservationItemButtonGroup->checkedId();
        if (reservationItemTypeInt == -1) {
            return;
        }

        ReservationItemType reservationItemType = static_cast<ReservationItemType>(reservationItemTypeInt);
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, date, reservationType);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, date, reservationType);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, date, reservationType);
                break;
            default:
                break;
        }
    }
    //
    void TableReservationView::onReservedButton_clicked(int itemId)
    {
        ReservationItemType reservationItemType = static_cast<ReservationItemType>(this->ui->reservationItemButtonGroup->checkedId());

        if (reservationItemType == ReservationItemType::LunchTableType)
        {
            Singletons::m_pDialogManager->numItemDialog(this, tr("Number of guests?"),
                    std::bind(&TableReservationView::onTableItemGiven, this, itemId, _1)
                    );
            return;
        }
        reserveItems(itemId, 0);
    }
    //
    void TableReservationView::onTableItemGiven(int itemId, QString resultStr)
    {
        Uint32 guestNum = resultStr.toUInt();
        if (guestNum == 0)
        {
            return;
        }
        reserveItems(itemId, guestNum);
    }
    //
    void TableReservationView::reserveItems(int itemId, Uint32 guestNum)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate date = this->ui->calendarWidget->selectedDate();
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        ReservationItemType reservationItemType = static_cast<ReservationItemType>(this->ui->reservationItemButtonGroup->checkedId());
        bool isAdmin = false;
        bool ok = false;
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                ok = Singletons::m_pDAO->makeTableReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId, isAdmin);
                break;
            case ReservationItemType::OvenType:
                ok = Singletons::m_pDAO->makeOvenReservation(date, reservationType, pCurrMemberPtr->m_id, itemId, isAdmin);
                break;
            case ReservationItemType::FireplaceType:
                ok = Singletons::m_pDAO->makeFireplaceReservation(date, reservationType, pCurrMemberPtr->m_id, itemId, isAdmin);
                break;
            default:
                break;
        }

        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        QLocale enLocale = QLocale("en");
        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kReservation,
                QString("reserved %1, itemid %2, %3 %4").arg(GetStringFromReservationItemTypeEnum(reservationItemType)).arg(itemId).arg(GetStringFromReservationTypeEnum(reservationType)).arg(enLocale.toString(date)));
        Singletons::m_pDialogManager->infoMessageBox(this,
                tr("Reserved %1 at %2").arg(GetStringFromReservationItemTypeEnum(reservationItemType, true)).arg(GetStringFromReservationTypeEnum(reservationType, true)),
                std::bind(&TableReservationView::onReserved, this, reservationItemType, date, reservationType)
                );
    }
    //
    void TableReservationView::onReserved(ReservationItemType reservationItemType, QDate reservationDate, ReservationType reservationType)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        // currentPage does not need to be changed
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, reservationDate, reservationType);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, reservationDate, reservationType);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, reservationDate, reservationType);
                break;
            default:
                break;
        }
    }
    //
    void TableReservationView::onCancelButton_clicked(int reservationId)
    {
        bool ok = false;
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        ReservationItemType reservationItemType = static_cast<ReservationItemType>(this->ui->reservationItemButtonGroup->checkedId());
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                ok = Singletons::m_pDAO->cancelTableReservation(reservationId);
                break;
            case ReservationItemType::OvenType:
                ok = Singletons::m_pDAO->cancelOvenReservation(reservationId);
                break;
            case ReservationItemType::FireplaceType:
                ok = Singletons::m_pDAO->cancelFireplaceReservation(reservationId);
                break;
            default:
                break;
        }
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        QLocale enLocale = QLocale("en");
        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kReservation,
                QString("canceled %1, reservationid %2, %3 %4").arg(GetStringFromReservationItemTypeEnum(reservationItemType)).arg(reservationId).arg(GetStringFromReservationTypeEnum(reservationType)).arg(enLocale.toString(date)));
        Singletons::m_pDialogManager->infoMessageBox(this,
                tr("Cancelled %1 at %2").arg(GetStringFromReservationItemTypeEnum(reservationItemType, true)).arg(GetStringFromReservationTypeEnum(reservationType, true)),
                std::bind(&TableReservationView::onCancel, this, reservationItemType, date, reservationType)
                );
    }
    //
    void TableReservationView::onCancel(ReservationItemType reservationItemType, QDate reservationDate, ReservationType reservationType)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        // currentPage does not need to be changed
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, reservationDate, reservationType);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, reservationDate, reservationType);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, reservationDate, reservationType);
                break;
            default:
                break;
        }
    }
    //
    void TableReservationView::on_lunchButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }
        int reservationItemTypeInt = this->ui->reservationItemButtonGroup->checkedId();
        if (reservationItemTypeInt == -1) {
            return;
        }

        ReservationItemType reservationItemType = static_cast<ReservationItemType>(reservationItemTypeInt);

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        m_currentPage = 0;
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, date, ReservationType::Lunch);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, date, ReservationType::Lunch);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, date, ReservationType::Lunch);
                break;
            default:
                break;
        }
    }
    //
    void TableReservationView::on_dinnerButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }
        int reservationItemTypeInt = this->ui->reservationItemButtonGroup->checkedId();
        if (reservationItemTypeInt == -1) {
            return;
        }

        ReservationItemType reservationItemType = static_cast<ReservationItemType>(reservationItemTypeInt);

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        m_currentPage = 0;
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, date, ReservationType::Dinner);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, date, ReservationType::Dinner);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, date, ReservationType::Dinner);
                break;
            default:
                break;
        }
    }

    void TableReservationView::on_newinvoiceButton_clicked()
    {
        //call new invoice window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }

    void TableReservationView::on_invoicesPushButton_clicked()
    {
        // call invoices window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }

    void TableReservationView::on_accountButton_clicked()
    {
        // call account window
        m_switchCentralWidgetCallback(WindowKey::kAccountViewWindowKey);
    }

    void TableReservationView::on_depositsButton_clicked()
    {
        // call deposits window
        m_switchCentralWidgetCallback(WindowKey::kDepositsWindowKey);
    }

    void TableReservationView::on_exitButton_clicked()
    {
        // call login window on exit
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
    //
    void TableReservationView::on_prevPagePushButton_clicked()
    {
        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        ReservationItemType reservationItemType = static_cast<ReservationItemType>(this->ui->reservationItemButtonGroup->checkedId());
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        m_currentPage--;
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, date, reservationType);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, date, reservationType);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, date, reservationType);
                break;
            default:
                break;
        }
    }
    //
    void TableReservationView::on_nextPagePushButton_clicked()
    {
        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        ReservationItemType reservationItemType = static_cast<ReservationItemType>(this->ui->reservationItemButtonGroup->checkedId());
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        m_currentPage++;
        switch (reservationItemType)
        {
            case ReservationItemType::LunchTableType:
                fillTableReservations(pCurrMemberPtr, date, reservationType);
                break;
            case ReservationItemType::OvenType:
                fillOvenReservations(pCurrMemberPtr, date, reservationType);
                break;
            case ReservationItemType::FireplaceType:
                fillFireplaceReservations(pCurrMemberPtr, date, reservationType);
                break;
            default:
                break;
        }
    }
    //
    void TableReservationView::on_tablePushButton_clicked()
    {
        int reservationTypeInt = this->ui->reservationTypeButtonGroup->checkedId();
        if (reservationTypeInt == -1) {
            return;
        }
        ReservationType reservationType = static_cast<ReservationType>(reservationTypeInt);

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        m_currentPage = 0;
        fillTableReservations(pCurrMemberPtr, date, reservationType);
    }
    //
    void TableReservationView::on_ovenPushButton_clicked()
    {
        int reservationTypeInt = this->ui->reservationTypeButtonGroup->checkedId();
        if (reservationTypeInt == -1) {
            return;
        }
        ReservationType reservationType = static_cast<ReservationType>(reservationTypeInt);
        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        m_currentPage = 0;
        fillOvenReservations(pCurrMemberPtr, date, reservationType);
    }
    //
    void TableReservationView::on_fireplacePushButton_clicked()
    {
        int reservationTypeInt = this->ui->reservationTypeButtonGroup->checkedId();
        if (reservationTypeInt == -1) {
            return;
        }
        ReservationType reservationType = static_cast<ReservationType>(reservationTypeInt);
        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        m_currentPage = 0;
        fillFireplaceReservations(pCurrMemberPtr, date, reservationType);
    }
}

