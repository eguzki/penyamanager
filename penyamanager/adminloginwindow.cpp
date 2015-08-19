//

#include <QDebug>
#include <QMessageBox>

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

        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(0);
            return;
        }

        show();
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
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getMemberById(this->ui->loginInput->text().toInt());
        if (!pCurrMemberPtr)
        {
            // User could not be found
            QMessageBox::about(this, "Login failed",
                    "User not registered in the system: " + this->ui->loginInput->text());
            return;
        }

        QString plainPwd = this->ui->passInput->text();
        QString hashedPwd = Utils::hashSHA256asHex(plainPwd);
        if (pCurrMemberPtr->m_pwd != hashedPwd)
        {
            // User not active
            QMessageBox::about(this, "Login failed",
                    "Password incorrect");
            return;
        }

        if (!pCurrMemberPtr->m_active)
        {
            // User not active
            QMessageBox::about(this, "Login failed",
                    "User not active in the system: " + this->ui->loginInput->text());
            return;
        }

        if (!pCurrMemberPtr->m_isAdmin)
        {
            // User not admin
            QMessageBox::about(this, "Login failed",
                    "User does not have permissions to login");
            return;
        }

        // login granted
        this->hide();
        // assign user
        Singletons::m_pCurrMember = pCurrMemberPtr;
        // call admin main window
        m_pAdminMainWindow->init();
    }
    //
    void PenyaManager::AdminLoginWindow::on_languagePushButton_clicked()
    {
        // change translator
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_currentLangIndex = (Singletons::m_currentLangIndex + 1)%Singletons::m_numLangs;
        // load new dictionary
        m_pTranslator->load(QString("penyamanageradmin_%1").arg(Singletons::m_pLanguagesPrefixArray[Singletons::m_currentLangIndex]));
        // installTranslator() will create a change event which will be sent to every single widget
        qApp->installTranslator(m_pTranslator);
    }
}

