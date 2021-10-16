#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QObject>

#include "DataTypes.h"
//#include "passchangedialog.h"

namespace PenyaManager {
    //
    typedef std::function<void(int res, QString passStr)> PassChangeDialogCallback;
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
            void passChangeDialog(QWidget *parent, const PassChangeDialogCallback &callback);
            //
            void getOpenFileName(QWidget *parent,
                    const QString &caption, const QString &directory,
                    const QString &filter, QFileDialog::FileMode filemode, const FileDialogCallback &callback);
            //
            void onInactivityTimeout();

        public slots:
            //
            void passChangeDialogClosed(int);
            //
            void fileDialogFileSelected(const QString &file);
            //
            void fileDialogRejected();

        private:
            //
            PassChangeDialogCallback        m_passChangeCallback;
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
