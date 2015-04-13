//

#include "depositwindow.h"
#include "ui_depositwindow.h"

namespace PenyaManager {
    //
    DepositWindow::DepositWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::DepositWindow)
    {
        ui->setupUi(this);
    }
    //
    DepositWindow::~DepositWindow()
    {
        delete ui;
    }
    //
    void DepositWindow::init()
    {
        //
        // Show
        //

        show();
    }
    //
    void DepositWindow::on_backButton_clicked()
    {

    }
    //
    void DepositWindow::on_confirmButton_clicked()
    {

    }
}
