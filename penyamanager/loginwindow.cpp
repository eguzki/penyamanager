#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::setParner(QWidget *partner) {
    if(partner == 0)
        return;

    connect(this->ui->loginButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(this->ui->loginButton, SIGNAL(clicked()), partner, SLOT(showMaximized()));

}
