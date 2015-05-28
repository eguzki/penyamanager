#ifndef ADMINLOGINWINDOW_H
#define ADMINLOGINWINDOW_H

#include "IPartner.h"
#include "adminmainwindow.h"

namespace Ui {
    //
    class AdminLoginWindow;
}

namespace PenyaManager {

    //
    class AdminLoginWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminLoginWindow(AdminMainWindow *pAdminMainWindow);
            //
            ~AdminLoginWindow();

        private:
            //
            AdminMainWindow *m_pAdminMainWindow;
            //
            Ui::AdminLoginWindow *ui;

        private slots:
            //
            void init();
            //
            void on_loginButton_clicked();
    };

}
#endif // ADMINLOGINWINDOW_H
