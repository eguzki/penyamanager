//

#include "singletons.h"
#include "timedmessagebox.h"

namespace PenyaManager {
    //
    TimedMessageBox::TimedMessageBox(QTimer *pInactivityTimer, const MessageBoxCallback &callback,
            QMessageBox::Icon icon, const QString &title, const QString &text,
            QMessageBox::StandardButtons buttons, QWidget *parent, Qt::WindowFlags f) :
        QMessageBox(icon, title, text, buttons, parent, f),
        m_pInactivityTimer(pInactivityTimer),
        m_callback(callback)
    {
        this->connect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
    }
    //
    void TimedMessageBox::OnButtonClicked(QAbstractButton *pButton)
    {
        finish();
        m_callback(pButton);
    }

    //
    void TimedMessageBox::OnTimeout()
    {
        finish();
    }

    //
    void TimedMessageBox::finish()
    {
        this->disconnect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
        // The object will be deleted when control returns to the event loop
        this->deleteLater();
        this->close();
    }

    //
    void TimedMessageBox::infoMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        // will be self-destroyed
        TimedMessageBox *pMsgBox = new TimedMessageBox(
                Singletons::m_pInactivityTimer, convertInfoMessageBox(callback),
                QMessageBox::Information, QString(), message, QMessageBox::Ok, parent, Qt::FramelessWindowHint);
        // connects buttonClicked signal
        pMsgBox->open(pMsgBox, SLOT(OnButtonClicked(QAbstractButton*)));
    }

    //
    void TimedMessageBox::infoMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        // will be self-destroyed
        TimedMessageBox *pMsgBox = new TimedMessageBox(
                Singletons::m_pInactivityTimer, convertInfoMessageBox(callback),
                QMessageBox::Information, QString("Penyamanager"), message, QMessageBox::Ok, parent);
        // connects buttonClicked signal
        pMsgBox->open(pMsgBox, SLOT(OnButtonClicked(QAbstractButton*)));
    }

    //
    void TimedMessageBox::criticalMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        // will be self-destroyed
        TimedMessageBox *pMsgBox = new TimedMessageBox(
                Singletons::m_pInactivityTimer, convertInfoMessageBox(callback),
                QMessageBox::Critical, QString(), message, QMessageBox::Ok, parent, Qt::FramelessWindowHint);
        // connects buttonClicked signal
        pMsgBox->open(pMsgBox, SLOT(OnButtonClicked(QAbstractButton*)));
    }

    //
    void TimedMessageBox::criticalMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        // will be self-destroyed
        TimedMessageBox *pMsgBox = new TimedMessageBox(
                Singletons::m_pInactivityTimer, convertInfoMessageBox(callback),
                QMessageBox::Critical, QString("Penyamanager"), message, QMessageBox::Ok, parent);
        // connects buttonClicked signal
        pMsgBox->open(pMsgBox, SLOT(OnButtonClicked(QAbstractButton*)));
    }

    //
    void TimedMessageBox::questionMessageBoxTitled(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback)
    {
        // will be self-destroyed
        TimedMessageBox *pMsgBox = new TimedMessageBox(
                Singletons::m_pInactivityTimer, convertQuestionMessageBox(callback),
                QMessageBox::Question, QString("Penyamanager"), message, QMessageBox::Yes|QMessageBox::No, parent);
        // connects buttonClicked signal
        pMsgBox->open(pMsgBox, SLOT(OnButtonClicked(QAbstractButton*)));
    }

    //
    void TimedMessageBox::questionMessageBox(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback)
    {
        // will be self-destroyed
        TimedMessageBox *pMsgBox = new TimedMessageBox(
                Singletons::m_pInactivityTimer, convertQuestionMessageBox(callback),
                QMessageBox::Question, QString(), message, QMessageBox::Yes|QMessageBox::No, parent, Qt::FramelessWindowHint);
        // connects buttonClicked signal
        pMsgBox->open(pMsgBox, SLOT(OnButtonClicked(QAbstractButton*)));
    }

    //
    MessageBoxCallback TimedMessageBox::convertInfoMessageBox(const InfoMessageBoxCallback &callback)
    {
        return [callback](QAbstractButton *pButton){ Q_UNUSED(pButton); callback(); };
    }
    //
    MessageBoxCallback TimedMessageBox::convertQuestionMessageBox(const QuestionMessageBoxCallback &callback)
    {
        return [callback](QAbstractButton *pButton)
        {
            QMessageBox::StandardButton standardButton = QMessageBox::Yes;
            if (pButton->text() != QWidget::tr("Yes")) {
                standardButton = QMessageBox::No;
            }
            callback(standardButton);
        };
    }
}
