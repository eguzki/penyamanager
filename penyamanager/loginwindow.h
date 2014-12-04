#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "IPartner.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public IPartner
{
    Q_OBJECT

    public:
        //
        explicit LoginWindow(QWidget *parent = 0);
        //
        ~LoginWindow();
        //
        void setParner(IPartner *partner);
        //
        void start();

    private:
        Ui::LoginWindow *ui;

    private slots:
        //
        void init();

};

#endif // LOGINWINDOW_H
