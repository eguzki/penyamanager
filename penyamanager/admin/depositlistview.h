#ifndef DEPOSITLISTVIEW_H
#define DEPOSITLISTVIEW_H

#include <QWidget>

#include <commons/IPartner.h>

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
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void showUncheckedDeposits();
            //
            void initializeTable();

        private slots:
            //
            void onDeposit_check_clicked(Uint32 rowCount);

        private:
            //
            Ui::DepositListView *ui;
    };
}

#endif // DEPOSITLISTVIEW_H
