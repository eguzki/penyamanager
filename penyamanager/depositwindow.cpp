//

#include <QMessageBox>

#include "utils.h"
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
}
