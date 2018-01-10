//

#include <QMessageBox>
#include <QFile>

#include <commons/utils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include "ui_adminloginwindow.h"
#include "adminloginwindow.h"

namespace PenyaManager {
    //
    AdminLoginWindow::AdminLoginWindow(QWidget *parent, AdminMainWindow *pAdminMainWindow, QTranslator *pTranslator) :
        IPartner(parent),
        m_pAdminMainWindow(pAdminMainWindow),
        ui(new Ui::AdminLoginWindow),
        m_pTranslator(pTranslator)
    {
        ui->setupUi(this);
        // only numbers allowed
        QValidator *pMemberIdIntValidator = new QIntValidator();
        this->ui->loginInput->setValidator(pMemberIdIntValidator);
        QValidator *pPassIntValidator = new QIntValidator();
        this->ui->passInput->setValidator(pPassIntValidator);

        // load code build
        QFile versionFile(":VERSION_ADMIN");
        versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream versionStream(&versionFile);
        versionStream.setCodec("UTF-8");
        QString versionStr = versionStream.readAll();
        this->ui->versionLabel->setText(QString("code build %1").arg(versionStr));
    }
    //
    AdminLoginWindow::~AdminLoginWindow()
    {
        delete ui;
    }
    //
    void AdminLoginWindow::init()
    {
        initializeLang();
        this->ui->passInput->clear();
        this->ui->loginInput->clear();
        Singletons::m_pCurrMember = GetInvalidMember();
    }
    //
    void AdminLoginWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->ui->languagePushButton->setText(Singletons::m_pTranslationManager->getLanguageLabel());
    }
    //
    void AdminLoginWindow::initializeLang()
    {
        // Init with basque language
        if (Singletons::m_pTranslationManager->getLanguageLabel() != TranslationManager::kBasqueLangLabel)
        {
            // change translator
            qApp->removeTranslator(m_pTranslator);
            Singletons::m_pTranslationManager->switchLanguage();
            // load new dictionary
            m_pTranslator->load(Singletons::m_pTranslationManager->getAdminTranslationFile());
            // installTranslator() will create a change event which will be sent to every single widget
            qApp->installTranslator(m_pTranslator);
        }
    }
    //
    void AdminLoginWindow::on_loginButton_clicked()
    {
        // Loading user Profile
        QString loginName = this->ui->loginInput->text();
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(loginName.toInt());
        if (pMemberResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        if (!pMemberResultPtr->m_member)
        {
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("username %1 does not exist").arg(loginName));

            // User could not be found
            QMessageBox::about(this, tr("Login failed"),
                    tr("User not registered in the system: %1").arg(this->ui->loginInput->text()));
            return;
        }

        QString plainPwd = this->ui->passInput->text();
        QString hashedPwd = Utils::hashSHA256asHex(plainPwd);
        if (pMemberResultPtr->m_member->m_pwd != hashedPwd)
        {
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("id %1 username %2 pass check failed").arg(pMemberResultPtr->m_member->m_id).arg(loginName));
            // User not active
            QMessageBox::about(this, tr("Login failed"), tr("Password incorrect"));
            return;
        }

        if (!pMemberResultPtr->m_member->m_active)
        {
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("User id %1 not active").arg(pMemberResultPtr->m_member->m_id));
            // User not active
            QMessageBox::about(this, tr("Login failed"), tr("User not active in the system: %1").arg(this->ui->loginInput->text()));
            return;
        }

        if (!pMemberResultPtr->m_member->m_isAdmin)
        {
            Singletons::m_pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kLogin,
                    QString("User id %1 not admin").arg(pMemberResultPtr->m_member->m_id));
            // User not admin
            QMessageBox::about(this, tr("Login failed"), tr("User does not have permissions to login"));
            return;
        }

        // login granted
        Singletons::m_pLogger->Info(pMemberResultPtr->m_member->m_id, PenyaManager::LogAction::kLogin, QString("login in"));

        // switch
        this->hide();
        // assign user
        Singletons::m_pCurrMember = pMemberResultPtr->m_member;
        // call admin main window
        m_pAdminMainWindow->init();
        m_pAdminMainWindow->show();
    }
    //
    void PenyaManager::AdminLoginWindow::on_languagePushButton_clicked()
    {
        // change translator
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_pTranslationManager->switchLanguage();
        // load new dictionary
        m_pTranslator->load(Singletons::m_pTranslationManager->getAdminTranslationFile());
        // installTranslator() will create a change event which will be sent to every single widget
        qApp->installTranslator(m_pTranslator);
    }
}

