//
#include <QtSql>

#include "ddbbhelper.h"
//#include "familyviewdelegate.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(this->ui->quitButton, SIGNAL(clicked()), this, SLOT(quitButtonOnClick()));

    QSqlQueryModel *pModel = new FamilyItemsSqlQueryModel;
    pModel->setQuery("SELECT idproduct_family, name, image FROM product_family WHERE active = 1");

//    FamilyViewDelegate *pFvd = new FamilyViewDelegate;

    ui->familyListView->setModelColumn(1);
    ui->familyListView->setModel(pModel);
 //   ui->familyListView->setItemDelegate(pFvd);
}

//
MainWindow::~MainWindow()
{
    delete ui;
}

//
void MainWindow::setParner(QWidget *partner)
{
    if(partner == 0)
        return;

    connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(this->ui->exitButton, SIGNAL(clicked()), partner, SLOT(showFullScreen()));
}

//
void MainWindow::quitButtonOnClick()
{
    // qApp is a macro defined as: (QApplication*)QCoreApplication::instance()
    qApp->exit(0);
    //close();
}
