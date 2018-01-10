//

#include "numitemdialog.h"
#include "ui_numitemdialog.h"

namespace PenyaManager {

    //
    NumItemDialog::NumItemDialog(QWidget *parent, QString title, bool passMode, Uint32 maxDigits) :
        QDialog(parent),
        ui(new Ui::NumItemDialog),
        m_maxDigits(maxDigits),
        m_keyStr(""),
        m_passMode(passMode)
    {
        ui->setupUi(this);
        if (title.length() > 0) {
            this->ui->displayLabel->setText(title);
        } else {
            this->ui->displayLabel->setHidden(true);
        }
        this->setWindowFlags(Qt::Dialog|Qt::SubWindow|Qt::FramelessWindowHint);
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
        this->ui->toolButton_Done->setEnabled(false);
    }

    //
    NumItemDialog::~NumItemDialog()
    {
        delete ui;
    }
    //
    void NumItemDialog::open(QObject *receiver, const char *member)
    {
        this->connect(this, SIGNAL(finished(int)), receiver, member);
        QDialog::open();
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

        if (!this->ui->toolButton_Done->isEnabled()) {
            this->ui->toolButton_Done->setEnabled(true);
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
        this->ui->toolButton_Done->setEnabled(false);
    }
    //
    QString NumItemDialog::getKeyStr()
    {
        return this->m_keyStr;
    }
}
