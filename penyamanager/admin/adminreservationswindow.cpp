//

#include <QMessageBox>

#include <commons/numitemdialog.h>
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
        this->ui->reservationTypeButtonGroup->setId(this->ui->midMorningButton, static_cast<Int32>(ReservationType::MidMorning));
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
        this->ui->reservationTypeButtonGroup->setId(this->ui->supperButton, static_cast<Int32>(ReservationType::Supper));
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        initializeTable();
        this->ui->calendarWidget->setLocale(Singletons::m_translationManager.getLocale());
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
        this->ui->calendarWidget->setLocale(Singletons::m_translationManager.getLocale());
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
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QDate nowDate = nowDateTime.date();
        this->ui->calendarWidget->setSelectedDate(nowDate);
        // set minimum selectable date
        this->ui->calendarWidget->setMinimumDate(nowDate);
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
        fillReservations(nowDate, ReservationType::Lunch);
    }
    //
    void AdminReservationsWindow::fillReservations(const QDate &date, ReservationType reservationType)
    {
        // fetch table reservation data
        ReservationListResultPtr pTableReservationListResultPtr = Singletons::m_pDAO->getTableReservation(reservationType, date);
        if (pTableReservationListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // fetch tables data
        ReservationItemListResultPtr pTableListResultPtr = Singletons::m_pDAO->getAllLunchTableList();
        if (pTableListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        // fetch oven reservation data
        ReservationListResultPtr pOvenReservationListResultPtr = Singletons::m_pDAO->getOvenReservation(reservationType, date);
        if (pOvenReservationListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // fetch oven data
        ReservationItemListResultPtr pOvenListResultPtr = Singletons::m_pDAO->getAllOvenList();
        if (pOvenListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        // fetch fireplace reservation data
        ReservationListResultPtr pFireplaceReservationListResultPtr = Singletons::m_pDAO->getFireplaceReservation(reservationType, date);
        if (pFireplaceReservationListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // fetch fireplace data
        ReservationItemListResultPtr pFireplaceListResultPtr = Singletons::m_pDAO->getAllFireplaceList();
        if (pFireplaceListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        Uint32 totalSize = pTableListResultPtr->m_list->size() + pOvenListResultPtr->m_list->size() + pFireplaceReservationListResultPtr->m_list->size();
        // table
        this->ui->tableReservationTableWidget->setRowCount(totalSize);

        // invoice table reset
        this->ui->tableReservationTableWidget->clearContents();
        Uint32 rowCount = 0;
        // fill table data
        fillReservationsItems(pTableReservationListResultPtr->m_list, pTableListResultPtr->m_list, rowCount,
                std::bind(&AdminReservationsWindow::on_new_table_reservation_button_clicked, this, _1),
                std::bind(&AdminReservationsWindow::on_update_table_reservation_button_clicked, this, _1)
                );
        // fill oven data
        fillReservationsItems(pOvenReservationListResultPtr->m_list, pOvenListResultPtr->m_list, rowCount,
                std::bind(&AdminReservationsWindow::on_new_oven_reservation_button_clicked, this, _1),
                std::bind(&AdminReservationsWindow::on_update_oven_reservation_button_clicked, this, _1)
                );

        // fill fireplace data
        fillReservationsItems(pFireplaceReservationListResultPtr->m_list, pFireplaceListResultPtr->m_list, rowCount,
                std::bind(&AdminReservationsWindow::on_new_fireplace_reservation_button_clicked, this, _1),
                std::bind(&AdminReservationsWindow::on_update_fireplace_reservation_button_clicked, this, _1)
                );

    }
    //
    void AdminReservationsWindow::fillReservationsItems(
            const ReservationListPtr &pReservationListPtr,
            const ReservationItemListPtr &pReservationItemListPtr,
            Uint32 &rowCount,
            ReservationCallback newReservationCallback,
            ReservationCallback updateReservationCallback
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
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(getStringFromReservationTypeEnum(pReservationItemPtr->m_itemType)));
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pReservationItemPtr->m_itemName));
            this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pReservationItemPtr->m_guestNum)));
            auto tableReservationMapItem = tableReservationMap.find(pReservationItemPtr->m_idItem);
            // not showing action buttons when: a)has reservation for unreserved tables and b)reservation of other members
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                // show reservation action
                QPushButton *pReservationButton = new QPushButton(tr("Reserve"), this->ui->tableReservationTableWidget);
                this->connect(pReservationButton, &QPushButton::clicked, std::bind(newReservationCallback, pReservationItemPtr->m_idItem));
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
                    this->connect(pCancelButton, &QPushButton::clicked, std::bind(&AdminReservationsWindow::on_cancelButton_clicked, this, pReservationPtr->m_reservationId, pReservationItemPtr->m_itemType));
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
    void AdminReservationsWindow::on_midMorningButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, ReservationType::MidMorning);
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
    void AdminReservationsWindow::on_supperButton_clicked(bool checked)
    {
        if (!checked) {
            // discard event of unchecked button
            return;
        }

        QDate date = this->ui->calendarWidget->selectedDate();
        fillReservations(date, ReservationType::Supper);
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
    void AdminReservationsWindow::on_new_table_reservation_button_clicked(int itemId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        Uint32 guestNum = numItemDialog.getKey();
        if (guestNum == 0)
        {
            return;
        }

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        bool isAdmin = true;
        QString title = "Table";
        bool ok = Singletons::m_pDAO->makeTableReservation(date, reservationType, guestNum, pCurrMemberPtr->m_id, itemId, isAdmin);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("%1 %2").arg(title).arg(itemId));
        QMessageBox::information(this, title, tr("Reservation done"));
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::on_update_table_reservation_button_clicked(int reservationId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        Uint32 guestNum = numItemDialog.getKey();
        if (guestNum == 0)
        {
            return;
        }

        bool isAdmin = true;
        QString title = "Table";
        bool ok = Singletons::m_pDAO->updateTableReservation(reservationId, isAdmin);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("[BLOCKED] %1 %2").arg(title).arg(reservationId));
        QMessageBox::information(this, title, tr("Reservation done"));
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::on_new_fireplace_reservation_button_clicked(int itemId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        bool isAdmin = true;
        QString title = "Fireplace";
        bool ok = Singletons::m_pDAO->makeFireplaceReservation(date, reservationType, pCurrMemberPtr->m_id, itemId, isAdmin);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("%1 %2").arg(title).arg(itemId));
        QMessageBox::information(this, title, tr("Reservation done"));
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::on_update_fireplace_reservation_button_clicked(int reservationId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();
        bool isAdmin = true;
        QString title = "Fireplace";
        bool ok = Singletons::m_pDAO->updateFireplaceReservation(reservationId, isAdmin);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("[BLOCKED] %1 %2").arg(title).arg(reservationId));
        QMessageBox::information(this, title, tr("Reservation done"));
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::on_new_oven_reservation_button_clicked(int itemId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        bool isAdmin = true;
        QString title = "Oven";
        bool ok = Singletons::m_pDAO->makeOvenReservation(date, reservationType, pCurrMemberPtr->m_id, itemId, isAdmin);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("%1 %2").arg(title).arg(itemId));
        QMessageBox::information(this, title, tr("Reservation done"));
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::on_update_oven_reservation_button_clicked(int reservationId)
    {
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
        QDate date = this->ui->calendarWidget->selectedDate();

        bool isAdmin = true;
        QString title = "Oven";
        bool ok = Singletons::m_pDAO->updateOvenReservation(reservationId, isAdmin);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kReservation,
                QString("[BLOCKED] %1 %2").arg(title).arg(reservationId));
        QMessageBox::information(this, title, tr("Reservation done"));
        fillReservations(date, reservationType);
    }
    //
    void AdminReservationsWindow::on_cancelButton_clicked(int reservationId, ReservationItemType itemType)
    {
        QDate date = this->ui->calendarWidget->selectedDate();
        ReservationType reservationType = static_cast<ReservationType>(this->ui->reservationTypeButtonGroup->checkedId());
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
        QMessageBox::information(this, title, tr("Reservation cancelled"));
        fillReservations(date, reservationType);
    }
}

