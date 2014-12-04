#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "IPartner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public IPartner
{
    Q_OBJECT

    public:
        //
        explicit MainWindow(QWidget *parent = 0);
        //
        ~MainWindow();
        //
        void setParner(IPartner *partner);

    private:
        Ui::MainWindow *ui;

    private slots:
        //
        void quitButtonOnClick();
        //
        void init();
};

#endif // MAINWINDOW_H
