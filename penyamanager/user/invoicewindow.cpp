//

#include <QMessageBox>

#include <QsLog.h>

#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include "invoicewindow.h"
#include "ui_invoicewindow.h"

namespace PenyaManager {
    //
    InvoiceWindow::InvoiceWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::InvoiceWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        initializeTable();
    }
    //
    InvoiceWindow::~InvoiceWindow()
    {
        delete ui;
    }
    //
    void InvoiceWindow::initializeTable()
    {
        // table
        this->ui->invoiceProductTableWidget->setColumnCount(4);
        translateTable();
        Uint32 column = 0;
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 300);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 100);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 100);
        this->ui->invoiceProductTableWidget->setColumnWidth(column++, 100);
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
    }
    //
    void InvoiceWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void InvoiceWindow::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append(tr("count"));
        headers.append(tr("total"));
        this->ui->invoiceProductTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void InvoiceWindow::on_backPushButton_clicked()
    {
        // Go to dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
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

        // call dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void InvoiceWindow::fillInvoiceData(const MemberPtr &pMemberPtr, const InvoicePtr &pInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        this->ui->invoiceProductTableWidget->setRowCount(pInvoiceProductItemListPtr->size());
        // invoice table reset
        this->ui->invoiceProductTableWidget->clearContents();

        //fill data
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2)));
            this->ui->invoiceProductTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceProductTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            totalInvoice += totalPrice;
            rowCount++;
        }

        //
        // Invoice Information
        //
        // ID
        this->ui->invoiceIdInfoLabel->setText(QString("%1").arg(pInvoicePtr->m_id));
        // Date
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_date, QLocale::NarrowFormat);
        this->ui->invoiceDateInfoLabel->setText(dateLocalized);
        // Total
        this->ui->invoiceTotalInfoLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
        // new balance
        Float newBalance = pMemberPtr->m_balance;
        newBalance -= totalInvoice;
        this->ui->newBalanceInfoLabel->setText(QString("%1 €").arg(newBalance, 0, 'f', 2));
    }
    //
    void InvoiceWindow::on_printPushButton_clicked()
    {
        // use static global variable to get invoiceId
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;

        // Loading Current Invoice
        // current invoice has not been closed. Some attr are missing
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
        // invoice date is invoice creation date
        // Can be old (e.g. an unclosed invoice created some days ago)
        // print current date
        invoiceData["dateValue"] = QDateTime::currentDateTime();

        // invoice products info
        QVariantList productList;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QVariantHash productData;
            productData["productName"] = pInvoiceProductItemPtr->m_productname;
            productData["productCount"] = pInvoiceProductItemPtr->m_count;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            totalInvoice += totalPrice;
            productData["productTotal"] = QString("%1 €").arg(totalPrice, 0, 'f', 2);
            productList.push_back(productData);
        }
        invoiceData["products"] = productList;
        // computed invoice total value
        invoiceData["invoiceTotal"] = QString("%1 €").arg(totalInvoice, 0, 'f', 2);
        // print invoice
        GuiUtils::printInvoice(invoiceData, pCurrMemberPtr->m_id, pInvoicePtr->m_id);
        QMessageBox::information(this, tr("Print Invoice"), tr("Invoice #%1 sent to printer").arg(QString::number(pInvoicePtr->m_id)));
    }
}


