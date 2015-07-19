//
#include <QDebug>
#include <QMessageBox>
#include "constants.h"
#include "singletons.h"
#include "ui_loginwindow.h"
#include "loginwindow.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::LoginWindow)
    {
        ui->setupUi(this);
        //
        this->connect(this->ui->loginButton, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
    }

    //
    LoginWindow::~LoginWindow()
    {
        delete ui;
    }

    //
    void LoginWindow::init()
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
    void LoginWindow::on_loginButton_clicked()
    {
        // Loading user Profile
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getMemberById(this->ui->loginInput->text().toInt());
        if (pCurrMemberPtr)
        {
            // TODO check passwd
            // TODO check active
            // assign user
            Singletons::m_pCurrMember = pCurrMemberPtr;
            switchWindow(WindowKey::kMainWindowKey);
        } else {
            // User could not be found
            QMessageBox::about(this, "User not found",
                    "User not registered in the system: " + this->ui->loginInput->text());
        }
    }
}



