#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    this->connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(pushbutton1_click()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::pushbutton1_click(){
    this->ui->lineEdit->setText("Internet is for porn");
}
