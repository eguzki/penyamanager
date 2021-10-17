#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QObject>

#include "DataTypes.h"

namespace PenyaManager {
    //
    typedef std::function<void(QString filename)> FileDialogCallback;
    //
    class DialogManager : public QObject
    {
        Q_OBJECT

        public:
            //
            explicit DialogManager(QObject *parent = 0);
            //
            void getOpenFileName(QWidget *parent,
                    const QString &caption, const QString &directory,
                    const QString &filter, QFileDialog::FileMode filemode, const FileDialogCallback &callback);
            //
            void onInactivityTimeout();

        public slots:
            //
            void fileDialogFileSelected(const QString &file);
            //
            void fileDialogRejected();

        private:
            //
            FileDialogCallback              m_fileDialogCallback;
            //
            //PassChangeDialog               *m_pPassChangeDialog;
            //
            QFileDialog                    *m_pFileDialog;
            //
            bool                            m_inactivityFlag;
    };
}

#endif // DIALOGMANAGER_H
