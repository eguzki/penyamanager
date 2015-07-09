#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>

#include "constants.h"

namespace Ui {
class AdminMainWindow;
}

namespace PenyaManager {
    //
    class AdminMainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            //
            explicit AdminMainWindow(QWidget *parent = 0);
            //
            ~AdminMainWindow();
            //
            void init();
            //
            void switchCentralWidget(WindowKey key);

        private slots:
            //
            void on_exit_button_triggered();
            //
            void on_slow_payers_button_triggered();
            //
            void on_invoice_list_button_triggered();
            //
            void on_manage_providers_button_triggered();
            //
            void on_manage_stock_button_triggered();
            //
            void on_manage_family_items_button_triggered();
            //
            void on_product_expenses_button_triggered();
            //
            void on_provider_invoice_button_triggered();
            //
            void on_provider_invoice_list_button_triggered();
            //
            void on_deposit_list_button_triggered();
            //
            void on_account_balance_list_button_triggered();

        private:
            //
            Ui::AdminMainWindow *ui;
    };
}
#endif // ADMINMAINWINDOW_H
