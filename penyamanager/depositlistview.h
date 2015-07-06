#ifndef DEPOSITLISTVIEW_H
#define DEPOSITLISTVIEW_H

#include <QWidget>

#include "IPartner.h"

namespace Ui {
    //
    class DepositListView;
}

namespace PenyaManager {
    //
    class DepositListView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit DepositListView(QWidget *parent = 0);
            //
            ~DepositListView();
            //
            void init();

        private:
            //
            void showUncheckedDeposits();
            //
            void initializeTable();

        private slots:
            //
            void on_deposit_check_clicked(Uint32 rowCount);

        private:
            //
            Ui::DepositListView *ui;
    };
}

#endif // DEPOSITLISTVIEW_H
