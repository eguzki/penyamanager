//

#include <QMessageBox>
#include <QPushButton>

#include <QsLog.h>

#include <commons/utils.h>
#include <commons/singletons.h>
#include <commons/numitemdialog.h>
#include "tablereservationview.h"
#include "ui_tablereservationview.h"

namespace PenyaManager {
    // Rules:
    // * One member, one reservation in a given (day, reservationtype {mid-morning, lunch, supper, dinner})
    // * Reservations can be done only for the current week days
    // * Reservations are available since Monday 06:00AM till Sunday 23:59PM
    // * Reservations can be cancelled

    //
    TableReservationView::TableReservationView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::TableReservationView),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        this->ui->reservationTypeButtonGroup->setId(this->ui->midMorningButton, static_cast<Int32>(ReservationType::MidMorning));
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
        this->ui->reservationTypeButtonGroup->setId(this->ui->supperButton, static_cast<Int32>(ReservationType::Supper));
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        initializeTable();
        this->ui->calendarWidget->setLocale(Singletons::m_translationManager.getLocale());
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
        translateTable();
        this->ui->calendarWidget->setLocale(Singletons::m_translationManager.getLocale());
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
        headers.append(tr("Action"));
        this->ui->tableReservationTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void TableReservationView::initializeTable()
    {
        // table
        this->ui->tableReservationTableWidget->setColumnCount(5);
        translateTable();
        Uint32 column = 0;
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 80);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 100);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
    }
    //
    void TableReservationView::init()
    {
        //
        // Loading User profile
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        //
        // Initial state
        //
        initializeTableReservations(pCurrMemberPtr);
    }
    //
    void TableReservationView::on_backButton_clicked()
    {
        // Go to dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void TableReservationView::initializeTableReservations(const MemberPtr &pCurrMemberPtr)
    {
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 11), QTime(0,0)); // when reservations cannot be done
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 11), QTime(7,0)); // monday after deadline
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 17), QTime(7,0)); // sunday (same day min and max)
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QDate nowDate = nowDateTime.date();

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
            // reservation type (midmorning,lunch,supper,dinner) buttons
            this->ui->midMorningButton->setEnabled(false);
            this->ui->lunchButton->setEnabled(false);
            this->ui->supperButton->setEnabled(false);
            this->ui->dinnerButton->setEnabled(false);
        } else {
            // reservation type (midmorning,lunch,supper,dinner) buttons
            this->ui->midMorningButton->setEnabled(true);
            this->ui->lunchButton->setEnabled(true);
            this->ui->supperButton->setEnabled(true);
            this->ui->dinnerButton->setEnabled(true);
            this->ui->midMorningButton->setCheckable(true);
            this->ui->lunchButton->setCheckable(true);
            this->ui->supperButton->setCheckable(true);
            this->ui->dinnerButton->setCheckable(true);
            this->ui->midMorningButton->setChecked(false);
            this->ui->lunchButton->setChecked(true);
            this->ui->supperButton->setChecked(false);
            this->ui->dinnerButton->setChecked(false);
            this->ui->calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
            fillTableReservations(pCurrMemberPtr, nowDate, ReservationType::Lunch);
        }
    }
    //
    void TableReservationView::fillReservationsItems(const MemberPtr &pMemberPtr, const ReservationListPtr &pReservationListPtr, const ReservationItemListPtr &pReservationItemListPtr, Uint32 &rowCount)
    {
        bool hasReservation = false;
        // create map structure for easy and efficient lookup
        ReservationMap tableReservationMap;
        prepareTableReservationMap(tableReservationMap, pReservationListPtr, pMemberPtr, hasReservation);

        // fill data
        for (ReservationItemList::iterator iter = pReservationItemListPtr->begin(); iter != pReservationItemListPtr->end(); ++iter) {
            ReservationItemPtr pReservationItemPtr = *iter;
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pReservationItemPtr->m_itemName));
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(pReservationItemPtr->m_guestNum)));
            auto tableReservationMapItem = tableReservationMap.find(pReservationItemPtr->m_idItem);
            // not showing action buttons when: a)has reservation for unreserved tables and b)reservation of other members
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                if (!hasReservation) {
                    // show reservation action
                    // only when there is no reserved table for this (date, reservationType)
                    QPushButton *pReservationButton = new QPushButton(tr("Reserve"), this->ui->tableReservationTableWidget);
                    this->connect(pReservationButton, &QPushButton::clicked, std::bind(&TableReservationView::on_reservedButton_clicked, this, pReservationItemPtr->m_idItem, pReservationItemPtr->m_itemType));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 4, pReservationButton);
                }
            } else {
                // this table is reserved
                ReservationPtr pReservationPtr = tableReservationMapItem->second;
                this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(pReservationPtr->m_guestNum)));
                // do not show cancel when reservation is from Admin
                if (pReservationPtr->m_isAdmin)
                {
                    this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString(tr("BLOCKED"))));
                } else
                {
                    QString guestName = QString("%1 %2 %3").arg(pReservationPtr->m_memberName).arg(pReservationPtr->m_memberSurname1).arg(pReservationPtr->m_memberSurname2);
                    this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(guestName));
                    if (pReservationPtr->m_idMember == pMemberPtr->m_id) {
                        // show cancel button action
                        QPushButton *pCancelButton = new QPushButton(tr("Cancel"), this->ui->tableReservationTableWidget);
                        this->connect(pCancelButton, &QPushButton::clicked, std::bind(&TableReservationView::on_cancelButton_clicked, this, pReservationPtr->m_reservationId, pReservationItemPtr->m_itemType));
                        this->ui->tableReservationTableWidget->setCellWidget(rowCount, 4, pCancelButton);
                    }
                }

            }
            rowCount++;
        }
    }
    //
    void TableReservationView::fillTableReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch table reservation data
        ReservationListResultPtr pTableReservationListResultPtr = Singletons::m_pDAO->getTableReservation(reservationType, nowDate);
        if (pTableReservationListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // fetch tables data
        ReservationItemListResultPtr pTableListResultPtr = Singletons::m_pDAO->getLunchTableList();
        if (pTableListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        // fetch oven reservation data
        ReservationListResultPtr pOvenReservationListResultPtr = Singletons::m_pDAO->getOvenReservation(reservationType, nowDate);
        if (pOvenReservationListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // fetch oven data
        ReservationItemListResultPtr pOvenListResultPtr = Singletons::m_pDAO->getOvenList();
        if (pOvenListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        // fetch fireplace reservation data
        ReservationListResultPtr pFireplaceReservationListResultPtr = Singletons::m_pDAO->getFireplaceReservation(reservationType, nowDate);
        if (pFireplaceReservationListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // fetch fireplace data
        ReservationItemListResultPtr pFireplaceListResultPtr = Singletons::m_pDAO->getFireplaceList();
        if (pFireplaceListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        Uint32 totalSize = pTableListResultPtr->m_list->size() + pOvenListResultPtr->m_list->size() + pFireplaceListResultPtr->m_list->size();
        // table
        this->ui->tableReservationTableWidget->setRowCount(totalSize);

        // invoice table reset
        this->ui->tableReservationTableWidget->clearContents();
        Uint32 rowCount = 0;
        // fill table data
        fillReservationsItems(pMemberPtr, pTableReservationListResultPtr->m_list, pTableListResultPtr->m_list, rowCount);
        // fill oven data
        fillReservationsItems(pMemberPtr, pOvenReservationListResultPtr->m_list, pOvenListResultPtr->m_list, rowCount);
        // fill fireplace data
        fillReservationsItems(pMemberPtr, pFireplaceReservationListResultPtr->m_list, pFireplaceListResultPtr->m_list, rowCount);
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
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        fillTableReservations(pCurrMemberPtr, date, reservationType);
    }
    //
    void TableReservationView::on_reservedButton_clicked(int itemId, ReservationItemType itemType)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate date = this->ui->calendarWidget->selectedDate();
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());

        Uint32 guestNum = 0;
        if (itemType == ReservationItemType::LunchTableType)
        {
            NumItemDialog numItemDialog(this);
            numItemDialog.exec();
            guestNum = numItemDialog.getKey();
            if (guestNum == 0)
            {
                return;
            }
        }

        bool isAdmin = false;
        bool ok = false;
        QString title;
        switch (itemType)
        {
            case ReservationItemType::LunchTableType:
                title = "Table reservation";
                ok = Singletons::m_pDAO->makeTableReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId, isAdmin);
                break;
            case ReservationItemType::OvenType:
                title = "Oven reservation";
                ok = Singletons::m_pDAO->makeOvenReservation(date, reservationType, pCurrMemberPtr->m_id, itemId, isAdmin);
                break;
            case ReservationItemType::FireplaceType:
                title = "Fireplace reservation";
                ok = Singletons::m_pDAO->makeFireplaceReservation(date, reservationType, pCurrMemberPtr->m_id, itemId, isAdmin);
                break;
            default:
                break;
        }

        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        QLOG_INFO() << QString("[%1] [User %2] [item %3]").arg(title).arg(pCurrMemberPtr->m_id).arg(itemId);
        QMessageBox::information(this, title, "Reservation done");
        fillTableReservations(pCurrMemberPtr, date, reservationType);
    }
    //
    void TableReservationView::on_cancelButton_clicked(int reservationId, ReservationItemType itemType)
    {
        QString title;
        bool ok = false;
        switch (itemType)
        {
            case ReservationItemType::LunchTableType:
                title = "Table reservation";
                ok = Singletons::m_pDAO->cancelTableReservation(reservationId);
                break;
            case ReservationItemType::OvenType:
                title = "Oven reservation";
                ok = Singletons::m_pDAO->cancelOvenReservation(reservationId);
                break;
            case ReservationItemType::FireplaceType:
                title = "Fireplace reservation";
                ok = Singletons::m_pDAO->cancelFireplaceReservation(reservationId);
                break;
            default:
                break;
        }
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        QMessageBox::information(this, title, "Reservation cancelled");
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate date = this->ui->calendarWidget->selectedDate();
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        fillTableReservations(pCurrMemberPtr, date, reservationType);
    }
    //
    void TableReservationView::on_midMorningButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillTableReservations(pCurrMemberPtr, date, ReservationType::MidMorning);
    }
    //
    void TableReservationView::on_lunchButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillTableReservations(pCurrMemberPtr, date, ReservationType::Lunch);
    }
    //
    void TableReservationView::on_supperButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillTableReservations(pCurrMemberPtr, date, ReservationType::Supper);
    }
    //
    void TableReservationView::on_dinnerButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillTableReservations(pCurrMemberPtr, date, ReservationType::Dinner);
    }
}

