#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(pushbutton1_click()));
    this->connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(pushbutton2_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushbutton1_click(){
    this->ui->lineEdit->setText("Internet is for porn");
}

void MainWindow::pushbutton2_click(){
    this->ui->lineEdit->setText("");
}
