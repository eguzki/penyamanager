#ifndef TIMEDMEMBERDROPDIALOG_H
#define TIMEDMEMBERDROPDIALOG_H

#include <QTimer>
#include <QDialog>

namespace Ui {
    //
    class TimedMemberDropDialog;
}

namespace PenyaManager {
    //
    typedef std::function<void()> MemberDropCallback;
    //
    class TimedMemberDropDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit TimedMemberDropDialog(QTimer *pInactivityTimer, QString name,
                    const MemberDropCallback &callback, QWidget *parent);
            //
            virtual ~TimedMemberDropDialog();
            //
            static void memberDropDialog(QWidget *parent, QString name, const MemberDropCallback &callback);

        private slots:
            //
            void on_buttonBox_accepted();
            //
            void on_buttonBox_rejected();
            //
            void onTimeout();
            //
            void getConfirmationLineEditValue(QString);

        private:
            //
            void finish();

        private:
            //
            Ui::TimedMemberDropDialog       *ui;
            //
            QTimer                          *m_pInactivityTimer;
            //
            MemberDropCallback              m_callback;
            //
            QString                         m_name;
    };
}

#endif // TIMEDPASSCHANGEDIALOG_H
