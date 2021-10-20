//

#include <commons/singletons.h>

#include "timedfiledialog.h"

namespace PenyaManager {
    //
    TimedFileDialog::TimedFileDialog(QTimer *pInactivityTimer,
            QWidget *parent, const QString &caption, const QString &directory,
            const QString &filter, QFileDialog::AcceptMode acceptMode,
            const FileDialogCallback &callback) :
        QFileDialog(parent, caption, directory, filter),
        m_pInactivityTimer(pInactivityTimer),
        m_callback(callback)
    {
        this->setAcceptMode(acceptMode);
        this->connect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        this->connect(this, SIGNAL(filesSelected(const QStringList&)), this, SLOT(onFilesSelected(const QStringList&)));
        this->connect(this, SIGNAL(rejected()), this, SLOT(onRejected()));
    }
    //
    void TimedFileDialog::onTimeout()
    {
        finish();
    }
    //
    void TimedFileDialog::onRejected()
    {
        finish();
    }
    //
    void TimedFileDialog::finish()
    {
        this->disconnect(m_pInactivityTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        this->disconnect(this, SIGNAL(filesSelected(const QStringList&)), this, SLOT(onFilesSelected(const QStringList&)));
        this->disconnect(this, SIGNAL(rejected()), this, SLOT(onRejected()));
        // The object will be deleted when control returns to the event loop
        this->deleteLater();
        this->close();
    }
    //
    void TimedFileDialog::onFilesSelected(const QStringList &selected)
    {
        finish();
        if (selected.count() > 0) {
            m_callback(selected.first());
        }
    }
    //
    void TimedFileDialog::fileDialog(QWidget *parent,
                    const QString &caption, const QString &directory,
                    const QString &filter, QFileDialog::AcceptMode acceptMode, const FileDialogCallback &callback)
    {
        // will be self-destroyed
        TimedFileDialog *pTimedFileDialog = new TimedFileDialog(
                Singletons::m_pInactivityTimer, parent, caption, directory, filter, acceptMode,
                callback);
        pTimedFileDialog->open();
    }
}
