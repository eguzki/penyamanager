//

#include <QMessageBox>

#include "utils.h"
#include "singletons.h"
#include "accountview.h"
#include "ui_accountview.h"

namespace PenyaManager {
    //
    AccountView::AccountView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AccountView)
    {
        ui->setupUi(this);
    }
    //
    AccountView::~AccountView()
    {
        delete ui;
    }
    //
    void AccountView::init()
    {
        //
        // Loading User profile
        //

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillMemberProfile(pCurrMemberPtr);

        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        // add one day to "toDate" to be included
        fillAccountData(pCurrMemberPtr->m_id, fromIntialDate, toInitialDate.addDays(1));

        //
        // Show
        //

        show();
    }
    //
    void AccountView::fillAccountData(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        // fetch data
        TransactionListPtr pTransactionListPtr = Singletons::m_pDAO->getAccountList(memberId, fromDate, toDate);

        // table
        this->ui->accountTableWidget->setColumnCount(4);
        this->ui->accountTableWidget->setRowCount(pTransactionListPtr->size());

        // invoice table Header
        QStringList headers;
        headers.append("Date");
        headers.append("Description");
        headers.append("Amount");
        headers.append("Type");
        this->ui->accountTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->accountTableWidget->setColumnWidth(0, 200);
        this->ui->accountTableWidget->setColumnWidth(1, 400);
        this->ui->accountTableWidget->setColumnWidth(2, 200);
        this->ui->accountTableWidget->setColumnWidth(3, 130);
        // invoice table reset
        this->ui->accountTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (TransactionList::iterator iter = pTransactionListPtr->begin(); iter != pTransactionListPtr->end(); ++iter)
        {
            TransactionPtr pTransactionPtr = *iter;
            this->ui->accountTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pTransactionPtr->m_date.toString()));
            this->ui->accountTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pTransactionPtr->m_descr));
            this->ui->accountTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1 €").arg(pTransactionPtr->m_amount)));
            this->ui->accountTableWidget->setItem(rowCount, 3, new QTableWidgetItem(getStringFromTransactionTypeEnum(pTransactionPtr->m_type)));
            rowCount++;
        }
    }
    //
    void AccountView::fillMemberProfile(const MemberPtr &pMemberPtr)
    {
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
        QPixmap memberPixmap = Utils::getImage(imagePath);
        this->ui->memberImage->setPixmap(memberPixmap);
        this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->memberImage->setScaledContents(true);
        this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
        this->ui->memberIdInfo->setText(QString::number(pMemberPtr->m_id));
        this->ui->memberBalanceInfo->setText(QString::number(pMemberPtr->m_balance, 'f', 2));
    }
    //
    void AccountView::on_backPushButton_clicked()
    {
        this->hide();
        // call main window
        IPartner* pMainWindow = Singletons::m_pParnetFinder->getPartner(Constants::kMainWindowKey);
        pMainWindow->init();
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

