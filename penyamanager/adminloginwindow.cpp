//
#include <QDebug>
#include <QMessageBox>
#include "constants.h"
#include "singletons.h"
#include "ui_adminloginwindow.h"
#include "adminloginwindow.h"

namespace PenyaManager {

    //
    AdminLoginWindow::AdminLoginWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AdminLoginWindow)
    {
        ui->setupUi(this);
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
        // TODO generalize getActiveMemberById to filter admin users
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getActiveMemberById(this->ui->loginInput->text().toInt());
        if (pCurrMemberPtr)
        {
            this->hide();
            // assign user
            Singletons::m_pCurrMember = pCurrMemberPtr;
            // call admin main window
            IPartner* pMainWindow = Singletons::m_pParnetFinder->getPartner(Constants::kAdminMainWindowKey);
            pMainWindow->init();
        } else {
            // User could not be found
            QMessageBox::about(this, "Admin user not found",
                    "Admin user not registered in the system: " + this->ui->loginInput->text());
        }
    }
}
