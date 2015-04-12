//

#include <QMessageBox>

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
        m_cachedInvoiceTotal(0.0)
    {
        ui->setupUi(this);
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
        fillMemberProfile(pCurrMember);

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
    void InvoiceWindow::on_backPushButton_clicked()
    {
        hide();
        // call main window
        IPartner* pMainWindow = Singletons::m_pParnetFinder->getPartner(Constants::kMainWindowKey);
        pMainWindow->init();
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
        // invoice date: now
        pInvoicePtr->m_date = QDateTime::currentDateTime();
        // state: closed
        pInvoicePtr->m_state = InvoiceState::Closed;
        // total
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            totalInvoice += totalPrice;
        }
        pInvoicePtr->m_total = totalInvoice;
        // payment
        pInvoicePtr->m_payment = (this->ui->accountRadioButton->isChecked()) ? (PaymentType::Account) : (PaymentType::Cash);
        // update invoice data
        Singletons::m_pDAO->updateInvoice(pInvoicePtr);

        // Go to login page
        hide();
        // call login window on exit
        IPartner* pLoginWindow = Singletons::m_pParnetFinder->getPartner(Constants::kLoginWindowKey);
        pLoginWindow->init();
    }
    //
    void InvoiceWindow::fillMemberProfile(const MemberPtr &pMemberPtr)
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
        qDebug() << pInvoicePtr->m_date.toString();
        this->ui->invoiceDateInfoLabel->setText(tr("%1").arg(pInvoicePtr->m_date.toString()));
        // Total
        this->ui->invoiceTotalInfoLabel->setText(QString("%1 €").arg(totalInvoice));
        // new balance
        Float newBalance = pMemberPtr->m_balance;
        if (this->ui->accountRadioButton->isChecked()) {
            newBalance -= totalInvoice;
        }
        this->ui->newBalanceInfoLabel->setText(QString("%1 €").arg(newBalance));
    }
    //
    void InvoiceWindow::on_cashRadioButton_toggled(bool cashButtonChecked)
    {
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // new balance
        Float newBalance = cashButtonChecked?(pCurrMember->m_balance):(pCurrMember->m_balance - m_cachedInvoiceTotal);
        this->ui->newBalanceInfoLabel->setText(QString("%1 €").arg(newBalance));
    }
}


