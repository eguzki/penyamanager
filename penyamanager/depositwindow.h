#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QWidget>

#include "objs/Member.h"
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

        private:
            //
            void fillMemberProfile(const MemberPtr &pMemberPtr);
            //
            void updateNewBalanceLabel(double deposit);

        private slots:
            //
            void on_backButton_clicked();
            //
            void on_confirmButton_clicked();
            //
            void on_pushButton_number_clicked(Uint32 num);
            //
            void on_pushButton_coma_clicked();
            //
            void on_pushButton_C_clicked();

        private:
            //
            Ui::DepositWindow *ui;
    };
}

#endif // DEPOSITWINDOW_H
