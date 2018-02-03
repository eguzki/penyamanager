//

#include <QPushButton>
#include <mustache.h>
#include <QMessageBox>

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "depositwindow.h"
#include "ui_depositwindow.h"

namespace PenyaManager {
    //
    DepositWindow::DepositWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::DepositWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback),
        m_depositValue(0.0),
        m_decimalPosition(0)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        this->connect(this->ui->pushButton_00, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 0));
        this->connect(this->ui->pushButton_01, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 1));
        this->connect(this->ui->pushButton_02, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 2));
        this->connect(this->ui->pushButton_03, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 3));
        this->connect(this->ui->pushButton_04, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 4));
        this->connect(this->ui->pushButton_05, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 5));
        this->connect(this->ui->pushButton_06, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 6));
        this->connect(this->ui->pushButton_07, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 7));
        this->connect(this->ui->pushButton_08, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 8));
        this->connect(this->ui->pushButton_09, &QPushButton::clicked, std::bind(&DepositWindow::onPushButton_number_clicked, this, 9));
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
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_pCurrMember->m_id);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kDashboard,
                    QString("Unable to find owner by id %1").arg(Singletons::m_pCurrMember->m_id));
            return;
        }

        MemberPtr pCurrMemberPtr = pMemberResultPtr->m_member;
        Singletons::m_pCurrMember = pCurrMemberPtr;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        // Current deposit reset
        m_depositValue = 0.0;
        m_decimalPosition = 0;
        this->ui->depositLabel->setText("0.00 €");
        this->ui->newBalanceLabel->setText(QString("%1 €").arg(QString::number(pCurrMemberPtr->m_balance, 'f', 2)));
    }
    //
    void DepositWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
    }
    //
    void DepositWindow::on_confirmButton_clicked()
    {
        if (m_depositValue <= 0){
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Deposit not valid"), [](){});
            return;
        }

        Singletons::m_pDialogManager->questionMessageBox(this,
                tr("Create deposit for %1 €?").arg(QString::number(m_depositValue, 'f', 2)),
                std::bind(&DepositWindow::onDepositConfirmed, this, _1)
                );
    }
    //
    void DepositWindow::onDepositConfirmed(QMessageBox::StandardButton answerButton)
    {
        if (answerButton == QMessageBox::No){
            return;
        }

        m_depositValue = std::trunc(100 * m_depositValue) / 100;

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        // Create deposit info
        DepositResultPtr pDepositResultPtr = Singletons::m_pServices->createDeposit(pCurrMemberPtr, m_depositValue);
        if (pDepositResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        if (!pDepositResultPtr->m_deposit) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDeposit,
                    QString("createDeposit. amount %1").arg(m_depositValue, 0, 'f', 2));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // Update member balance
        QString description = GuiUtils::invoiceAccountDescription(pDepositResultPtr->m_deposit->m_id);
        bool transactionOk = Singletons::m_pServices->createAccountTransaction(pCurrMemberPtr->m_id, m_depositValue, description, TransactionType::Deposit);
        if (!transactionOk) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDeposit,
                    QString("createaccounttransaction. amount %1").arg(m_depositValue, 0, 'f', 2));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDeposit,
                QString("Deposit id %1. Amount %2").arg(pDepositResultPtr->m_deposit->m_id).arg(QString::number(m_depositValue, 'f', 2)));
        // print deposit
        printDeposit(pCurrMemberPtr, pDepositResultPtr->m_deposit);
        Singletons::m_pDialogManager->infoMessageBox(this,
                tr("Deposit for %1 € created sucessfully").arg(QString::number(m_depositValue, 'f', 2)),
                std::bind(&DepositWindow::onDepositCreated, this)
                );
    }
    //
    void DepositWindow::onDepositCreated()
    {
        // Go to dashboard window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void DepositWindow::updateNewBalanceLabel(double deposit)
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        this->ui->newBalanceLabel->setText(QString("%1 €").arg(QString::number(pCurrMemberPtr->m_balance + deposit, 'f', 2)));
    }
    //
    void DepositWindow::onPushButton_number_clicked(Uint32 num)
    {
        // Check number is not too high and few decimals
        if (m_depositValue > std::pow(10, 7))
        {
            // do not allow "big" numbers
            return;
        }

        switch(m_decimalPosition) {
            case 0:
              {
                m_depositValue = m_depositValue*10 + num;
                break;
              }
            case 1:
              {
                bool ok;
                // needs to be done this way, because float(7)/10 = 0.6999999
                QString depositStr(QString::number(m_depositValue).append(".").append(QString::number(num)));
                m_depositValue = depositStr.toDouble(&ok);
                Q_ASSERT(ok);
                m_decimalPosition++;
                break;
              }
            case 2:
              {
                bool ok;
                // needs to be done this way, because float(7)/10 = 0.6999999
                QString depositStr(QString::number(m_depositValue, 'f', 1).append(QString::number(num)));
                m_depositValue = depositStr.toDouble(&ok);
                Q_ASSERT(ok);
                m_decimalPosition++;
                break;
              }
            default:
                return;
        }
        this->ui->depositLabel->setText(QString("%1 €").arg(QString::number(m_depositValue, 'f', 2)));
        updateNewBalanceLabel(m_depositValue);
    }
    //
    void DepositWindow::on_pushButton_coma_clicked()
    {
        switch(m_decimalPosition) {
            case 0:
                m_decimalPosition++;
                break;
            case 1:
            case 2:
            default:
                return;
        }
    }
    //
    void DepositWindow::on_pushButton_C_clicked()
    {
        this->ui->depositLabel->setText("0.00 €");
        m_decimalPosition = 0;
        m_depositValue = 0.0;
        updateNewBalanceLabel(0.0);
    }
    //
    void DepositWindow::printDeposit(const MemberPtr &pMemberPtr, const DepositPtr &pDepositPtr)
    {
        QFile depositTemplateFile(":resources/deposit.html");
        if (!depositTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            Singletons::m_pLogger->Error(pMemberPtr->m_id, PenyaManager::LogAction::kDeposit, QString("deposit.html not found"));
            return;
        }
        QTextStream depositTemplateStream(&depositTemplateFile);
        depositTemplateStream.setCodec("UTF-8");
        QString depositTemplate = depositTemplateStream.readAll();
        QString depositHtml = renderDepositTemplate(depositTemplate, pMemberPtr, pDepositPtr);
        GuiUtils::printText(depositHtml);
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
        depositData["memberid"] = pMemberPtr->m_username;
        depositData["memberName"] = QString("%1 %2 %3").arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname1).arg(pMemberPtr->m_surname2);
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pDepositPtr->m_date.toLocalTime(), QLocale::NarrowFormat);
        depositData["dateValue"] = dateLocalized;
        depositData["depositTotal"] = QString("%1 €").arg(QString::number(pDepositPtr->m_total, 'f', 2));
        QString depositHtml = Mustache::renderTemplate(depositTemplate, depositData);
        return depositHtml;
    }
    //
    void DepositWindow::on_newinvoiceButton_clicked()
    {
        //call new invoice window
        m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
    }
    //
    void DepositWindow::on_tableReservationButton_clicked()
    {
        // call table reservation window
        m_switchCentralWidgetCallback(WindowKey::kTableReservationViewWindowKey);

    }
    //
    void DepositWindow::on_invoicesPushButton_clicked()
    {
        // call invoices window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);

    }
    //
    void DepositWindow::on_accountButton_clicked()
    {
        // call account window
        m_switchCentralWidgetCallback(WindowKey::kAccountViewWindowKey);
    }
    //
    void DepositWindow::on_exitButton_clicked()
    {
        // call login window on exit
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
}

