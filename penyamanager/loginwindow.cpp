//
#include <QDebug>
#include <QMessageBox>

#include "numitemdialog.h"
#include "utils.h"
#include "constants.h"
#include "singletons.h"
#include "ui_loginwindow.h"
#include "loginwindow.h"

namespace PenyaManager {

    //
    LoginWindow::LoginWindow(QWidget *parent, QTranslator *pTranslator) :
        IPartner(parent),
        ui(new Ui::LoginWindow),
        m_password(),
        m_memberId(-1),
        m_pTranslator(pTranslator)
    {
        ui->setupUi(this);
        // TODO pixmap disapears on translation!!
        QPixmap logoPixmap(":/images/alegrialogo.jpg");
        this->ui->imageLabel->setPixmap(logoPixmap);
    }

    //
    LoginWindow::~LoginWindow()
    {
        delete ui;
    }
    //
    void LoginWindow::init()
    {
        this->ui->memberIdLabel->clear();
        this->ui->passwordLabel->clear();
        this->m_memberId = -1;
        this->m_password = QString();

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
    void LoginWindow::retranslate()
    {
        qDebug() << "retranslate2 login window";
        this->ui->retranslateUi(this);
    }
    //
    void LoginWindow::on_loginPushButton_clicked()
    {
        // check memberId input
        if (this->m_memberId < 0)
        {
            QMessageBox::about(this, "Login failed", "MemberId not set");
            return;
        }
        // check password input
        if (this->m_password.isEmpty())
        {
            QMessageBox::about(this, "Login failed", "Password not set");
            return;
        }
        // Loading user Profile
        MemberPtr pCurrMemberPtr = Singletons::m_pDAO->getMemberById(this->m_memberId);
        if (!pCurrMemberPtr)
        {
            // User could not be found
            QMessageBox::about(this, "Login failed",
                    QString("User not registered in the system: %1").arg(this->m_memberId));
            return;
        }

        QString hashedPwd = Utils::hashSHA256asHex(this->m_password);
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
                    QString("User not active in the system: %1").arg(this->m_memberId));
            return;
        }

        if (pCurrMemberPtr->m_balance < 0)
        {
            // User is slow payer
            QMessageBox::warning(this, "Slow Payer",
                    QString("Your current balance is negative: %1 €").arg(pCurrMemberPtr->m_balance));
        }

        // login granted
        // assign user
        Singletons::m_pCurrMember = pCurrMemberPtr;
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void LoginWindow::on_passwordPushButton_clicked()
    {
        NumItemDialog numItemDialog(this, true);
        numItemDialog.exec();
        this->m_password = numItemDialog.getKeyStr();
        QString hiddenPassText(this->m_password);
        hiddenPassText.replace(QRegExp("."), "*");
        this->ui->passwordLabel->setText(hiddenPassText);
    }
    //
    void LoginWindow::on_memberIdPushButton_clicked()
    {
        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        this->m_memberId = numItemDialog.getKey();
        this->ui->memberIdLabel->setText(QString::number(this->m_memberId));
    }
    void LoginWindow::on_languagePushButton_clicked()
    {
        qApp->removeTranslator(m_pTranslator);
        Singletons::m_currentLangIndex = (Singletons::m_currentLangIndex + 1)%Singletons::m_numLangs;
        // load new dictionary
        qDebug() << QString("penyamanager_%1").arg(Singletons::m_pLanguagesPrefixArray[Singletons::m_currentLangIndex]);
        bool ok = m_pTranslator->load(QString("penyamanager_%1").arg(Singletons::m_pLanguagesPrefixArray[Singletons::m_currentLangIndex]));
        qDebug() << ok;
        // installTranslator() will create a change event which will be sent to every single widget
        qApp->installTranslator(m_pTranslator);
    }
}

