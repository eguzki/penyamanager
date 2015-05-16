#ifndef NUMITEMDIALOG_H
#define NUMITEMDIALOG_H

#include <QDialog>

#include "DataTypes.h"

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
            explicit NumItemDialog(QWidget *parent = 0);
            //
            ~NumItemDialog();

        private:
            //
            Ui::NumItemDialog *ui;

        private slots:
            //
            void onButtonClick(Uint32 count);
            //
            void on_toolButton_C_clicked();
            //
            void on_toolButton_Done_clicked();
    };

}

#endif // NUMITEMDIALOG_H
