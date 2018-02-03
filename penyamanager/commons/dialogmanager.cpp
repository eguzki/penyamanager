#include <QAbstractButton>

#include "DataTypes.h"
#include "dialogmanager.h"

namespace PenyaManager {
    //
    DialogManager::DialogManager(QObject *parent) :
        QObject(parent),
        m_pMsgBox(NULL),
        m_pNumItemDialog(NULL),
        m_pPassChangeDialog(NULL),
        m_pFileDialog(NULL),
        m_inactivityFlag(false)
    {

    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    void DialogManager::questionMessageBoxTitled(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback)
    {
        m_questionCallback = callback;
        m_pMsgBox = new QMessageBox(QMessageBox::Question, QString("Penyamanager"), message, QMessageBox::Yes|QMessageBox::No, parent);
        //makes sure the msgbox is deleted automatically when closed
        m_pMsgBox->setAttribute(Qt::WA_DeleteOnClose);
        // The right way is not to manually translate those strings. Qt already includes translations.
        m_pMsgBox->setButtonText(QMessageBox::Yes, QWidget::tr("Yes"));
        m_pMsgBox->setButtonText(QMessageBox::No, QWidget::tr("No"));
        m_pMsgBox->open(this, SLOT(questionMsgBoxClosed(QAbstractButton*)));
    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    void DialogManager::questionMessageBox(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback)
    {
        m_questionCallback = callback;
        m_pMsgBox = new QMessageBox(QMessageBox::Question, QString(), message, QMessageBox::Yes|QMessageBox::No, parent, Qt::FramelessWindowHint);
        //makes sure the msgbox is deleted automatically when closed
        m_pMsgBox->setAttribute(Qt::WA_DeleteOnClose);
        // The right way is not to manually translate those strings. Qt already includes translations.
        m_pMsgBox->setButtonText(QMessageBox::Yes, QWidget::tr("Yes"));
        m_pMsgBox->setButtonText(QMessageBox::No, QWidget::tr("No"));
        m_pMsgBox->open(this, SLOT(questionMsgBoxClosed(QAbstractButton*)));
    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    //
    void DialogManager::questionMsgBoxClosed(QAbstractButton *pButton)
    {
        // msgbox is deleted automatically (Qt::WA_DeleteOnClose is set)
        m_pMsgBox = NULL;
        if (!m_inactivityFlag) {
            QMessageBox::StandardButton standardButton = QMessageBox::Yes;
            if (pButton->text() != QWidget::tr("Yes")) {
                standardButton = QMessageBox::No;
            }
            m_questionCallback(standardButton);
        }
    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    //
    void DialogManager::criticalMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        m_infoCallback = callback;
        m_pMsgBox = new QMessageBox(QMessageBox::Critical, QString("Penyamanager"), message, QMessageBox::Ok, parent);
        //makes sure the msgbox is deleted automatically when closed
        m_pMsgBox->setAttribute(Qt::WA_DeleteOnClose);
        m_pMsgBox->open(this, SLOT(infoMsgBoxClosed()));
    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    //
    void DialogManager::criticalMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        m_infoCallback = callback;
        m_pMsgBox = new QMessageBox(QMessageBox::Critical, QString(), message, QMessageBox::Ok, parent, Qt::FramelessWindowHint);
        //makes sure the msgbox is deleted automatically when closed
        m_pMsgBox->setAttribute(Qt::WA_DeleteOnClose);
        m_pMsgBox->open(this, SLOT(infoMsgBoxClosed()));
    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    //
    void DialogManager::infoMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        m_infoCallback = callback;
        m_pMsgBox = new QMessageBox(QMessageBox::Information, QString("Penyamanager"), message, QMessageBox::Ok, parent);
        //makes sure the msgbox is deleted automatically when closed
        m_pMsgBox->setAttribute(Qt::WA_DeleteOnClose);
        m_pMsgBox->open(this, SLOT(infoMsgBoxClosed()));
    }
    // Non blocking version of messagebox
    // required when inactivity timeout triggers when messagebox is displayed and not answered yet
    //
    void DialogManager::infoMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback)
    {
        m_infoCallback = callback;
        m_pMsgBox = new QMessageBox(QMessageBox::Information, QString(), message, QMessageBox::Ok, parent, Qt::FramelessWindowHint);
        //makes sure the msgbox is deleted automatically when closed
        m_pMsgBox->setAttribute(Qt::WA_DeleteOnClose);
        m_pMsgBox->open(this, SLOT(infoMsgBoxClosed()));
    }
    //
    void DialogManager::infoMsgBoxClosed()
    {
        // msgbox is deleted automatically (Qt::WA_DeleteOnClose is set)
        m_pMsgBox = NULL;
        // only call callback when user pressed button
        if (!m_inactivityFlag) {
            m_infoCallback();
        }
    }
    //
    // Non blocking version of NumItemDialog
    // required when inactivity timeout triggers when NumItemDialog is displayed and not answered yet
    void DialogManager::numItemDialog(QWidget *parent, const QString &message, const NumItemDialogCallback &callback)
    {
        m_numItemCallback = callback;
        m_pNumItemDialog = new NumItemDialog(parent, message);
        //makes sure the numitemdialog is deleted automatically when closed
        m_pNumItemDialog->setAttribute(Qt::WA_DeleteOnClose);
        m_pNumItemDialog->open(this, SLOT(numItemDialogClosed()));
    }
    //
    void DialogManager::numItemDialogClosed()
    {
        QString result;
        if (m_pNumItemDialog) {
            result = m_pNumItemDialog->getKeyStr();
            m_pNumItemDialog = NULL;
        }
        // only call callback when user pressed button
        if (!m_inactivityFlag) {
            m_numItemCallback(result);
        }
    }
    //
    void DialogManager::passChangeDialog(QWidget *parent, const PassChangeDialogCallback &callback)
    {
        m_passChangeCallback = callback;
        m_pPassChangeDialog = new PassChangeDialog(parent);
        //makes sure the passChangeDialog is deleted automatically when closed
        m_pPassChangeDialog->setAttribute(Qt::WA_DeleteOnClose);
        m_pPassChangeDialog->open(this, SLOT(passChangeDialogClosed(int)));
    }
    //
    void DialogManager::passChangeDialogClosed(int res)
    {
        QString result;
        if (m_pPassChangeDialog) {
            result = m_pPassChangeDialog->getPassword();
            m_pPassChangeDialog = NULL;
        }
        // only call callback when user pressed button
        if (!m_inactivityFlag) {
            m_passChangeCallback(res, result);
        }
    }
    //
    void DialogManager::getOpenFileName(QWidget *parent,
            const QString &caption, const QString &directory,
            const QString &filter, QFileDialog::FileMode filemode, const FileDialogCallback &callback)
    {
        m_fileDialogCallback = callback;
        m_pFileDialog = new QFileDialog(parent, caption, directory, filter);
        m_pFileDialog->setFileMode(filemode);
        //makes sure the m_pFileDialog is deleted automatically when closed
        m_pFileDialog->setAttribute(Qt::WA_DeleteOnClose);
        this->connect(m_pFileDialog, SIGNAL(rejected()), this, SLOT(fileDialogRejected()));
        m_pFileDialog->open(this, SLOT(fileDialogFileSelected(const QString&)));
    }
    //
    // When dialog is rejected, slot callback in open method is not called
    void DialogManager::fileDialogRejected()
    {
        // m_pFileDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
        m_pFileDialog = NULL;
    }

    //
    void DialogManager::fileDialogFileSelected(const QString &file)
    {
        // m_pFileDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
        m_pFileDialog = NULL;
        // only call callback when user pressed button
        if (!m_inactivityFlag) {
            m_fileDialogCallback(file);
        }
    }
    //
    // When inactivity timeout is triggered,
    // registrered messagebox callback is not called,
    // closing messagebox window and finishing event loop
    void DialogManager::onInactivityTimeout()
    {
        m_inactivityFlag = true;
        // More than one of the dialog types should not be active,
        // otherwise, code bug
        if (m_pMsgBox) {
            // does not trigger msgBoxClosed slot when question dialog box
            // but triggers infoMsgBoxClosed slot when info or critical dialog box
            m_pMsgBox->close();
            // msgbox is deleted automatically (Qt::WA_DeleteOnClose is set)
            m_pMsgBox = NULL;
        } else if (m_pNumItemDialog) {
            m_pNumItemDialog->close();
            // m_pNumItemDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
            m_pNumItemDialog = NULL;
        } else if (m_pPassChangeDialog) {
            m_pPassChangeDialog->close();
            // m_pPassChangeDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
            m_pPassChangeDialog = NULL;
        } else if (m_pFileDialog) {
            // triggers fileDialogRejected slot
            m_pFileDialog->close();
            // m_pFileDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
            m_pFileDialog = NULL;
        }
        m_inactivityFlag = false;
    }
}
