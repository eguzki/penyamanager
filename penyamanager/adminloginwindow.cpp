//

#include <QDebug>
#include <QMessageBox>

#include <QsLog.h>

#include "utils.h"
#include "constants.h"
#include "singletons.h"
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
    }
    //
    void AdminLoginWindow::on_loginButton_clicked()
    {
        // Loading user Profile
        QString loginName = this->ui->loginInput->text();
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getMemberById(loginName.toInt());
        if (!pCurrMemberPtr)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 does not exist").arg(loginName);
            // User could not be found
            QMessageBox::about(this, "Login failed",
                    "User not registered in the system: " + this->ui->loginInput->text());
            return;
        }

        QString plainPwd = this->ui->passInput->text();
        QString hashedPwd = Utils::hashSHA256asHex(plainPwd);
        if (pCurrMemberPtr->m_pwd != hashedPwd)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 pass check failed").arg(loginName);
            // User not active
            QMessageBox::about(this, "Login failed",
                    "Password incorrect");
            return;
        }

        if (!pCurrMemberPtr->m_active)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 not active").arg(loginName);
            // User not active
            QMessageBox::about(this, "Login failed",
                    "User not active in the system: " + this->ui->loginInput->text());
            return;
        }

        if (!pCurrMemberPtr->m_isAdmin)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 not admin").arg(loginName);
            // User not admin
            QMessageBox::about(this, "Login failed",
                    "User does not have permissions to login");
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

