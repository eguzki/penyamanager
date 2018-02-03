#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QObject>

#include "DataTypes.h"
#include "numitemdialog.h"
#include "passchangedialog.h"

namespace PenyaManager {
    //
    typedef std::function<void(QMessageBox::StandardButton answerButton)> QuestionMessageBoxCallback;
    //
    typedef std::function<void()> InfoMessageBoxCallback;
    //
    typedef std::function<void(QString resultStr)> NumItemDialogCallback;
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
            void questionMessageBoxTitled(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback);
            //
            void questionMessageBox(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback);
            //
            void criticalMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            void criticalMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            void infoMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            void infoMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            void numItemDialog(QWidget *parent, const QString &message, const NumItemDialogCallback &callback);
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
            void questionMsgBoxClosed(QAbstractButton *pButton);
            //
            void infoMsgBoxClosed();
            //
            void numItemDialogClosed();
            //
            void passChangeDialogClosed(int);
            //
            void fileDialogFileSelected(const QString &file);
            //
            void fileDialogRejected();

        private:
            //
            QuestionMessageBoxCallback      m_questionCallback;
            //
            InfoMessageBoxCallback          m_infoCallback;
            //
            NumItemDialogCallback           m_numItemCallback;
            //
            PassChangeDialogCallback        m_passChangeCallback;
            //
            FileDialogCallback              m_fileDialogCallback;
            //
            QMessageBox                    *m_pMsgBox;
            //
            NumItemDialog                  *m_pNumItemDialog;
            //
            PassChangeDialog               *m_pPassChangeDialog;
            //
            QFileDialog                    *m_pFileDialog;
            //
            bool                            m_inactivityFlag;
    };
}

#endif // DIALOGMANAGER_H
