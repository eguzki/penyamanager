//

#include <QMessageBox>

#include "objs/LunchTable.h"
#include "utils.h"
#include "singletons.h"
#include "tablereservationview.h"
#include "ui_tablereservationview.h"

namespace PenyaManager {

    //
    TableReservationView::TableReservationView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::TableReservationView)
    {
        ui->setupUi(this);
        this->ui->reservationTypeButtonGroup->setId(this->ui->dinnerButton, static_cast<Int32>(ReservationType::Dinner));
        this->ui->reservationTypeButtonGroup->setId(this->ui->lunchButton, static_cast<Int32>(ReservationType::Lunch));
        this->connect(this->ui->reservationTypeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_reservationType_clicked(int)));
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
        fillMemberProfile(pCurrMemberPtr);

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
    void TableReservationView::fillMemberProfile(const MemberPtr &pMemberPtr)
    {
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
        QPixmap memberPixmap = Utils::getImage(imagePath);
        this->ui->memberImage->setPixmap(memberPixmap);
        this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->memberImage->setScaledContents(true);
        this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
        this->ui->memberIdInfoLabel->setText(QString::number(pMemberPtr->m_id));
        this->ui->memberAccountInfoLabel->setText(QString::number(pMemberPtr->m_balance, 'f', 2));
    }
    //
    void TableReservationView::on_backButton_clicked()
    {
        this->hide();
        // call main window
        IPartner* pMainWindow = Singletons::m_pParnetFinder->getPartner(Constants::kMainWindowKey);
        pMainWindow->init();
    }
    //
    void TableReservationView::on_reservationType_clicked(int reservationTypeInt)
    {
        QDate date = this->ui->calendarWidget->selectedDate();
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        ReservationType reservationType = static_cast<ReservationType>(reservationTypeInt);
        fillTableReservations(pCurrMemberPtr, date, reservationType);
    }
    //
    void TableReservationView::initializeTableReservations(const MemberPtr &pMemberPtr)
    {
        QDateTime nowDateTime = QDateTime::currentDateTime();
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 11), QTime(0,0)); // when reservations cannot be done
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 11), QTime(7,0)); // monday after deadline
        //QDateTime nowDateTime = QDateTime(QDate(2015, 5, 17), QTime(7,0)); // sunday (same day min and max)
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
            this->ui->lunchButton->setEnabled(false);
            this->ui->dinnerButton->setEnabled(false);
            return;
        } else {
            // reservation type (lunch/dinner) buttons
            this->ui->lunchButton->setCheckable(true);
            this->ui->dinnerButton->setCheckable(true);
            this->ui->lunchButton->setChecked(true);
            this->ui->dinnerButton->setChecked(false);
        }

        this->ui->calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);

        fillTableReservations(pMemberPtr, nowDate, ReservationType::Lunch);

    }
    //
    void TableReservationView::fillTableReservations(const MemberPtr &pMemberPtr, const QDate &nowDate, ReservationType reservationType)
    {
        // fetch reservation data
        TableReservationListPtr pTableReservationListPtr =  Singletons::m_pDAO->getTableReservation(reservationType, nowDate);

        // create map structure for easy and efficient lookup
        TableReservationMap tableReservationMap;
        prepareTableReservationMap(tableReservationMap, pTableReservationListPtr);

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
        for (LunchTableList::iterator iter = pLunchTableListPtr->begin(); iter != pLunchTableListPtr->end(); ++iter)
        {
            LunchTablePtr pLunchTablePtr = *iter;
            this->ui->tableReservationTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pLunchTablePtr->m_idTable)));
            this->ui->tableReservationTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pLunchTablePtr->m_tableName));
            this->ui->tableReservationTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pLunchTablePtr->m_guestNum)));
            auto tableReservationMapItem = tableReservationMap.find(pLunchTablePtr->m_idTable);
            if (tableReservationMapItem == tableReservationMap.end()) {
                // this table is not reserved
                this->ui->tableReservationTableWidget->setItem(rowCount, 5, new QTableWidgetItem("Action"));
            } else {
                // this table is reserved
                TableReservationPtr pTableReservationPtr = tableReservationMapItem->second;
                QString guestName = QString("[%1] %2 %3").arg(pTableReservationPtr->m_idMember).arg(pTableReservationPtr->m_memberName).arg(pTableReservationPtr->m_memberSurname);
                this->ui->tableReservationTableWidget->setItem(rowCount, 3, new QTableWidgetItem(guestName));
                this->ui->tableReservationTableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(pTableReservationPtr->m_guestNum)));
                this->ui->tableReservationTableWidget->setItem(rowCount, 5, new QTableWidgetItem("Action"));
            }
            rowCount++;
        }
    }
    //
    void TableReservationView::prepareTableReservationMap(TableReservationMap &tableReservationMap, const TableReservationListPtr &pTableReservationListPtr)
    {
        for (auto iter = pTableReservationListPtr->begin(); iter != pTableReservationListPtr->end(); ++iter)
        {
            TableReservationPtr pTableReservationPtr = *iter;
            tableReservationMap[pTableReservationPtr->m_idTable] = pTableReservationPtr;
        }
    }
    //
    void TableReservationView::on_calendarWidget_clicked(const QDate &date)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        bool lunchChecked = this->ui->lunchButton->isChecked();
        ReservationType reservationType = (lunchChecked)?(ReservationType::Lunch) : (ReservationType::Dinner);
        fillTableReservations(pCurrMemberPtr, date, reservationType);
    }
}



