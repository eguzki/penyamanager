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
        if (m_pFileDialog) {
            // triggers fileDialogRejected slot
            m_pFileDialog->close();
            // m_pFileDialog is deleted automatically (Qt::WA_DeleteOnClose is set)
            m_pFileDialog = NULL;
        }
        m_inactivityFlag = false;
    }
}
