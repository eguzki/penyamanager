#ifndef TIMEDPASSCHANGEDIALOG_H
#define TIMEDPASSCHANGEDIALOG_H

#include <QDialog>

namespace Ui {
    //
    class TimedPassChangeDialog;
}

namespace PenyaManager {
    //
    typedef std::function<void(int res, QString passStr)> PassChangeDialogCallback;
    //
    class TimedPassChangeDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit TimedPassChangeDialog(QTimer *pInactivityTimer,
                    const PassChangeDialogCallback &callback, QWidget *parent);
            //
            virtual ~TimedPassChangeDialog();
            //
            static void passChangeDialog(QWidget *parent, const PassChangeDialogCallback &callback);

        private slots:
            //
            void on_buttonBox_accepted();
            //
            void on_buttonBox_rejected();
            //
            void OnTimeout();

        private:
            //
            void finish();

        private:
            //
            Ui::TimedPassChangeDialog       *ui;
            //
            QTimer                          *m_pInactivityTimer;
            //
            PassChangeDialogCallback        m_callback;
            //
            QString                         m_pwd;
    };
}

#endif // TIMEDPASSCHANGEDIALOG_H
