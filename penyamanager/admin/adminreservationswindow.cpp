//

#include <commons/singletons.h>
#include "adminreservationswindow.h"
#include "ui_adminreservationswindow.h"

namespace PenyaManager {
    //
    AdminReservationsWindow::AdminReservationsWindow(QWidget *parent):
        IPartner(parent),
        ui(new Ui::AdminReservationsWindow)
    {
        ui->setupUi(this);
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        initializeTable();
        this->ui->calendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    AdminReservationsWindow::~AdminReservationsWindow()
    {
        delete ui;
    }
    //
    void AdminReservationsWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->calendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    void AdminReservationsWindow::translateTable()
    {
        // table reservation table Header
        QStringList headers;
        headers.append(tr("Type"));
        headers.append(tr("Name"));
        headers.append(tr("Size"));
        headers.append(tr("Reserved By Guest"));
        headers.append(tr("# reserved"));
        headers.append(tr("Action"));
        this->ui->tableReservationTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void AdminReservationsWindow::initializeTable()
    {
        // table
        this->ui->tableReservationTableWidget->setColumnCount(6);
        translateTable();
        Uint32 column = 0;
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 150);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 80);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 100);
        this->ui->tableReservationTableWidget->setColumnWidth(column++, 200);
    }
    //
    void AdminReservationsWindow::init()
    {
        //
        // Loading User profile
        //
        //MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;

        //
        // Initial state
        //
        initializeCalendar();
    }
    //
    void AdminReservationsWindow::initializeCalendar()
    {
        // this date should be localized
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QDate nowDate = nowDateTime.date();
        this->ui->calendarWidget->setSelectedDate(nowDate);
        // set minimum selectable date
        this->ui->calendarWidget->setMinimumDate(nowDate);
        // reservation type (lunch,dinner) buttons
        this->ui->lunchButton->setEnabled(true);
        this->ui->dinnerButton->setEnabled(true);
        this->ui->lunchButton->setCheckable(true);
        this->ui->dinnerButton->setCheckable(true);
        this->ui->lunchButton->setChecked(true);
        this->ui->dinnerButton->setChecked(false);
        this->ui->calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
        fillReservations(nowDate, ReservationType::Lunch);
    }
    //
    void AdminReservationsWindow::fillReservations(const QDate &date, ReservationType reservationType)
    {
        // fetch table reservation data
        ReservationListResultPtr pTableReservationListResultPtr = Singletons::m_pDAO->getTableReservation(reservationType, date);
        if (pTableReservationListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // fetch tables data
        ReservationItemListResultPtr pTableListResultPtr = Singletons::m_pDAO->getAllLunchTableList();
        if (pTableListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Uint32 totalSize = pTableListResultPtr->m_list->size();
        // table
        this->ui->tableReservationTableWidget->setRowCount(totalSize);

        // invoice table reset
        this->ui->tableReservationTableWidget->clearContents();
        Uint32 rowCount = 0;
        // fill table data
        fillReservationsItems(pTableReservationListResultPtr->m_list, pTableListResultPtr->m_list, rowCount,
                std::bind(&AdminReservationsWindow::onNew_table_reservation_button_clicked, this, _1, _2),
                std::bind(&AdminReservationsWindow::onUpdate_table_reservation_button_clicked, this, _1)
                );
    }
    //
    void AdminReservationsWindow::fillReservationsItems(
            const ReservationListPtr &pReservationListPtr,
            const ReservationItemListPtr &pReservationItemListPtr,
            Uint32 &rowCount,
            const NewReservationCallback newReservationCallback,
            const UpdateReservationCallback updateReservationCallback
            )
    {
        ReservationMap tableReservationMap;
        for (auto iter = pReservationListPtr->begin(); iter != pReservationListPtr->end(); ++iter)
        {
            ReservationPtr pReservationPtr = *iter;
            tableReservationMap[pReservationPtr->m_idItem] = pReservationPtr;
        }
        // fill data
        for (ReservationItemList::iterator iter = pReservationItemListPtr->begin(); iter != pReservationItemListPtr->end(); ++iter) {
            ReservationItemPtr pReservationItemPtr = *iter;
            this->ui->tableReservationTableWidget->setRowHeight(rowCount, 50);
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(GetStringFromReservationItemTypeEnum(pReservationItemPtr->m_itemType, true)));
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pReservationItemPtr->m_itemName));
            this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pReservationItemPtr->m_guestNum)));
            auto tableReservationMapItem = tableReservationMap.find(pReservationItemPtr->m_idItem);
            // not showing action buttons when: a)has reservation for unreserved tables and b)reservation of other members
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                // show reservation action
                QPushButton *pReservationButton = new QPushButton(tr("Reserve"), this->ui->tableReservationTableWidget);
                this->connect(pReservationButton, &QPushButton::clicked, std::bind(newReservationCallback, pReservationItemPtr->m_idItem, pReservationItemPtr->m_guestNum));
                this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pReservationButton);
            } else {
                // this table is reserved
                ReservationPtr pReservationPtr = tableReservationMapItem->second;
                this->ui->tableReservationTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(pReservationPtr->m_guestNum)));
                // do not show cancel when reservation is from Admin
                if (pReservationPtr->m_isAdmin) {
                    this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString(tr("BLOCKED"))));
                    // show cancel button action
                    QPushButton *pCancelButton = new QPushButton(tr("Cancel"), this->ui->tableReservationTableWidget);
                    this->connect(pCancelButton, &QPushButton::clicked, std::bind(&AdminReservationsWindow::onCancelButton_clicked, this, pReservationPtr->m_reservationId));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pCancelButton);
                } else {
                    QString guestName = QString("%1 %2 %3").arg(pReservationPtr->m_memberName).arg(pReservationPtr->m_memberSurname1).arg(pReservationPtr->m_memberSurname2);
                    this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(guestName));
                    QPushButton *pReservationButton = new QPushButton(tr("Reserve"), this->ui->tableReservationTableWidget);
                    this->connect(pReservationButton, &QPushButton::clicked, std::bind(updateReservationCallback, pReservationPtr->m_reservationId));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pReservationButton);
                }
            }
            rowCount++;
        }
    }
    void AdminReservationsWindow::on_lunchButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, ReservationType::Lunch);
    }
    //
    void AdminReservationsWindow::on_dinnerButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, ReservationType::Dinner);
    }
    void AdminReservationsWindow::on_calendarWidget_clicked(const QDate &date)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::onNew_table_reservation_button_clicked(int itemId, int guestNum)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        bool isAdmin = true;
        bool ok = Singletons::m_pDAO->makeTableReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId, isAdmin);
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        QLocale enLocale = QLocale("en");
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("reserved table, itemid %1, %2 %3").arg(itemId).arg(GetStringFromReservationTypeEnum(reservationType)).arg(enLocale.toString(date)));
        Singletons::m_pDialogManager->infoMessageBoxTitled(this,
                tr("Reserved %1 at %2").arg(GetStringFromReservationItemTypeEnum(ReservationItemType::LunchTableType, true)).arg(GetStringFromReservationTypeEnum(reservationType, true)),
                std::bind(&AdminReservationsWindow::onTableReservationDone, this)
                );
        // nothing should be added here
    }
    //
    void AdminReservationsWindow::onTableReservationDone()
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::onUpdate_table_reservation_button_clicked(int reservationId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        bool isAdmin = true;
        bool ok = Singletons::m_pDAO->updateTableReservation(reservationId, isAdmin);
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        QLocale enLocale = QLocale("en");
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("blocked table, reservationid %1 %2 on %3").arg(reservationId).arg(GetStringFromReservationTypeEnum(reservationType)).arg(enLocale.toString(date)));
        Singletons::m_pDialogManager->infoMessageBoxTitled(this,
                tr("Reserved %1 at %2").arg(GetStringFromReservationItemTypeEnum(ReservationItemType::LunchTableType, true)).arg(GetStringFromReservationTypeEnum(reservationType, true)),
                std::bind(&AdminReservationsWindow::onTableReservationUpdateDone, this)
                );
        // nothing should be added here
    }
    //
    void AdminReservationsWindow::onTableReservationUpdateDone()
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::onCancelButton_clicked(int reservationId)
    {
        QDate date = this->ui->calendarWidget->selectedDate();
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        bool ok = Singletons::m_pDAO->cancelTableReservation(reservationId);
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        QLocale enLocale = QLocale("en");
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("canceled %1, reservationid %2, %3 %4").arg(GetStringFromReservationItemTypeEnum(ReservationItemType::LunchTableType)).arg(reservationId).arg(GetStringFromReservationTypeEnum(reservationType)).arg(enLocale.toString(date)));
        Singletons::m_pDialogManager->infoMessageBoxTitled(this,
                tr("Cancelled %1 at %2").arg(GetStringFromReservationItemTypeEnum(ReservationItemType::LunchTableType, true)).arg(GetStringFromReservationTypeEnum(reservationType, true)),
                std::bind(&AdminReservationsWindow::onTableReservationCancelled, this)
                );
    }
    //
    void AdminReservationsWindow::onTableReservationCancelled()
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, reservationType);
    }
}

