//

#include <QDoubleSpinBox>
#include <QPushButton>
#include <QMessageBox>

#include <QsLog.h>

#include "singletons.h"
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
        headers.append(tr("memberid"));
        headers.append(tr("Total"));
        headers.append(tr("Cash"));
        headers.append(tr("Action"));
        this->ui->depositTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void DepositListView::showUncheckedDeposits()
    {
        DepositListPtr pDepositListPtr = Singletons::m_pDAO->getUncheckedDeposits();
        // num rows
        this->ui->depositTableWidget->setRowCount(pDepositListPtr->size());
        // deposit table reset
        this->ui->depositTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (DepositList::iterator iter = pDepositListPtr->begin(); iter != pDepositListPtr->end(); ++iter)
        {
            DepositPtr pDepositPtr = *iter;
            Uint32 column = 0;
            QTableWidgetItem *pTableItem = new QTableWidgetItem(QString::number(pDepositPtr->m_id));
            pTableItem->setData(Qt::UserRole, pDepositPtr->m_id);
            this->ui->depositTableWidget->setItem(rowCount, column++, pTableItem);
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pDepositPtr->m_date, QLocale::NarrowFormat);
            this->ui->depositTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            pTableItem = new QTableWidgetItem(QString::number(pDepositPtr->m_memberId));
            pTableItem->setData(Qt::UserRole, pDepositPtr->m_memberId);
            this->ui->depositTableWidget->setItem(rowCount, column++, pTableItem);
            pTableItem = new QTableWidgetItem(tr("%1 €").arg(pDepositPtr->m_total));
            pTableItem->setData(Qt::UserRole, pDepositPtr->m_total);
            this->ui->depositTableWidget->setItem(rowCount, column++, pTableItem);
            QDoubleSpinBox *pQDoubleSpinBox = new QDoubleSpinBox(this->ui->depositTableWidget);
            pQDoubleSpinBox->setMaximum(999999.99);
            pQDoubleSpinBox->setValue(pDepositPtr->m_total);
            this->ui->depositTableWidget->setCellWidget(rowCount, column++, pQDoubleSpinBox);
            QPushButton *pQPushButton = new QPushButton("OK", this->ui->depositTableWidget);
            this->ui->depositTableWidget->setCellWidget(rowCount, column++, pQPushButton);
            this->connect(pQPushButton, &QPushButton::clicked, std::bind(&DepositListView::on_deposit_check_clicked, this, rowCount));
            rowCount++;
        }
    }
    //
    void DepositListView::on_deposit_check_clicked(Uint32 rowCount)
    {
        // get cash
        QWidget *pCashWidget = this->ui->depositTableWidget->cellWidget(rowCount, 4);
        QDoubleSpinBox *pDoubleSpinBox = qobject_cast<QDoubleSpinBox *>(pCashWidget);
        if (pDoubleSpinBox == 0) {
            QMessageBox::critical(this, "Unexpected error",
                    "DepositListView failed taking SpinBox");
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
            QString descr = QString("deposit fix. Ref: %1").arg(depositId);
            Singletons::m_pServices->createAccountTransaction(memberId, amount, descr, TransactionType::DepositFix);
        }
        // close deposit
        Singletons::m_pDAO->closeDeposit(depositId);
        QLOG_INFO() << QString("[DepositCheck] deposit ID %1 member ID %2 total %3€ diff %4€").arg(depositId).arg(memberId).arg(total).arg(amount);
        QMessageBox::information(this, "Deposit checked", QString("Difference: %1").arg(amount));
        showUncheckedDeposits();
    }
}

