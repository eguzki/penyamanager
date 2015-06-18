//

#include <QMessageBox>
#include <QPushButton>

#include "objs/LunchTable.h"
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
    }
    //
    TableReservationView::~TableReservationView()
    {
        delete ui;
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
    void TableReservationView::fillTableReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch reservation data
        TableReservationListPtr pTableReservationListPtr = Singletons::m_pDAO->getTableReservation(reservationType, nowDate);

        bool hasReservation = false;
        // create map structure for easy and efficient lookup
        TableReservationMap tableReservationMap;
        prepareTableReservationMap(tableReservationMap, pTableReservationListPtr, pMemberPtr, hasReservation);

        // fetch tables data
        LunchTableListPtr pLunchTableListPtr = Singletons::m_pDAO->getLunchTableList();

        // table
        this->ui->tableReservationTableWidget->setColumnCount(6);
        this->ui->tableReservationTableWidget->setRowCount(pLunchTableListPtr->size());

        // table reservation table Header
        QStringList headers;
        headers.append("Table ID");
        headers.append("Table Name");
        headers.append("Table Size");
        headers.append("Reserved By Guest");
        headers.append("# reserved");
        headers.append("Action");

        this->ui->tableReservationTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->tableReservationTableWidget->setColumnWidth(0, 80);
        this->ui->tableReservationTableWidget->setColumnWidth(1, 250);
        this->ui->tableReservationTableWidget->setColumnWidth(2, 80);
        this->ui->tableReservationTableWidget->setColumnWidth(3, 400);
        this->ui->tableReservationTableWidget->setColumnWidth(4, 80);
        this->ui->tableReservationTableWidget->setColumnWidth(5, 200);

        // invoice table reset
        this->ui->tableReservationTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (LunchTableList::iterator iter = pLunchTableListPtr->begin(); iter != pLunchTableListPtr->end(); ++iter) {
            LunchTablePtr pLunchTablePtr = *iter;
            this->ui->tableReservationTableWidget->setRowHeight(rowCount, 50);
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pLunchTablePtr->m_idTable)));
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pLunchTablePtr->m_tableName));
            this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pLunchTablePtr->m_guestNum)));
            auto tableReservationMapItem = tableReservationMap.find(pLunchTablePtr->m_idTable);
            // not showwing action buttons when: a)has reservation for unreserved tables and b)reservation of other members
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                if (!hasReservation) {
                    // show reservation action
                    // only when there is no reserved table for this (date, reservationType)
                    QPushButton *pReservationButton = new QPushButton("Reserve", this->ui->tableReservationTableWidget);
                    this->connect(pReservationButton, &QPushButton::clicked, std::bind(&TableReservationView::on_reservedButton_clicked, this, pLunchTablePtr->m_idTable));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pReservationButton);
                }
            } else {
                // this table is reserved
                TableReservationPtr pTableReservationPtr = tableReservationMapItem->second;
                QString guestName = QString("[%1] %2 %3").arg(pTableReservationPtr->m_idMember).arg(pTableReservationPtr->m_memberName).arg(pTableReservationPtr->m_memberSurname);
                this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(guestName));
                this->ui->tableReservationTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(pTableReservationPtr->m_guestNum)));
                if (pTableReservationPtr->m_idMember == pMemberPtr->m_id) {
                    // show cancel button action
                    QPushButton *pCancelButton = new QPushButton("Cancel", this->ui->tableReservationTableWidget);
                    this->connect(pCancelButton, &QPushButton::clicked, std::bind(&TableReservationView::on_cancelButton_clicked, this, pTableReservationPtr->m_reservationId));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pCancelButton);
                }
            }
            rowCount++;
        }
    }
    //
    void TableReservationView::prepareTableReservationMap(TableReservationMap &tableReservationMap, const TableReservationListPtr &pTableReservationListPtr, const MemberPtr &pMemberPtr, bool &hasReservation)
    {
        hasReservation = false;
        for (auto iter = pTableReservationListPtr->begin(); iter != pTableReservationListPtr->end(); ++iter)
        {
            TableReservationPtr pTableReservationPtr = *iter;
            tableReservationMap[pTableReservationPtr->m_idTable] = pTableReservationPtr;
            if (pTableReservationPtr->m_idMember == pMemberPtr->m_id)
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
    void TableReservationView::on_reservedButton_clicked(int tableId)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        QDate date = this->ui->calendarWidget->selectedDate();
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        NumItemDialog numItemDialog(this);
        Uint32 guestNum = numItemDialog.exec();
        Singletons::m_pDAO->makeTableReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, tableId);
        QMessageBox::information(this, "Table reservation", "Reservation done");
        // call main window
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void TableReservationView::on_cancelButton_clicked(int reservationId)
    {
        Singletons::m_pDAO->cancelTableReservation(reservationId);
        QMessageBox::information(this, "Table reservation", "Reservation cancelled");
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

