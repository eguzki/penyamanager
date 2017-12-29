//

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include <commons/numitemdialog.h>
#include "ui_loginwindow.h"
#include "loginwindow.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent, QTranslator *pTranslator, QTimer *pInactivityTimer, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::LoginWindow),
        m_currentPage(0),
        m_password(),
        m_username(-1),
        m_pTranslator(pTranslator),
        m_pInactivityTimer(pInactivityTimer),
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
        // connect QTimer timeout event
        this->connect(m_pInactivityTimer, &QTimer::timeout, std::bind(&LoginWindow::onInactivityTimeout, this));
    }
    //
    LoginWindow::~LoginWindow()
    {
        delete ui;
    }
    //
    void LoginWindow::init()
    {
        initializeLang();

        m_pInactivityTimer->stop();

        this->m_username = -1;
        this->m_password = QString();

        //
        // Loading Last Invoice
        //
        InvoiceResultPtr pLastInvoiceResultPtr = Singletons::m_pDAO->getLastInvoiceInfo();
        if (pLastInvoiceResultPtr->m_error) {
            // Last invoice not found
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin, QString("Last invoice not found"));
            return;
        }

        //
        // Loading Last Invoice's owner profile
        //
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(pLastInvoiceResultPtr->m_pInvoice->m_memberId);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pLogger->Error(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("getMemberById %1").arg(pLastInvoiceResultPtr->m_pInvoice->m_memberId));
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("Unable to find last invoice's owner by id %1").arg(pLastInvoiceResultPtr->m_pInvoice->m_memberId));
            return;
        }
        fillLastInvoiceOwnerInfo(pMemberResultPtr->m_member);
        //
        // Loading Last Invoice info
        //
        m_currentPage = 0;
        fillLastInvoiceInfo(pLastInvoiceResultPtr->m_pInvoice);
    }
    //
    void LoginWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->languagePushButton->setText(Singletons::m_pTranslationManager->getLanguageLabel());
    }
    //
    void LoginWindow::initializeLang()
    {
        // Init with basque language
        if (Singletons::m_pTranslationManager->getLanguageLabel() != TranslationManager::kBasqueLangLabel)
        {
            // change translator
            qApp->removeTranslator(m_pTranslator);
            Singletons::m_pTranslationManager->switchLanguage();
            // load new dictionary
            m_pTranslator->load(Singletons::m_pTranslationManager->getTranslationFile());
            // installTranslator() will create a change event which will be sent to every single widget
            qApp->installTranslator(m_pTranslator);
        }
    }
    //
    void LoginWindow::initializeTable()
    {
        // table
        QHeaderView* header = this->ui->lastInvoiceTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        this->ui->lastInvoiceTableWidget->setColumnCount(4);
        header->setDefaultSectionSize(80);
        translateTable();
        Uint32 column = 0;

        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 175);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 90);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 60);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 90);
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
        NumItemDialog numItemDialog(this, tr("Insert username"));
        numItemDialog.exec();
        this->m_username = numItemDialog.getKey();
        // check member username input
        if (this->m_username < 0)
        {
            GuiUtils::infoMessageBox(this, tr("Username required"));
            return;
        }

        // Ask for password
        NumItemDialog passNumItemDialog(this, tr("Insert password"), true);
        passNumItemDialog.exec();
        this->m_password = passNumItemDialog.getKeyStr();
        // check password input
        if (this->m_password.isEmpty())
        {
            GuiUtils::infoMessageBox(this, tr("Password not set"));
            return;
        }

        // Loading user Profile
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(this->m_username);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pLogger->Error(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("getMemberByUsername %1").arg(this->m_username));
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        if (!pMemberResultPtr->m_member)
        {
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("username %1 does not exist").arg(this->m_username));
            // User could not be found
            GuiUtils::infoMessageBox(this, tr("User not registered in the system: %1").arg(this->m_username));
            return;
        }

        QString hashedPwd = Utils::hashSHA256asHex(this->m_password);
        if (pMemberResultPtr->m_member->m_pwd != hashedPwd)
        {
            // User not active
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("id %1 username %2 pass check failed").arg(pMemberResultPtr->m_member->m_id).arg(this->m_username));
            GuiUtils::infoMessageBox(this, tr("Password incorrect"));
            return;
        }

        if (!pMemberResultPtr->m_member->m_active)
        {
            // User not active
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("User id %1 not active").arg(pMemberResultPtr->m_member->m_id));
            GuiUtils::infoMessageBox(this, tr("User not active in the system: %1").arg(pMemberResultPtr->m_member->m_id));
            return;
        }

        if (pMemberResultPtr->m_member->m_balance < 0)
        {
            // User is slow payer
            GuiUtils::criticalMessageBox(this, tr("Your current balance is negative: %1 €").arg(pMemberResultPtr->m_member->m_balance, 0, 'f', 2));
        }

        // login granted
        Singletons::m_pLogger->Info(pMemberResultPtr->m_member->m_id, PenyaManager::LogAction::kLogin, QString("login in"));

        // Every member login, outdated invoices are cleaned
        // It is supossed that only few invoices would be open
        bool ok = Singletons::m_pServices->cleanOutdatedInvoices();
        if (!ok) {
            Singletons::m_pLogger->Error(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin, QString("cleanOutdatedInvoices"));
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }

        // assign user
        Singletons::m_pCurrMember = pMemberResultPtr->m_member;

        // change last login date
        ok = Singletons::m_pDAO->changeMemberLastLogin(pMemberResultPtr->m_member->m_id, QDateTime::currentDateTimeUtc());
        if (!ok) {
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        // initialize inactivity timer
        m_pInactivityTimer->start();
        // load main window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void LoginWindow::on_languagePushButton_clicked()
    {
        // change translator
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_pTranslationManager->switchLanguage();
        // load new dictionary
        m_pTranslator->load(Singletons::m_pTranslationManager->getTranslationFile());
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
        this->ui->memberNameLabel->setText(QString("%1").arg(pLastInvoiceOwnerPtr->m_name));
        // id
        this->ui->memberIdLabel->setText(QString::number(pLastInvoiceOwnerPtr->m_username));
    }
    //
    void LoginWindow::fillLastInvoiceInfo(const InvoicePtr &pLastInvoicePtr)
    {
        //
        // Product List
        //
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getInvoiceProductItems(pLastInvoicePtr->m_id, m_currentPage, Constants::kLoginWindowProductListPageCount);
        if (pInvoiceProductItemListResultPtr->m_error) {
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(pLastInvoicePtr->m_id);
        if (invoiceProductItemStatsResultPtr->m_error) {
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)invoiceProductItemStatsResultPtr->m_stats->m_totalProducts/Constants::kLoginWindowProductListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }

        // invoice table reset
        this->ui->lastInvoiceTableWidget->clearContents();
        this->ui->lastInvoiceTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());

        //fill data
        Uint32 rowCount = 0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QTableWidgetItem *item = new QTableWidgetItem(pInvoiceProductItemPtr->m_productname);
            item->setData(Qt::TextAlignmentRole, Qt::AlignLeft);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 0, item);
            item = new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2));
            item->setData(Qt::TextAlignmentRole, Qt::AlignRight);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 1, item);
            item = new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count));
            item->setData(Qt::TextAlignmentRole, Qt::AlignRight);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 2, item);
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            item = new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2));
            item->setData(Qt::TextAlignmentRole, Qt::AlignRight);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 3, item);
            this->ui->lastInvoiceTableWidget->setRowHeight(rowCount, 35);
            rowCount++;
        }

        //
        // Invoice Information
        //
        // Date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pLastInvoicePtr->m_date, QLocale::NarrowFormat);
        QString lastModifDateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pLastInvoicePtr->m_lastModified, QLocale::NarrowFormat);
        this->ui->lastInvoiceDateLabel->setText(tr("Created on: %1   Modified on: %2").arg(dateLocalized).arg(lastModifDateLocalized));
        // Total
        this->ui->lastInvoiceTotalLabel->setText(QString("%1 €").arg(invoiceProductItemStatsResultPtr->m_stats->m_totalAmount, 0, 'f', 2));
    }
    //
    void LoginWindow::on_prevPagePushButton_clicked()
    {
        //
        // Loading Last Invoice
        //
        InvoiceResultPtr pLastInvoiceResultPtr = Singletons::m_pDAO->getLastInvoiceInfo();
        if (pLastInvoiceResultPtr->m_error) {
            // Last invoice not found
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin, QString("previous page, last invoice not found"));
            return;
        }

        m_currentPage--;
        fillLastInvoiceInfo(pLastInvoiceResultPtr->m_pInvoice);
    }
    //
    void LoginWindow::on_nextPagePushButton_clicked()
    {
        //
        // Loading Last Invoice
        //
        InvoiceResultPtr pLastInvoiceResultPtr = Singletons::m_pDAO->getLastInvoiceInfo();
        if (pLastInvoiceResultPtr->m_error) {
            // Last invoice not found
            GuiUtils::criticalMessageBox(this, tr("Database error. Contact administrator"));
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin, QString("next page, last invoice not found"));
            return;
        }
        m_currentPage++;
        fillLastInvoiceInfo(pLastInvoiceResultPtr->m_pInvoice);
    }
    //
    void LoginWindow::onInactivityTimeout()
    {
        // load login window
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
}

