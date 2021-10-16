#include <QAbstractButton>

#include "DataTypes.h"
#include "singletons.h"
#include "dialogmanager.h"

namespace PenyaManager {
    //
    DialogManager::DialogManager(QObject *parent) :
        QObject(parent),
        //m_pNumItemDialog(NULL),
        //m_pPassChangeDialog(NULL),
        m_pFileDialog(NULL),
        m_inactivityFlag(false)
    {

    }
    //
    void DialogManager::passChangeDialog(QWidget *parent, const PassChangeDialogCallback &callback)
    {
        Q_UNUSED(parent)
        Q_UNUSED(callback)
        //m_passChangeCallback = callback;
        //m_pPassChangeDialog = new PassChangeDialog(parent);
        ////makes sure the passChangeDialog is deleted automatically when closed
        //m_pPassChangeDialog->setAttribute(Qt::WA_DeleteOnClose);
        //m_pPassChangeDialog->open(this, SLOT(passChangeDialogClosed(int)));
    }
    //
    void DialogManager::passChangeDialogClosed(int res)
    {
        Q_UNUSED(res)
        //QString result;
        //if (m_pPassChangeDialog) {
        //    result = m_pPassChangeDialog->getPassword();
        //    m_pPassChangeDialog = NULL;
        //}
        //// only call callback when user pressed button
        //if (!m_inactivityFlag) {
        //    m_passChangeCallback(res, result);
        //}
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
        //} else if (m_pNumItemDialog) {
        //    m_pNumItemDialog->close();
        //    // m_pNumItemDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
        //    m_pNumItemDialog = NULL;
        //} else if (m_pPassChangeDialog) {
        //    m_pPassChangeDialog->close();
        //    // m_pPassChangeDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
        //    m_pPassChangeDialog = NULL;
        if (m_pFileDialog) {
            // triggers fileDialogRejected slot
            m_pFileDialog->close();
            // m_pFileDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
            m_pFileDialog = NULL;
        }
        m_inactivityFlag = false;
    }
}
