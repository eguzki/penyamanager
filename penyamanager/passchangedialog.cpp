//

#include <QMessageBox>

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
    }
    //
    PassChangeDialog::~PassChangeDialog()
    {
        delete ui;
    }
    //
    void PassChangeDialog::on_buttonBox_accepted()
    {
        // Validate not empty fields
        QString plainPwd = this->ui->pwdLineEdit->text();
        QString repeatedPlainPwd = this->ui->repeatedPwdLineEdit->text();
        if (plainPwd.isEmpty() || repeatedPlainPwd.isEmpty()){
            QMessageBox::warning(this, "Data missing", "password fields cannot be empty");
            return;
        }
        if (plainPwd != repeatedPlainPwd){
            QMessageBox::warning(this, "Data not valid", "password fields do not match");
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
