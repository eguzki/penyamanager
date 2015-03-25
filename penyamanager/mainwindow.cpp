#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "families.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(pushbutton1_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushbutton1_click(){
    this->ui->lineEdit->setText("Internet is for porn");
}

void MainWindow::on_login_main_clicked()
{
    families fam;
    fam.isModal();
    fam.show();

    /* aquí mostramos la pantalla sin bloquear la que queda detrás (login). El primer método, bloquea la ventana del login */
//    fam =new families(this);
//    fam->show();
}
