//

#include "passchangedialog.h"
#include "ui_passchangedialog.h"

namespace PenyaManager {
    //
    PassChangeDialog::PassChangeDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::PassChangeDialog),
        m_pwd()
    {
        ui->setupUi(this);
        // only numbers allowed
        QValidator *pIntValidator = new QIntValidator();
        this->ui->pwdLineEdit->setValidator(pIntValidator);
        QValidator *pRepeatedIntValidator = new QIntValidator();
        this->ui->repeatedPwdLineEdit->setValidator(pRepeatedIntValidator);
        this->ui->errorLabel->setHidden(true);
    }
    //
    PassChangeDialog::~PassChangeDialog()
    {
        delete ui;
    }
    //
    void PassChangeDialog::open(QObject *receiver, const char *member)
    {
        this->connect(this, SIGNAL(finished(int)), receiver, member);
        QDialog::open();
    }
    //
    void PassChangeDialog::on_buttonBox_accepted()
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

        m_pwd = plainPwd;
        this->accept();
    }
    //
    QString PassChangeDialog::getPassword()
    {
        return m_pwd;
    }
}
