//

#include <QMessageBox>

#include <commons/utils.h>
#include <commons/singletons.h>
#include "accountview.h"
#include "ui_accountview.h"

namespace PenyaManager {
    //
    AccountView::AccountView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AccountView),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelwidget->layout()->addWidget(m_pMemberProfileGroupBox);
        initializeTable();
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
        this->ui->accountTableWidget->setColumnCount(5);
        translateTable();
        Uint32 column = 0;
        this->ui->accountTableWidget->setColumnWidth(column++, 200);
        this->ui->accountTableWidget->setColumnWidth(column++, 400);
        this->ui->accountTableWidget->setColumnWidth(column++, 200);
        this->ui->accountTableWidget->setColumnWidth(column++, 200);
        this->ui->accountTableWidget->setColumnWidth(column++, 130);
    }
    //
    void AccountView::init()
    {
        //
        // Loading User profile
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        // add one day to "toDate" to be included
        fillAccountData(pCurrMemberPtr->m_id, fromIntialDate, toInitialDate.addDays(1));
    }
    //
    void AccountView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void AccountView::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("Date"));
        headers.append(tr("Description"));
        headers.append(tr("Amount"));
        headers.append(tr("Balance"));
        headers.append(tr("Type"));
        this->ui->accountTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void AccountView::fillAccountData(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        // fetch data
        TransactionListPtr pTransactionListPtr = Singletons::m_pDAO->getAccountListByMemberId(memberId, fromDate, toDate, 0, 9999);

        // num rows
        this->ui->accountTableWidget->setRowCount(pTransactionListPtr->size());
        // invoice table reset
        this->ui->accountTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (TransactionList::iterator iter = pTransactionListPtr->begin(); iter != pTransactionListPtr->end(); ++iter)
        {
            Uint32 column = 0;
            TransactionPtr pTransactionPtr = *iter;
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pTransactionPtr->m_date, QLocale::NarrowFormat);
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pTransactionPtr->m_descr));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_amount, 0, 'f', 2)));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString("%1 €").arg(pTransactionPtr->m_balance, 0, 'f', 2)));
            this->ui->accountTableWidget->setItem(rowCount, column++, new QTableWidgetItem(getStringFromTransactionTypeEnum(pTransactionPtr->m_type)));
            rowCount++;
        }
    }
    //
    void AccountView::on_backPushButton_clicked()
    {
        // Go to dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void AccountView::on_searchButton_clicked()
    {
        if (this->ui->fromCalendarWidget->selectedDate() >= this->ui->toCalendarWidget->selectedDate())
        {
            QMessageBox::information(this, "Wrong search criteria", "From date must be before To date");
        } else {
            MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
            // add one day to "toDate" to be included
            fillAccountData(pCurrMemberPtr->m_id, this->ui->fromCalendarWidget->selectedDate(), this->ui->toCalendarWidget->selectedDate().addDays(1));
        }
    }
}
