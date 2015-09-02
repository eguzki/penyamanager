//

#include <QMessageBox>
#include <mustache.h>
#include <QsLog.h>

#include "guiutils.h"
#include "singletons.h"
#include "depositwindow.h"
#include "ui_depositwindow.h"

namespace PenyaManager {
    //
    DepositWindow::DepositWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::DepositWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        this->connect(this->ui->pushButton_00, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 0));
        this->connect(this->ui->pushButton_01, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 1));
        this->connect(this->ui->pushButton_02, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 2));
        this->connect(this->ui->pushButton_03, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 3));
        this->connect(this->ui->pushButton_04, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 4));
        this->connect(this->ui->pushButton_05, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 5));
        this->connect(this->ui->pushButton_06, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 6));
        this->connect(this->ui->pushButton_07, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 7));
        this->connect(this->ui->pushButton_08, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 8));
        this->connect(this->ui->pushButton_09, &QPushButton::clicked, std::bind(&DepositWindow::on_pushButton_number_clicked, this, 9));
    }
    //
    DepositWindow::~DepositWindow()
    {
        delete ui;
    }
    //
    void DepositWindow::init()
    {
        //
        // Loading User profile
        //

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        // Current deposit reset
        this->ui->depositLabel->setText("");
        this->ui->newBalanceLabel->setText(QString::number(pCurrMemberPtr->m_balance, 'f', 2));

        //
        // Show
        //

        show();
    }
    //
    void DepositWindow::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void DepositWindow::on_backButton_clicked()
    {
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void DepositWindow::on_confirmButton_clicked()
    {
        bool ok;
        double deposit = this->ui->depositLabel->text().toDouble(&ok);

        if (ok)
        {
            MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
            // Create deposit info
            DepositPtr pDepositPtr = Singletons::m_pServices->createDeposit(pCurrMemberPtr, deposit);
            if (!pDepositPtr) {
                // TODO handle error
                QMessageBox::warning(this, "Could not create deposit", "Contact administrator");
                return;
            }

            // Update member balance
            QString description = QString("deposit id: %1").arg(pDepositPtr->m_id);
            Singletons::m_pServices->createAccountTransaction(pCurrMemberPtr->m_id, deposit, description, TransactionType::Deposit);
            QLOG_INFO() << QString("[Deposit] User %1 deposit ID %2").arg(pCurrMemberPtr->m_id).arg(pDepositPtr->m_id);
            // print deposit
            printDeposit(pCurrMemberPtr, pDepositPtr);
            QMessageBox::information(this, "Deposit", tr("Deposit done"));
        }

        // Go to main window
        switchWindow(WindowKey::kMainWindowKey);
    }
    //
    void DepositWindow::updateNewBalanceLabel(double deposit)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->ui->newBalanceLabel->setText(QString::number(pCurrMemberPtr->m_balance + deposit, 'f', 2));
    }
    //
    void DepositWindow::on_pushButton_number_clicked(Uint32 num)
    {
        // Check number is not too high and few decimals
        if (this->ui->depositLabel->text().length() > 8)
        {
            // do not allow "big" numbers
            return;
        }

        bool ok;
        QString newDepositText(this->ui->depositLabel->text().append(QString::number(num)));
        double deposit = newDepositText.toDouble(&ok);

        if (ok)
        {
            this->ui->depositLabel->setText(newDepositText);
        }
        updateNewBalanceLabel(deposit);
    }
    //
    void DepositWindow::on_pushButton_coma_clicked()
    {
        // check decimal point does not exist and there is at least one char
        if (!this->ui->depositLabel->text().contains(".") && this->ui->depositLabel->text().length() > 0)
        {
            this->ui->depositLabel->setText(this->ui->depositLabel->text().append("."));
        };
    }
    //
    void DepositWindow::on_pushButton_C_clicked()
    {
        this->ui->depositLabel->setText("");
        updateNewBalanceLabel(0.0);
    }
    //
    void DepositWindow::printDeposit(const MemberPtr &pMemberPtr, const DepositPtr &pDepositPtr)
    {
        QFile depositTemplateFile(":resources/deposit.html");
        if (!depositTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QLOG_ERROR() << QString("[Deposit] deposit.html not found");
            return;
        }
        QTextStream depositTemplateStream(&depositTemplateFile);
        QString depositTemplate = depositTemplateStream.readAll();
        QString depositHtml = renderDepositTemplate(depositTemplate, pMemberPtr, pDepositPtr);
        GuiUtils::printText(depositHtml);
        QLOG_INFO() << QString("[Print] print deposit user %1 deposit %2").arg(pMemberPtr->m_id).arg(pDepositPtr->m_id);
    }
    //
    QString DepositWindow::renderDepositTemplate(const QString &depositTemplate, const MemberPtr &pMemberPtr, const DepositPtr &pDepositPtr)
    {
        QVariantHash depositData;
        // Label
        depositData["depositLabel"] = tr("Deposit Id");
        depositData["memberidLabel"] = tr("Member Id");
        depositData["memberNameLabel"] = tr("Member Name");
        depositData["dateLabel"] = tr("Date");
        depositData["depositTotalLabel"] = tr("Deposit Total");
        // deposit info
        depositData["depositId"] = pDepositPtr->m_id;
        depositData["memberid"] = pMemberPtr->m_id;
        depositData["memberName"] = QString("%1 %2").arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname);
        depositData["dateValue"] = pDepositPtr->m_date;
        depositData["depositTotal"] = pDepositPtr->m_total;
        QString depositHtml = Mustache::renderTemplate(depositTemplate, depositData);
        return depositHtml; 
    }
}
