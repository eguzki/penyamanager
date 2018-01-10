#ifndef NUMITEMDIALOG_H
#define NUMITEMDIALOG_H

#include <QDialog>

#include "DataTypes.h"

namespace Ui {
    class NumItemDialog;
}

namespace PenyaManager {

    //
    typedef std::function<void(QString resultStr)> InternalNumItemDialogCallback;
    //
    class NumItemDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit NumItemDialog(QWidget *parent, QString title, bool passMode = false, Uint32 maxDigits = 5);
            //
            virtual ~NumItemDialog();
            //
            QString getKeyStr();
            //
            void open(QObject *receiver, const char *member);

        private slots:
            //
            void onButtonClick(Uint32 count);
            //
            void on_toolButton_C_clicked();

        private:
            //
            Ui::NumItemDialog *ui;
            //
            Int32           m_maxDigits;
            //
            QString         m_keyStr;
            //
            bool            m_passMode;
    };

}

#endif // NUMITEMDIALOG_H
