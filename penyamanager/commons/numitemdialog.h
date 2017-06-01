#ifndef NUMITEMDIALOG_H
#define NUMITEMDIALOG_H

#include <QDialog>

#include <commons/DataTypes.h>

namespace Ui {
    class NumItemDialog;
}

namespace PenyaManager {

    //
    class NumItemDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit NumItemDialog(QWidget *parent, bool passMode = false, Uint32 maxDigits = 5);
            //
            ~NumItemDialog();
            //
            QString getKeyStr();
            //
            Uint32 getKey();

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
