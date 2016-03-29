//

#include <QsLog.h>
#include <commons/singletons.h>
#include "adminreservationswindow.h"
#include "ui_adminreservationswindow.h"

namespace PenyaManager {
    //

    //
    AdminReservationsWindow::AdminReservationsWindow(QWidget *parent):
        IPartner(parent),
        ui(new Ui::AdminReservationsWindow)
    {
        ui->setupUi(this);
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
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
        // reservation type (lunch/dinner) buttons
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
        ReservationListPtr pTableReservationListPtr = Singletons::m_pDAO->getTableReservation(reservationType, date);
        // fetch tables data
        ReservationItemListPtr pTableListPtr = Singletons::m_pDAO->getLunchTableList();

        // fetch oven reservation data
        ReservationListPtr pOvenReservationListPtr = Singletons::m_pDAO->getOvenReservation(reservationType, date);
        // fetch oven data
        ReservationItemListPtr pOvenListPtr = Singletons::m_pDAO->getOvenList();

        // fetch fireplace reservation data
        ReservationListPtr pFireplaceReservationListPtr = Singletons::m_pDAO->getFireplaceReservation(reservationType, date);
        // fetch fireplace data
        ReservationItemListPtr pFireplaceListPtr = Singletons::m_pDAO->getFireplaceList();

        Uint32 totalSize = pTableListPtr->size() + pOvenListPtr->size() + pFireplaceListPtr->size();
        // table
        this->ui->tableReservationTableWidget->setRowCount(totalSize);

        // invoice table reset
        this->ui->tableReservationTableWidget->clearContents();
        Uint32 rowCount = 0;
        // fill table data
        fillReservationsItems(pTableReservationListPtr, pTableListPtr, rowCount);
        // fill oven data
        fillReservationsItems(pOvenReservationListPtr, pOvenListPtr, rowCount);
        // fill fireplace data
        fillReservationsItems(pFireplaceReservationListPtr, pFireplaceListPtr, rowCount);
    }
    //
    void AdminReservationsWindow::fillReservationsItems(const ReservationListPtr &pReservationListPtr, const ReservationItemListPtr &pReservationItemListPtr, Uint32 &rowCount)
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
                this->connect(pReservationButton, &QPushButton::clicked, std::bind(&AdminReservationsWindow::on_reservedButton_clicked, this, pReservationItemPtr->m_idItem, pReservationItemPtr->m_itemType));
                this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pReservationButton);
            } else {
                // this table is reserved
                ReservationPtr pReservationPtr = tableReservationMapItem->second;
                QString guestName = QString("[%1] %2 %3").arg(pReservationPtr->m_idMember).arg(pReservationPtr->m_memberName).arg(pReservationPtr->m_memberSurname);
                this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(guestName));
                this->ui->tableReservationTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(pReservationPtr->m_guestNum)));
                // do not show cancel when reservation is from Admin
                if (pReservationPtr->m_isAdmin) {
                    // show cancel button action
                    QPushButton *pCancelButton = new QPushButton(tr("Cancel"), this->ui->tableReservationTableWidget);
                    this->connect(pCancelButton, &QPushButton::clicked, std::bind(&AdminReservationsWindow::on_cancelButton_clicked, this, pReservationPtr->m_reservationId, pReservationItemPtr->m_itemType));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pCancelButton);
                } else {
                    QPushButton *pReservationButton = new QPushButton(tr("Reserve"), this->ui->tableReservationTableWidget);
                    this->connect(pReservationButton, &QPushButton::clicked, std::bind(&AdminReservationsWindow::on_reservedButton_clicked, this, pReservationItemPtr->m_idItem, pReservationItemPtr->m_itemType));
                    this->ui->tableReservationTableWidget->setCellWidget(rowCount, 5, pReservationButton);
                }
            }
            rowCount++;
        }
    }
}
