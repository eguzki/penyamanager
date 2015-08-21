//

#include <QMessageBox>
#include <QPushButton>

#include <QsLog.h>

#include "utils.h"
#include "numitemdialog.h"
#include "singletons.h"
#include "tablereservationview.h"
#include "ui_tablereservationview.h"

namespace PenyaManager {
    // Rules:
    // * One member, one reservation in a given (day, reservationtype {lunch, dinner})
    // * Reservations can be done only for the current week days
    // * Reservations are available since Monday 06:00AM till Sunday 23:59PM
    // * Reservations can be cancelled

    //
    TableReservationView::TableReservationView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::TableReservationView),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
        initializeTable();
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
    }
    //
    void TableReservationView::initializeTable()
    {
        // table
        this->ui->tableReservationTableWidget->setColumnCount(6);

        // table reservation table Header
        QStringList headers;
        headers.append("Type");
        headers.append("Name");
        headers.append("Size");
        headers.append("Reserved By Guest");
        headers.append("# reserved");
        headers.append("Action");

        Uint32 column = 0;
        this->ui->tableReservationTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 250);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 80);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 300);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 80);
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

        //
        // Show
        //
        show();
    }
    //
    void TableReservationView::on_backButton_clicked()
    {
        // call main window
        switchWindow(WindowKey::kMainWindowKey);
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
            // reservation type (lunch/dinner) buttons
            this->ui->lunchButton->setEnabled(false);
            this->ui->dinnerButton->setEnabled(false);
        } else {
            // reservation type (lunch/dinner) buttons
            this->ui->lunchButton->setEnabled(true);
            this->ui->dinnerButton->setEnabled(true);
            this->ui->lunchButton->setCheckable(true);
            this->ui->dinnerButton->setCheckable(true);
            this->ui->lunchButton->setChecked(true);
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
            this->ui->tableReservationTableWidget->setRowHeight(rowCount, 50);
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(getStringFromReservationTypeEnum(pReservationItemPtr->m_itemType)));
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pReservationItemPtr->m_itemName));
            this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pReservationItemPtr->m_guestNum)));
            auto tableReservationMapItem = tableReservationMap.find(pReservationItemPtr->m_idItem);
            // not showing action buttons when: a)has reservation for unreserved tables and b)reservation of other members
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                if (!hasReservation) {
                    // show reservation action
                    // only when there is no reserved table for this (date, reservationType)
                    QPushButton *pReservationButton = new QPushButton("Reserve", this->ui->tableReservationTableWidget);
                    this->connect(pReservationButton, &QPushButton::clicked, std::bind(&TableReservationView::on_reservedButton_clicked, this, pReservationItemPtr->m_idItem, pReservationItemPtr->m_itemType));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pReservationButton);
                }
            } else {
                // this table is reserved
                ReservationPtr pReservationPtr = tableReservationMapItem->second;
                QString guestName = QString("[%1] %2 %3").arg(pReservationPtr->m_idMember).arg(pReservationPtr->m_memberName).arg(pReservationPtr->m_memberSurname);
                this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(guestName));
                this->ui->tableReservationTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(pReservationPtr->m_guestNum)));
                if (pReservationPtr->m_idMember == pMemberPtr->m_id) {
                    // show cancel button action
                    QPushButton *pCancelButton = new QPushButton("Cancel", this->ui->tableReservationTableWidget);
                    this->connect(pCancelButton, &QPushButton::clicked, std::bind(&TableReservationView::on_cancelButton_clicked, this, pReservationPtr->m_reservationId, pReservationItemPtr->m_itemType));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pCancelButton);
                }
            }
            rowCount++;
        }
    }
    //
    void TableReservationView::fillTableReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch table reservation data
        ReservationListPtr pTableReservationListPtr = Singletons::m_pDAO->getTableReservation(reservationType, nowDate);
        // fetch tables data
        ReservationItemListPtr pTableListPtr = Singletons::m_pDAO->getLunchTableList();

        // fetch oven reservation data
        ReservationListPtr pOvenReservationListPtr = Singletons::m_pDAO->getOvenReservation(reservationType, nowDate);
        // fetch oven data
        ReservationItemListPtr pOvenListPtr = Singletons::m_pDAO->getOvenList();

        // fetch fireplace reservation data
        ReservationListPtr pFireplaceReservationListPtr = Singletons::m_pDAO->getFireplaceReservation(reservationType, nowDate);
        // fetch fireplace data
        ReservationItemListPtr pFireplaceListPtr = Singletons::m_pDAO->getFireplaceList();

        Uint32 totalSize = pTableListPtr->size() + pOvenListPtr->size() + pFireplaceListPtr->size();
        // table
        this->ui->tableReservationTableWidget->setRowCount(totalSize);

        // invoice table reset
        this->ui->tableReservationTableWidget->clearContents();
        Uint32 rowCount = 0;
        // fill table data
        fillReservationsItems(pMemberPtr, pTableReservationListPtr, pTableListPtr, rowCount);
        // fill oven data
        fillReservationsItems(pMemberPtr, pOvenReservationListPtr, pOvenListPtr, rowCount);
        // fill fireplace data
        fillReservationsItems(pMemberPtr, pFireplaceReservationListPtr, pFireplaceListPtr, rowCount);
    }
    //
    void TableReservationView::prepareTableReservationMap(ReservationMap &tableReservationMap, const ReservationListPtr &pReservationListPtr, const MemberPtr &pMemberPtr, bool &hasReservation)
    {
        hasReservation = false;
        for (auto iter = pReservationListPtr->begin(); iter != pReservationListPtr->end(); ++iter)
        {
            ReservationPtr pReservationPtr = *iter;
            tableReservationMap[pReservationPtr->m_idItem] = pReservationPtr;
            if (pReservationPtr->m_idMember == pMemberPtr->m_id)
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
        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        Uint32 guestNum = numItemDialog.getKey();
        if (guestNum == 0) 
        {
            return;
        }

        QString title;
        switch (itemType)
        {
            case ReservationItemType::LunchTableType:
                title = "Table reservation";
                Singletons::m_pDAO->makeTableReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId);
                break;
            case ReservationItemType::OvenType:
                title = "Oven reservation";
                Singletons::m_pDAO->makeOvenReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId);
                break;
            case ReservationItemType::FireplaceType:
                title = "Fireplace reservation";
                Singletons::m_pDAO->makeFireplaceReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId);
                break;
            default:
                break;
        }

        QLOG_INFO() << QString("[%1] User %2 item %3").arg(title).arg(pCurrMemberPtr->m_id).arg(itemId);
        QMessageBox::information(this, title, "Reservation done");
        // call main window
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void TableReservationView::on_cancelButton_clicked(int reservationId, ReservationItemType itemType)
    {
        QString title;
        switch (itemType)
        {
            case ReservationItemType::LunchTableType:
                title = "Table reservation";
                Singletons::m_pDAO->cancelTableReservation(reservationId);
                break;
            case ReservationItemType::OvenType:
                title = "Oven reservation";
                Singletons::m_pDAO->cancelOvenReservation(reservationId);
                break;
            case ReservationItemType::FireplaceType:
                title = "Fireplace reservation";
                Singletons::m_pDAO->cancelFireplaceReservation(reservationId);
                break;
            default:
                break;
        }
        QMessageBox::information(this, title, "Reservation cancelled");
        // call main window
        switchWindow(WindowKey::kMainWindowKey);
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

