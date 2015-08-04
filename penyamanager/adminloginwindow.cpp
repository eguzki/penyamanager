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
    AdminLoginWindow::AdminLoginWindow(AdminMainWindow *pAdminMainWindow) :
        IPartner(0),
        m_pAdminMainWindow(pAdminMainWindow),
        ui(new Ui::AdminLoginWindow)
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
}
