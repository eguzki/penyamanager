#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "IPartner.h"

namespace Ui {
    //
    class LoginWindow;
}

namespace PenyaManager {

    //
    class LoginWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit LoginWindow(QWidget *parent = 0);
            //
            ~LoginWindow();

        private slots:
            //
            void init();
            //
            void on_loginPushButton_clicked();
            //
            void on_passwordPushButton_clicked();
            //
            void on_memberIdPushButton_clicked();

        private:
            //
            Ui::LoginWindow *ui;
            //
            QString         m_password;
            //
            Int32           m_memberId;

    };

}

#endif // LOGINWINDOW_H
