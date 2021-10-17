//

#include <QIntValidator>
#include <QTimer>

#include <commons/singletons.h>

#include "timedpasschangedialog.h"
#include "ui_timedpasschangedialog.h"

namespace PenyaManager {
    //
    TimedPassChangeDialog::TimedPassChangeDialog(QTimer *pInactivityTimer,
                    const PassChangeDialogCallback &callback, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::TimedPassChangeDialog),
        m_pInactivityTimer(pInactivityTimer),
        m_callback(callback)
    {
        ui->setupUi(this);

        this->connect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(OnTimeout()));

        // only numbers allowed
        QValidator *pIntValidator = new QIntValidator();
        this->ui->pwdLineEdit->setValidator(pIntValidator);
        QValidator *pRepeatedIntValidator = new QIntValidator();
        this->ui->repeatedPwdLineEdit->setValidator(pRepeatedIntValidator);
        this->ui->errorLabel->setHidden(true);
    }
    //
    TimedPassChangeDialog::~TimedPassChangeDialog()
    {
        delete ui;
    }
    //
    void TimedPassChangeDialog::OnTimeout()
    {
        finish();
    }
    //
    void TimedPassChangeDialog::finish()
    {
        this->disconnect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
        // The object will be deleted when control returns to the event loop
        this->deleteLater();
        this->close();
    }
    //
    void TimedPassChangeDialog::on_buttonBox_rejected()
    {
        finish();
        m_callback(QDialog::Rejected, QString());
    }
    //
    void TimedPassChangeDialog::on_buttonBox_accepted()
    {
        // Validate not empty fields
        QString plainPwd = this->ui->pwdLineEdit->text();
        QString repeatedPlainPwd = this->ui->repeatedPwdLineEdit->text();
        if (plainPwd.isEmpty() || repeatedPlainPwd.isEmpty()){
            this->ui->errorLabel->setHidden(false);
            this->ui->errorLabel->setText(tr("password fields cannot be empty"));
            return;
        }
        if (plainPwd != repeatedPlainPwd){
            this->ui->errorLabel->setHidden(false);
            this->ui->errorLabel->setText(tr("password fields do not match"));
            return;
        }

        finish();
        m_callback(QDialog::Accepted, plainPwd);
    }
    //
    void TimedPassChangeDialog::passChangeDialog(QWidget *parent, const PassChangeDialogCallback &callback)
    {
        // will be self-destroyed
        TimedPassChangeDialog *pTimedPassChangeDialog = new TimedPassChangeDialog(
                Singletons::m_pInactivityTimer, callback, parent);
        pTimedPassChangeDialog->open();
    }
}
