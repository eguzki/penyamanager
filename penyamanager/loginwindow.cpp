//
#include <QDebug>
#include <QMessageBox>
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "singletons.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::LoginWindow),
        m_pPartner(0)
    {
        ui->setupUi(this);
        //
        //connect(this->ui->loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    }

    //
    LoginWindow::~LoginWindow()
    {
        delete ui;
    }

    //
    void LoginWindow::start()
    {
        init();
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

        showFullScreen();
    }

    //
    void LoginWindow::setParner(IPartner *partner) {
        if(partner == 0)
            return;
        m_pPartner = partner;
    }
    //
    void LoginWindow::on_loginButton_clicked()
    {
        qDebug() << "login";
        if(m_pPartner == 0)
        {
            // TODO log critical error
            QMessageBox::critical(this, "Unexpected state",
                    "Application state should not reach this point. Exiting.");
            qApp->exit(0);
            return;
        }

        //
        // Loading user Profile
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getMemberByName(this->ui->loginInput->text());
        if (pCurrMemberPtr)
        {
            this->hide();
            // assign user
            Singletons::m_pCurrMember = pCurrMemberPtr;
            m_pPartner->init();
        } else {
            // User could not be found
            QMessageBox::about(this, "User not found",
                    "User not registered in the system: " + this->ui->loginInput->text());
        }
    }
}

