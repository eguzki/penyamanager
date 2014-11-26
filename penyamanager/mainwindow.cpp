#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(this->ui->quitButton, SIGNAL(clicked()), this, SLOT(quitButtonOnClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setParner(QWidget *partner) {
    if(partner == 0)
        return;

    connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(this->ui->exitButton, SIGNAL(clicked()), partner, SLOT(showFullScreen()));

}

void MainWindow::quitButtonOnClick(){
    exit(0);
}
