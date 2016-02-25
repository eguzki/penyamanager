//
#include <QDebug>
#include <QMessageBox>

#include <QsLog.h>

#include <commons/utils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include "numitemdialog.h"
#include "ui_loginwindow.h"
#include "loginwindow.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent, QTranslator *pTranslator, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::LoginWindow),
        m_password(),
        m_memberId(-1),
        m_pTranslator(pTranslator),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);

        // load code build
        QFile versionFile(":VERSION");
        versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream versionStream(&versionFile);
        versionStream.setCodec("UTF-8");
        QString versionStr = versionStream.readAll();
        this->ui->versionLabel->setText(QString("code build %1").arg(versionStr));
    }

    //
    LoginWindow::~LoginWindow()
    {
        delete ui;
    }
    //
    void LoginWindow::init()
    {
        this->m_memberId = -1;
        this->m_password = QString();

        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QLOG_ERROR() << QString("[FATAL] Unable to initialize Database: %1").arg(err.text());
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(1);
            return;
        }
    }
    //
    void LoginWindow::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void LoginWindow::on_loginPushButton_clicked()
    {
        // Ask for userId
        NumItemDialog numItemDialog(this, tr("Enter member code"));
        numItemDialog.exec();
        this->m_memberId = numItemDialog.getKey();
        // check memberId input
        if (this->m_memberId < 0)
        {
            QMessageBox::about(this, tr("Login failed"), tr("MemberId not set"));
            return;
        }

        // Ask for password
        NumItemDialog passNumItemDialog(this, tr("Enter password"), true);
        passNumItemDialog.exec();
        this->m_password = passNumItemDialog.getKeyStr();
        // check password input
        if (this->m_password.isEmpty())
        {
            QMessageBox::about(this, tr("Login failed"), tr("Password not set"));
            return;
        }

        // Loading user Profile
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getMemberById(this->m_memberId);
        if (!pCurrMemberPtr)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 does not exist").arg(this->m_memberId);
            // User could not be found
            QMessageBox::about(this, tr("Login failed"),
                    tr("User not registered in the system: %1").arg(this->m_memberId));
            return;
        }

        QString hashedPwd = Utils::hashSHA256asHex(this->m_password);
        if (pCurrMemberPtr->m_pwd != hashedPwd)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 pass check failed").arg(this->m_memberId);
            // User not active
            QMessageBox::about(this, tr("Login failed"),
                    tr("Password incorrect"));
            return;
        }

        if (!pCurrMemberPtr->m_active)
        {
            QLOG_INFO() << QString("[LoginFailed] User %1 not active").arg(this->m_memberId);
            // User not active
            QMessageBox::about(this, "Login failed",
                    tr("User not active in the system: %1").arg(this->m_memberId));
            return;
        }

        if (pCurrMemberPtr->m_balance < 0)
        {
            // User is slow payer
            QMessageBox::warning(this, "Slow Payer",
                    tr("Your current balance is negative: %1 €").arg(pCurrMemberPtr->m_balance, 0, 'f', 2));
        }

        // login granted
        QLOG_INFO() << QString("[LoginSucess] User %1").arg(this->m_memberId);
        // assign user
        Singletons::m_pCurrMember = pCurrMemberPtr;

        // change last login date
        Singletons::m_pDAO->changeMemberLastLogin(this->m_memberId, QDateTime::currentDateTime());

        // load main window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    void LoginWindow::on_languagePushButton_clicked()
    {
        // change translator
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_translationManager.switchLanguage();
        // load new dictionary
        m_pTranslator->load(Singletons::m_translationManager.getTranslationFile());
        // installTranslator() will create a change event which will be sent to every single widget
        qApp->installTranslator(m_pTranslator);
    }
}
