//

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include <commons/timedmessagebox.h>
#include "timednumitemdialog.h"
#include "ui_loginwindow.h"
#include "loginwindow.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent, QTranslator *pTranslator, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::LoginWindow),
        m_currentPage(0),
        m_username(-1),
        m_pTranslator(pTranslator),
        m_pInactivityTimer(Singletons::m_pInactivityTimer),
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

        // initialize login state
        this->m_username = -1;
        Singletons::m_pCurrMember = GetInvalidMember();

        //
        // Loading Last Invoice
        //
        InvoiceResultPtr pLastInvoiceResultPtr = Singletons::m_pDAO->getLastInvoiceInfo();
        if (pLastInvoiceResultPtr->m_error) {
            // Last invoice not found
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin, QString("Last invoice not found"));
            return;
        }

        //
        // Loading Last Invoice's owner profile
        //
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(pLastInvoiceResultPtr->m_pInvoice->m_memberId);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pLogger->Error(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin,
                    QString("getMemberById %1").arg(pLastInvoiceResultPtr->m_pInvoice->m_memberId));
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin,
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

        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 170);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 90);
        this->ui->lastInvoiceTableWidget->setColumnWidth(column++, 50);
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

        InvoiceResultPtr pLastInvoiceResultPtr = Singletons::m_pDAO->getLastInvoiceInfo();
        if (pLastInvoiceResultPtr->m_error) {
            // Last invoice not found
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin, QString("Last invoice not found"));
            return;
        }
        fillLastInvoiceInfo(pLastInvoiceResultPtr->m_pInvoice);
    }
    //
    void LoginWindow::on_loginPushButton_clicked()
    {
        // Ask for userId
        TimedNumItemDialog::numItemDialog(this, tr("Insert username"), std::bind(&LoginWindow::onUsernameProvided, this, _1));
        // no code should be added after infoMessageBox
        return;
    }
    //
    void LoginWindow::onUsernameProvided(QString userNameStr)
    {
        if (userNameStr.isEmpty()) {
            TimedMessageBox::infoMessageBox(this, tr("Username required"), [](){});
            // no code should be added after infoMessageBox
            return;
        }
        // check member username input
        this->m_username = userNameStr.toUInt();

        // Ask for password
        TimedNumItemDialog::numItemDialog(this, tr("Insert password"), std::bind(&LoginWindow::onPassProvided, this, _1), true, 4);
    }
    //
    void LoginWindow::onPassProvided(QString passStr)
    {
        // check password input
        if (passStr.isEmpty())
        {
            TimedMessageBox::infoMessageBox(this, tr("Password not set"), [](){});
            return;
        }

        // Loading user Profile
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(this->m_username);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pLogger->Error(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin,
                    QString("getMemberByUsername %1").arg(this->m_username));
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        if (!pMemberResultPtr->m_member)
        {
            Singletons::m_pLogger->Info(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin,
                    QString("username %1 does not exist").arg(this->m_username));
            // User could not be found
            TimedMessageBox::infoMessageBox(this, tr("User not registered in the system: %1").arg(this->m_username), [](){});
            return;
        }

        if (pMemberResultPtr->m_member->m_pwd != Utils::hashSHA256asHex(passStr))
        {
            // password does not match
            Singletons::m_pLogger->Info(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin,
                    QString("id %1 username %2 pass check failed").arg(pMemberResultPtr->m_member->m_id).arg(this->m_username));
            TimedMessageBox::infoMessageBox(this, tr("Password incorrect"), [](){});
            return;
        }

        if (!pMemberResultPtr->m_member->IsActive())
        {
            // User not active
            Singletons::m_pLogger->Info(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin,
                    QString("User id %1 not active").arg(pMemberResultPtr->m_member->m_id));
            TimedMessageBox::infoMessageBox(this, tr("User not active in the system: %1").arg(pMemberResultPtr->m_member->m_username), [](){});
            return;
        }

        // assign user
        Singletons::m_pCurrMember = pMemberResultPtr->m_member;

        // login granted
        Singletons::m_pLogger->Info(pMemberResultPtr->m_member->m_id, PenyaManager::LogAction::kLogin, QString("login in"));

        // Every member login, outdated invoices are cleaned
        // It is supossed that only few invoices would be open
        bool ok = Singletons::m_pServices->cleanOutdatedInvoices();
        if (!ok) {
            Singletons::m_pLogger->Error(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin, QString("cleanOutdatedInvoices"));
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // change last login date
        ok = Singletons::m_pDAO->changeMemberLastLogin(pMemberResultPtr->m_member->m_id, QDateTime::currentDateTimeUtc());
        if (!ok) {
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
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
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(pLastInvoicePtr->m_id);
        if (invoiceProductItemStatsResultPtr->m_error) {
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
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
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            // price per unit depending on invoice is closed
            Float pricePerUnit = (pLastInvoicePtr->m_state == InvoiceState::Closed)?(pInvoiceProductItemPtr->m_pricePerUnit):(pInvoiceProductItemPtr->m_currentPricePerUnit);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 0, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItemPtr->m_productnameEus, pInvoiceProductItemPtr->m_productnameEs)));
            this->ui->lastInvoiceTableWidget->item(rowCount, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pricePerUnit, 0, 'f', 2)));
            this->ui->lastInvoiceTableWidget->item(rowCount, 1)->setTextAlignment(Qt::AlignCenter);
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            this->ui->lastInvoiceTableWidget->item(rowCount, 2)->setTextAlignment(Qt::AlignCenter);
            Float totalPrice = pricePerUnit * pInvoiceProductItemPtr->m_count;
            this->ui->lastInvoiceTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            this->ui->lastInvoiceTableWidget->item(rowCount, 3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            this->ui->lastInvoiceTableWidget->setRowHeight(rowCount, 35);
            totalInvoice += totalPrice;
            rowCount++;
        }

        //
        // Invoice Information
        //
        // Date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pLastInvoicePtr->m_date.toLocalTime(), QLocale::NarrowFormat);
        QString lastModifDateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pLastInvoicePtr->m_lastModified.toLocalTime(), QLocale::NarrowFormat);
        this->ui->lastInvoiceDateLabel->setText(tr("Created on: %1   Modified on: %2").arg(dateLocalized).arg(lastModifDateLocalized));
        // Total
        this->ui->lastInvoiceTotalLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
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
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin, QString("previous page, last invoice not found"));
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
            TimedMessageBox::criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pLastInvoiceResultPtr->m_pInvoice) {
            // Last invoice not found
            Singletons::m_pLogger->Warn(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kLogin, QString("next page, last invoice not found"));
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

