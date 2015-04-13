#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QWidget>

#include "IPartner.h"

namespace Ui {
class DepositWindow;
}

namespace PenyaManager {
    //
    class DepositWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit DepositWindow(QWidget *parent = 0);
            //
            ~DepositWindow();
            //
            void init();

        private slots:
            //
            void on_backButton_clicked();
            //
            void on_confirmButton_clicked();

        private:
            //
            Ui::DepositWindow *ui;
    };
}

#endif // DEPOSITWINDOW_H
