//

#include <QDoubleSpinBox>
#include <QPushButton>

#include <commons/singletons.h>
#include <commons/guiutils.h>
#include "depositlistview.h"
#include "ui_depositlistview.h"

namespace PenyaManager {
    //
    DepositListView::DepositListView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::DepositListView)
    {
        ui->setupUi(this);
        initializeTable();
    }
    //
    DepositListView::~DepositListView()
    {
        delete ui;
    }
    //
    void DepositListView::init()
    {
        showUncheckedDeposits();
    }
    //
    void DepositListView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void DepositListView::initializeTable()
    {
        // table
        this->ui->depositTableWidget->setColumnCount(6);
        translateTable();
        Uint32 column = 0;
        this->ui->depositTableWidget->setColumnWidth(column++, 100);
        this->ui->depositTableWidget->setColumnWidth(column++, 200);
        this->ui->depositTableWidget->setColumnWidth(column++, 100);
        this->ui->depositTableWidget->setColumnWidth(column++, 100);
        this->ui->depositTableWidget->setColumnWidth(column++, 200);
        this->ui->depositTableWidget->setColumnWidth(column++, 200);
    }
    //
    void DepositListView::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("ID"));
        headers.append(tr("date"));
        headers.append(tr("Username"));
        headers.append(tr("Total"));
        headers.append(tr("Cash"));
        headers.append(tr("Action"));
        this->ui->depositTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void DepositListView::showUncheckedDeposits()
    {
        DepositListResultPtr pDepositListResultPtr = Singletons::m_pDAO->getUncheckedDeposits();
        if (pDepositListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // num rows
        this->ui->depositTableWidget->setRowCount(pDepositListResultPtr->m_list->size());
        // deposit table reset
        this->ui->depositTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (DepositList::iterator iter = pDepositListResultPtr->m_list->begin(); iter != pDepositListResultPtr->m_list->end(); ++iter)
        {
            DepositPtr pDepositPtr = *iter;
            Uint32 column = 0;
            QTableWidgetItem *pTableItem = new QTableWidgetItem(QString::number(pDepositPtr->m_id));
            pTableItem->setData(Qt::UserRole, pDepositPtr->m_id);
            this->ui->depositTableWidget->setItem(rowCount, column++, pTableItem);
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pDepositPtr->m_date.toLocalTime(), QLocale::NarrowFormat);
            this->ui->depositTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            pTableItem = new QTableWidgetItem(QString::number(pDepositPtr->m_memberUsername));
            pTableItem->setData(Qt::UserRole, pDepositPtr->m_memberId);
            this->ui->depositTableWidget->setItem(rowCount, column++, pTableItem);
            pTableItem = new QTableWidgetItem(QString("%1 €").arg(pDepositPtr->m_total, 0, 'f', 2));
            pTableItem->setData(Qt::UserRole, pDepositPtr->m_total);
            this->ui->depositTableWidget->setItem(rowCount, column++, pTableItem);
            QDoubleSpinBox *pQDoubleSpinBox = new QDoubleSpinBox(this->ui->depositTableWidget);
            pQDoubleSpinBox->setMaximum(999999.99);
            pQDoubleSpinBox->setValue(pDepositPtr->m_total);
            this->ui->depositTableWidget->setCellWidget(rowCount, column++, pQDoubleSpinBox);
            QPushButton *pQPushButton = new QPushButton(tr("OK"), this->ui->depositTableWidget);
            this->ui->depositTableWidget->setCellWidget(rowCount, column++, pQPushButton);
            this->connect(pQPushButton, &QPushButton::clicked, std::bind(&DepositListView::onDeposit_check_clicked, this, rowCount));
            rowCount++;
        }
    }
    //
    void DepositListView::onDeposit_check_clicked(Uint32 rowCount)
    {
        // get cash
        QWidget *pCashWidget = this->ui->depositTableWidget->cellWidget(rowCount, 4);
        QDoubleSpinBox *pDoubleSpinBox = qobject_cast<QDoubleSpinBox *>(pCashWidget);
        if (pDoubleSpinBox == 0) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // get memberId
        Int32 memberId = this->ui->depositTableWidget->item(rowCount, 2)->data(Qt::UserRole).toInt();
        // get total
        Float total = this->ui->depositTableWidget->item(rowCount, 3)->data(Qt::UserRole).toFloat();
        // deposit id
        Int32 depositId = this->ui->depositTableWidget->item(rowCount, 0)->data(Qt::UserRole).toInt();
        Float amount = pDoubleSpinBox->value() - total;
        if (amount != 0) {
            // create account entry with difference when not equal
            QString description = GuiUtils::depositFixDescription(depositId);
            bool ok = Singletons::m_pServices->createAccountTransaction(memberId, amount, description, TransactionType::DepositFix);
            if (!ok) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        }
        // close deposit
        bool ok = Singletons::m_pDAO->closeDeposit(depositId);
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kDeposit,
                QString("deposit ID %1 member ID %2 total %3€ diff %4€").arg(depositId).arg(memberId).arg(total, 0, 'f', 2).arg(amount, 0, 'f', 2));
        showUncheckedDeposits();
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Deposit checked. Difference: %1 €").arg(amount, 0, 'f', 2), [](){});
        // nothing should be added here
    }
}

