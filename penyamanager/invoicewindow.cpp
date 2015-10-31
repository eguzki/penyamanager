//

#include <QMessageBox>

#include <QsLog.h>

#include "guiutils.h"
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
            QLOG_ERROR() << QString("[FATAL] Unable to initialize Database: %1").arg(err.text());
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(1);
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
            QLOG_ERROR() << QString("[FATAL] No active invoice found.: %1").arg(pCurrMember->m_id);
            qApp->exit(0);
            return;
        }

        // Update member balance
        Singletons::m_pServices->closeInvoice(pCurrMember, pInvoicePtr->m_id);
        QLOG_INFO() << QString("[Invoice] User %1 Invoice ID %2").arg(pCurrMember->m_id).arg(pInvoicePtr->m_id);

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
    //
    void InvoiceWindow::on_printPushButton_clicked()
    {
        // use static global variable to get invoiceId
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;

        // Loading Current Invoice
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        // Loading Current Invoice products
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);

        QVariantHash invoiceData;
        // Label
        invoiceData["invoiceLabel"] = tr("Invoice");
        invoiceData["memberidLabel"] = tr("Member Id");
        invoiceData["productLabel"] = tr("Product");
        invoiceData["countLabel"] = tr("Count");
        invoiceData["productTotalLabel"] = tr("Total");
        invoiceData["invoiceTotalLabel"] = tr("Invoice Total");

        // invoice general info
        invoiceData["invoiceId"] = pInvoicePtr->m_id;
        invoiceData["memberid"] = pCurrMemberPtr->m_id;
        invoiceData["memberName"] = QString("%1 %2").arg(pCurrMemberPtr->m_name).arg(pCurrMemberPtr->m_surname);
        invoiceData["dateValue"] = pInvoicePtr->m_date;
        invoiceData["invoiceTotal"] = QString("%1 €").arg(QString::number(pInvoicePtr->m_total, 'f', 2));

        // invoice products info
        QVariantList productList;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QVariantHash productData;
            productData["productName"] = pInvoiceProductItemPtr->m_productname;
            productData["productCount"] = pInvoiceProductItemPtr->m_count;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            productData["productTotal"] = QString("%1 €").arg(QString::number(totalPrice, 'f', 2));
            productList.push_back(productData);
        }
        invoiceData["products"] = productList;
        // print invoice
        GuiUtils::printInvoice(invoiceData, pCurrMemberPtr->m_id, pInvoicePtr->m_id);
        QMessageBox::information(this, tr("Print Invoice"), tr("Invoice #%1 sent to printer").arg(QString::number(pInvoicePtr->m_id)));

    }
}


