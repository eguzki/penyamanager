//

#include <commons/singletons.h>

#include "timednumitemdialog.h"
#include "ui_timednumitemdialog.h"

namespace PenyaManager {

    // Will be self destroyed
    TimedNumItemDialog::TimedNumItemDialog(QTimer *pInactivityTimer, const NumItemDialogCallback &callback,
            QWidget *parent, QString title, bool passMode, Uint32 maxDigits) :
        QDialog(parent),
        ui(new Ui::TimedNumItemDialog),
        m_pInactivityTimer(pInactivityTimer),
        m_callback(callback),
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
        this->connect(this->ui->toolButton_0, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 0));
        this->connect(this->ui->toolButton_1, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 1));
        this->connect(this->ui->toolButton_2, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 2));
        this->connect(this->ui->toolButton_3, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 3));
        this->connect(this->ui->toolButton_4, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 4));
        this->connect(this->ui->toolButton_5, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 5));
        this->connect(this->ui->toolButton_6, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 6));
        this->connect(this->ui->toolButton_7, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 7));
        this->connect(this->ui->toolButton_8, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 8));
        this->connect(this->ui->toolButton_9, &QToolButton::clicked, std::bind(&TimedNumItemDialog::onButtonClick, this, 9));
        this->connect(this->ui->toolButton_Done, SIGNAL(clicked()), this, SLOT(OnDone()));

        this->connect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(OnTimeout()));

        this->ui->numDisplayLabel->setText("");
        this->ui->toolButton_Done->setEnabled(false);
    }
    //
    TimedNumItemDialog::~TimedNumItemDialog()
    {
        delete ui;
    }
    //
    void TimedNumItemDialog::OnTimeout()
    {
        finish();
    }
    //
    void TimedNumItemDialog::OnDone()
    {
        finish();
        m_callback(this->m_keyStr);
    }
    //
    void TimedNumItemDialog::finish()
    {
        this->disconnect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
        // The object will be deleted when control returns to the event loop
        this->deleteLater();
        this->close();
    }
    //
    void TimedNumItemDialog::onButtonClick(Uint32 num)
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
    void TimedNumItemDialog::on_toolButton_C_clicked()
    {
        this->ui->numDisplayLabel->setText("");
        this->m_keyStr = QString("");
        this->ui->toolButton_Done->setEnabled(false);
    }
    //
    void TimedNumItemDialog::numItemDialog(QWidget *parent, QString title, const NumItemDialogCallback &callback,
            bool passMode, Uint32 maxDigits)
    {
        // will be self-destroyed
        TimedNumItemDialog *pTimedNumItemDialog = new TimedNumItemDialog(
                Singletons::m_pInactivityTimer, callback, parent, title, passMode, maxDigits);
        pTimedNumItemDialog->open();
    }
}
