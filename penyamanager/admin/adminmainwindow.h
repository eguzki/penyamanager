#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>

#include <commons/constants.h>

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
            explicit AdminMainWindow(QWidget *parent, QTimer *pInactivityTimer);
            //
            ~AdminMainWindow();
            //
            void switchCentralWidget(WindowKey key);
            //
            void init();
            //
            void retranslate();
            //
            virtual void changeEvent(QEvent* event);

        private slots:
            //
            void on_actionExit_triggered();
            //
            void on_actionSlow_payers_triggered();
            //
            void on_actionInvoice_list_triggered();
            //
            void on_actionManage_providers_triggered();
            //
            void on_actionManage_Stock_triggered();
            //
            void on_actionManage_family_items_triggered();
            //
            void on_actionProduct_consumption_triggered();
            //
            void on_actionProvider_invoice_triggered();
            //
            void on_actionProvider_invoice_list_triggered();
            //
            void on_actionDeposit_Check_triggered();
            //
            void on_actionAccount_Balance_triggered();
            //
            void on_actionMember_management_triggered();
            //
            void on_actionManager_reservations_triggered();

        private:
            //
            Ui::AdminMainWindow     *ui;
            //
            QWidget                 *m_pEmptyWidget;
            //
            QTimer                  *m_pInactivityTimer;
    };
}
#endif // ADMINMAINWINDOW_H
