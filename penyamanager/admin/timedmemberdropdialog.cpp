//

#include <QIntValidator>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTimer>
#include <QEvent>

#include <commons/singletons.h>

#include "timedmemberdropdialog.h"
#include "ui_timedmemberdropdialog.h"

namespace PenyaManager {
    //
    TimedMemberDropDialog::TimedMemberDropDialog(QTimer *pInactivityTimer, QString name,
                    const MemberDropCallback &callback, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::TimedMemberDropDialog),
        m_pInactivityTimer(pInactivityTimer),
        m_callback(callback),
        m_name(name)
    {
        ui->setupUi(this);

        this->connect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        this->connect(this->ui->confirmationLineEdit, SIGNAL(textChanged(QString)), this, SLOT(getConfirmationLineEditValue(QString)));

        QPushButton *pOkButton = this->ui->buttonBox->button(QDialogButtonBox::Ok);
        pOkButton->setEnabled(false);

        this->ui->infoLabel->setText(tr("Type the member name for confirmation: %1").arg(this->m_name));
    }
    //
    TimedMemberDropDialog::~TimedMemberDropDialog()
    {
        delete ui;
    }
    //
    void TimedMemberDropDialog::onTimeout()
    {
        finish();
    }
    //
    void TimedMemberDropDialog::finish()
    {
        this->disconnect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        // The object will be deleted when control returns to the event loop
        this->deleteLater();
        this->close();
    }
    //
    void TimedMemberDropDialog::on_buttonBox_rejected()
    {
        finish();
    }
    //
    void TimedMemberDropDialog::on_buttonBox_accepted()
    {
        // Validate not empty fields
        finish();
        m_callback();
    }
    //
    void TimedMemberDropDialog::getConfirmationLineEditValue(QString input)
    {
        QPushButton *pOkButton = this->ui->buttonBox->button(QDialogButtonBox::Ok);
        pOkButton->setEnabled(input == this->m_name.trimmed());
    }
    //
    void TimedMemberDropDialog::memberDropDialog(QWidget *parent, QString name, const MemberDropCallback &callback)
    {
        // will be self-destroyed
        TimedMemberDropDialog *pTimedMemberDropDialog = new TimedMemberDropDialog(
                Singletons::m_pInactivityTimer, name, callback, parent);
        pTimedMemberDropDialog->open();
    }
}
