//

#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QsLog.h>

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
        QFile versionFile(":VERSION");
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
        this->ui->passInput->clear();
        this->ui->loginInput->clear();
    }
    //
    void AdminLoginWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->ui->languagePushButton->setText(Singletons::m_translationManager.getLanguageLabel());
    }
    //
    void AdminLoginWindow::on_loginButton_clicked()
    {
        // Loading user Profile
        QString loginName = this->ui->loginInput->text();
        MemberPtr pCurrMemberPtr = Singletons::m_pServices->getMemberByUsername(loginName.toInt());
        if (!pCurrMemberPtr)
        {
            QLOG_INFO() << QString("[LoginFailed] username %1 does not exist").arg(loginName);
            // User could not be found
            QMessageBox::about(this, tr("Login failed"),
                    tr("User not registered in the system: %1").arg(this->ui->loginInput->text()));
            return;
        }

        QString plainPwd = this->ui->passInput->text();
        QString hashedPwd = Utils::hashSHA256asHex(plainPwd);
        if (pCurrMemberPtr->m_pwd != hashedPwd)
        {
            QLOG_INFO() << QString("[LoginFailed] User id %1 pass check failed").arg(pCurrMemberPtr->m_id);
            // User not active
            QMessageBox::about(this, tr("Login failed"), tr("Password incorrect"));
            return;
        }

        if (!pCurrMemberPtr->m_active)
        {
            QLOG_INFO() << QString("[LoginFailed] User id %1 not active").arg(pCurrMemberPtr->m_id);
            // User not active
            QMessageBox::about(this, tr("Login failed"), tr("User not active in the system: %1").arg(this->ui->loginInput->text()));
            return;
        }

        if (!pCurrMemberPtr->m_isAdmin)
        {
            QLOG_INFO() << QString("[LoginFailed] User id %1 not admin").arg(pCurrMemberPtr->m_id);
            // User not admin
            QMessageBox::about(this, tr("Login failed"), tr("User does not have permissions to login"));
            return;
        }

        // login granted
        QLOG_INFO() << QString("[LoginSucess] User %1").arg(loginName);

        // switch
        this->hide();
        // assign user
        Singletons::m_pCurrMember = pCurrMemberPtr;
        // call admin main window
        m_pAdminMainWindow->show();
    }
    //
    void PenyaManager::AdminLoginWindow::on_languagePushButton_clicked()
    {
        // change translator
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_translationManager.switchLanguage();
        // load new dictionary
        m_pTranslator->load(Singletons::m_translationManager.getAdminTranslationFile());
        // installTranslator() will create a change event which will be sent to every single widget
        qApp->installTranslator(m_pTranslator);
    }
}

