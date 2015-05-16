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

        private:
            //
            Ui::LoginWindow *ui;

        private slots:
            //
            void init();
            //
            void on_loginButton_clicked();
    };

}

#endif // LOGINWINDOW_H
