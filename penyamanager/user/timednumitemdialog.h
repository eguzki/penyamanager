#ifndef TIMEDNUMITEMDIALOG_H
#define TIMEDNUMITEMDIALOG_H

#include <QDialog>
#include <QTimer>

#include <commons/DataTypes.h>

namespace Ui {
    class TimedNumItemDialog;
}

namespace PenyaManager {

    //
    typedef std::function<void(QString resultStr)> NumItemDialogCallback;
    //
    class TimedNumItemDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit TimedNumItemDialog(QTimer *pInactivityTimer, const NumItemDialogCallback &callback, 
                    QWidget *parent, QString title, bool passMode = false, Uint32 maxDigits = 5);
            //
            virtual ~TimedNumItemDialog();
            //
            static void numItemDialog(QWidget *parent, QString title, const NumItemDialogCallback &callback,
                    bool passMode = false, Uint32 maxDigits = 5);

        private slots:
            //
            void onButtonClick(Uint32 count);
            //
            void on_toolButton_C_clicked();
            //
            void OnTimeout();
            //
            void OnDone();

        private:
            //
            void finish();

        private:
            //
            Ui::TimedNumItemDialog          *ui;
            //
            QTimer                          *m_pInactivityTimer;
            //
            NumItemDialogCallback           m_callback;
            //
            Int32                           m_maxDigits;
            //
            QString                         m_keyStr;
            //
            bool                            m_passMode;
    };

}

#endif // TIMEDNUMITEMDIALOG_H
