//

#include <QMessageBox>

#include <QsLog.h>

#include "utils.h"
#include "constants.h"
#include "singletons.h"
#include "invoicewindow.h"
#include "ui_invoicewindow.h"

namespace PenyaManager {
    //
    InvoiceWindow::InvoiceWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::InvoiceWindow),
        m_cachedInvoiceTotal(0.0),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
    }
    //
    InvoiceWindow::~InvoiceWindow()
    {
        delete ui;
    }
    //
    void InvoiceWindow::init()
    {
        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(0);
            return;
        }

        //
        // Loading User profile
        //
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMember);

        //
        // Loading Current Invoice
        //
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (!pInvoicePtr) {
            QMessageBox::critical(this, "No active invoice found.", "Program will exit");
            qApp->exit(0);
            return;
        }
        fillInvoiceData(pCurrMember, pInvoicePtr);

        //
        // Show
        //

        show();
    }
    //
    void InvoiceWindow::retranslate()
    {
        qDebug() << "retranslate invoicewindow";
        this->ui->retranslateUi(this);
    }
    //
    void InvoiceWindow::on_backPushButton_clicked()
    {
        // call main window
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void InvoiceWindow::on_confirmPushButton_clicked()
    {
        // Close invoice
        //
        // Loading Current Invoice
        //
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (!pInvoicePtr) {
            QMessageBox::critical(this, "No active invoice found.", "Program will exit");
            qApp->exit(0);
            return;
        }

        // Update member balance
        Singletons::m_pServices->closeInvoice(pCurrMember, pInvoicePtr->m_id);
        QLOG_INFO() << QString("[Invoice] User %1 Invoice ID %2").arg(pCurrMember->m_id).arg(pInvoicePtr->m_id);

        // print invoice

        // call main window
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void InvoiceWindow::fillInvoiceData(const MemberPtr &pMemberPtr, const InvoicePtr &pInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        this->ui->invoiceProductTableWidget->setColumnCount(4);
        this->ui->invoiceProductTableWidget->setRowCount(pInvoiceProductItemListPtr->size());
        // invoice table Header
        QStringList headers;
        headers.append("article");
        headers.append("price/u");
        headers.append("count");
        headers.append("total");
        this->ui->invoiceProductTableWidget->setHorizontalHeaderLabels(headers);
        // invoice table reset
        this->ui->invoiceProductTableWidget->clearContents();
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 1, new QTableWidgetItem(tr("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit)));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 3, new QTableWidgetItem(tr("%1 €").arg(totalPrice)));
            totalInvoice += totalPrice;
            rowCount++;
        }

        this->m_cachedInvoiceTotal = totalInvoice;

        //
        // Invoice Information
        //
        // ID
        this->ui->invoiceIdInfoLabel->setText(QString("%1").arg(pInvoicePtr->m_id));
        // Date
        this->ui->invoiceDateInfoLabel->setText(tr("%1").arg(pInvoicePtr->m_date.toString()));
        // Total
        this->ui->invoiceTotalInfoLabel->setText(QString("%1 €").arg(totalInvoice));
        // new balance
        Float newBalance = pMemberPtr->m_balance;
        newBalance -= totalInvoice;
        this->ui->newBalanceInfoLabel->setText(QString("%1 €").arg(newBalance));
    }
}

