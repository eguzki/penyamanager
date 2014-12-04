//

#include <QMessageBox>

#include "singletons.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//
MainWindow::MainWindow(QWidget *parent) :
    IPartner(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(this->ui->quitButton, SIGNAL(clicked()), this, SLOT(quitButtonOnClick()));
}

//
MainWindow::~MainWindow()
{
    delete ui;
}

//
void MainWindow::setParner(IPartner *partner)
{
    if(partner == 0)
        return;

    connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(this->ui->exitButton, SIGNAL(clicked()), partner, SLOT(init()));
}

void MainWindow::init()
{
    showFullScreen();
    if (!Singletons::m_pDAO->isOpen()) {
        QSqlError err = Singletons::m_pDAO->lastError();
        QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
        qApp->exit(0);
    }

    Singletons::m_pDAO->getProductFamilies();
}

//
void MainWindow::quitButtonOnClick()
{
    // qApp is a macro defined as: (QApplication*)QCoreApplication::instance()
    qApp->exit(0);
    //close();
}
