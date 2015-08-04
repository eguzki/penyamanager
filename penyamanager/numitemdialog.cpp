//

#include <functional>
using namespace std::placeholders;
#include <QMessageBox>

#include "numitemdialog.h"
#include "ui_numitemdialog.h"

namespace PenyaManager {

    //
    NumItemDialog::NumItemDialog(QWidget *parent, bool passMode, Uint32 maxDigits) :
        QDialog(parent),
        ui(new Ui::NumItemDialog),
        m_maxDigits(maxDigits),
        m_keyStr(""),
        m_passMode(passMode)
    {
        ui->setupUi(this);
        this->connect(this->ui->toolButton_0, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 0));
        this->connect(this->ui->toolButton_1, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 1));
        this->connect(this->ui->toolButton_2, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 2));
        this->connect(this->ui->toolButton_3, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 3));
        this->connect(this->ui->toolButton_4, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 4));
        this->connect(this->ui->toolButton_5, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 5));
        this->connect(this->ui->toolButton_6, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 6));
        this->connect(this->ui->toolButton_7, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 7));
        this->connect(this->ui->toolButton_8, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 8));
        this->connect(this->ui->toolButton_9, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 9));

        this->ui->numDisplayLabel->setText("");
    }

    //
    NumItemDialog::~NumItemDialog()
    {
        delete ui;
    }

    //
    void NumItemDialog::onButtonClick(Uint32 num)
    {
        // Check number is not too high
        if (this->m_keyStr.length() >= this->m_maxDigits)
        {
            // do not allow "big" numbers
            return;
        }

        this->m_keyStr.append(QString::number(num));
        if (m_passMode)
        {
            QString hiddenPass;
            hiddenPass.fill('*', this->m_keyStr.length() - 1);
            hiddenPass.append(this->m_keyStr.at(this->m_keyStr.length() - 1));
            this->ui->numDisplayLabel->setText(hiddenPass);
        } else {
            this->ui->numDisplayLabel->setText(this->m_keyStr);
        }

    }
    //
    void NumItemDialog::on_toolButton_C_clicked()
    {
        this->ui->numDisplayLabel->setText("");
        this->m_keyStr = QString("");
    }
    //
    QString NumItemDialog::getKeyStr()
    {
        return this->m_keyStr;
    }
    //
    Uint32 NumItemDialog::getKey()
    {
        return this->m_keyStr.toUInt();
    }
}
