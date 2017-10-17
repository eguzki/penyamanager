//
#include <QDebug>
#include <QMessageBox>

#include <QsLog.h>

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include <commons/numitemdialog.h>
#include "ui_loginwindow.h"
#include "loginwindow.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent, QTranslator *pTranslator, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::LoginWindow),
        m_password(),
        m_username(-1),
        m_pTranslator(pTranslator),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        initializeTable();
        // load code build
        QFile versionFile(":VERSION");
        versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream versionStream(&versionFile);
        versionStream.setCodec("UTF-8");
        QString versionStr = versionStream.readAll();
        this->ui->versionLabel->setText(QString("code build %1").arg(versionStr));
    }
    //
    LoginWindow::~LoginWindow()
    {
        delete ui;
    }
    //
    void LoginWindow::init()
    {
        this->m_username = -1;
        this->m_password = QString();

        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QLOG_ERROR() << QString("Unable to initialize Database: %1").arg(err.text());
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            qApp->exit(1);
            return;
        }

        //
        // Loading Last Invoice
        //
        InvoiceResultPtr pLastInvoiceResultPtr = Singletons::m_pDAO->getLastInvoiceInfo();
        if (pLastInvoiceResultPtr->m_error) {
            // Last invoice not found
            QLOG_INFO() << QString("Last invoice not found");
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            QLOG_WARN() << QString("Last invoice not found");
            return;
        }

        //
        // Loading Last Invoice's owner profile
        //
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(pLastInvoiceResultPtr->m_pInvoice->m_memberId);
        if (pMemberResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            QLOG_WARN() << QString("Unable to find last invoice's owner by id: %1").arg(pLastInvoiceResultPtr->m_pInvoice->m_memberId);
            return;
        }
        fillLastInvoiceOwnerInfo(pMemberResultPtr->m_member);
        //
        // Loading Last Invoice info
        //
        fillLastInvoiceInfo(pLastInvoiceResultPtr->m_pInvoice);
    }
    //
    void LoginWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->languagePushButton->setText(Singletons::m_translationManager.getLanguageLabel());
    }
    //
    void LoginWindow::initializeTable()
    {
        // table
        this->ui->lastInvoiceTableWidget->setColumnCount(4);
        QHeaderView* header = this->ui->lastInvoiceTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        header->setDefaultSectionSize(80);
        translateTable();
        Uint32 column = 0;
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 300);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 100);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 100);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 100);
    }
    //
    void LoginWindow::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append(tr("count"));
        headers.append(tr("total"));
        this->ui->lastInvoiceTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void LoginWindow::on_loginPushButton_clicked()
    {
        // Ask for userId
        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        this->m_username = numItemDialog.getKey();
        // check member username input
        if (this->m_username < 0)
        {
            QMessageBox::about(this, tr("Login failed"), tr("Member code not set"));
            return;
        }

        // Ask for password
        NumItemDialog passNumItemDialog(this, true);
        passNumItemDialog.exec();
        this->m_password = passNumItemDialog.getKeyStr();
        // check password input
        if (this->m_password.isEmpty())
        {
            QMessageBox::about(this, tr("Login failed"), tr("Password not set"));
            return;
        }

        // Loading user Profile
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(this->m_username);
        if (pMemberResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        if (!pMemberResultPtr->m_member)
        {
            QLOG_INFO() << QString("[LoginFailed] username %1 does not exist").arg(this->m_username);
            // User could not be found
            QMessageBox::about(this, tr("Login failed"),
                    tr("User not registered in the system: %1").arg(this->m_username));
            return;
        }

        QString hashedPwd = Utils::hashSHA256asHex(this->m_password);
        if (pMemberResultPtr->m_member->m_pwd != hashedPwd)
        {
            QLOG_INFO() << QString("[LoginFailed] id %1 username %2 pass check failed").arg(pMemberResultPtr->m_member->m_id).arg(this->m_username);
            // User not active
            QMessageBox::about(this, tr("Login failed"), tr("Password incorrect"));
            return;
        }

        if (!pMemberResultPtr->m_member->m_active)
        {
            QLOG_INFO() << QString("[LoginFailed] User id %1 not active").arg(pMemberResultPtr->m_member->m_id);
            // User not active
            QMessageBox::about(this, "Login failed",
                    tr("User not active in the system: %1").arg(pMemberResultPtr->m_member->m_id));
            return;
        }

        if (pMemberResultPtr->m_member->m_balance < 0)
        {
            // User is slow payer
            QMessageBox::warning(this, "Slow Payer",
                    tr("Your current balance is negative: %1 €").arg(pMemberResultPtr->m_member->m_balance, 0, 'f', 2));
        }

        // login granted
        QLOG_INFO() << QString("[LoginSucess] User %1").arg(pMemberResultPtr->m_member->m_id);

        // Every member login, outdated invoices are cleaned
        // It is supossed that only few invoices would be open
        bool ok = Singletons::m_pServices->cleanOutdatedInvoices();
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }

        // assign user
        Singletons::m_pCurrMember = pMemberResultPtr->m_member;

        // change last login date
        ok = Singletons::m_pDAO->changeMemberLastLogin(pMemberResultPtr->m_member->m_id, QDateTime::currentDateTime());
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }

        // load main window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void LoginWindow::on_languagePushButton_clicked()
    {
        // change translator
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_translationManager.switchLanguage();
        // load new dictionary
        m_pTranslator->load(Singletons::m_translationManager.getTranslationFile());
        // installTranslator() will create a change event which will be sent to every single widget
        qApp->installTranslator(m_pTranslator);
    }
    //
    void LoginWindow::fillLastInvoiceOwnerInfo(const MemberPtr &pLastInvoiceOwnerPtr)
    {
        // picture
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pLastInvoiceOwnerPtr->m_imagePath);
        QPixmap memberPixmap = GuiUtils::getImage(imagePath);
        this->ui->memberImageLabel->setPixmap(memberPixmap);
        // picture double size
        this->ui->memberImageLabel->setFixedWidth(Constants::kMemberImageWidth*2);
        this->ui->memberImageLabel->setFixedHeight(Constants::kMemberImageHeigth*2);
        this->ui->memberImageLabel->setScaledContents(true);
        // name
        this->ui->memberNameLabel->setText(pLastInvoiceOwnerPtr->m_name + " " + pLastInvoiceOwnerPtr->m_surname);
        // id
        this->ui->memberIdLabel->setText(QString::number(pLastInvoiceOwnerPtr->m_username));
    }
    //
    void LoginWindow::fillLastInvoiceInfo(const InvoicePtr &pLastInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getInvoiceProductItems(pLastInvoicePtr->m_id);
        if (pInvoiceProductItemListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        this->ui->lastInvoiceTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());
        // invoice table reset
        this->ui->lastInvoiceTableWidget->clearContents();

        //fill data
        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2)));
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            totalInvoice += totalPrice;
            rowCount++;
        }

        //
        // Invoice Information
        //
        // Date
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pLastInvoicePtr->m_date, QLocale::NarrowFormat);
        QString lastModifDateLocalized = Singletons::m_translationManager.getLocale().toString(pLastInvoicePtr->m_lastModified, QLocale::NarrowFormat);
        this->ui->lastInvoiceDateLabel->setText(QString("%1: %2     %3: %4").arg(tr("Created on")).arg(dateLocalized).arg(tr("Modified on")).arg(lastModifDateLocalized));
        // Total
        this->ui->lastInvoiceTotalLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
    }
}

