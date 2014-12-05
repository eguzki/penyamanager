//

#include <QLabel>
#include <QListWidgetItem>
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
    if (!Singletons::m_pDAO->isOpen()) {
        QSqlError err = Singletons::m_pDAO->lastError();
        QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
        qApp->exit(0);
    }

    ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies();

    fillFamilyProducts(pfListPtr);

    showFullScreen();
}
//
void MainWindow::createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList)
{
    QListWidgetItem *pFamilyItem = new QListWidgetItem(pList);
    pList->addItem(pFamilyItem);

    QWidget *pFamilyWidget = new QWidget;
    QLabel *pImageLabel = new QLabel(pfPtr->m_imagePath);
    QLabel *pTextLabel = new QLabel(pfPtr->m_name);

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addWidget(pImageLabel);
    pLayout->addWidget(pTextLabel);
    pFamilyWidget->setLayout(pLayout);
    pFamilyItem->setSizeHint(pLayout->minimumSize());
    pList->setItemWidget(pFamilyItem, pFamilyWidget);
}
//
void MainWindow::fillFamilyProducts(const ProductFamilyListPtr &pflPtr)
{
    this->ui->familyListWidget->clear();

    for (ProductFamilyList::iterator iter = pflPtr->begin(); iter != pflPtr->end(); ++iter)
    {
        createFamilyWidget(*iter, this->ui->familyListWidget);
    }
}

//
void MainWindow::quitButtonOnClick()
{
    // qApp is a macro defined as: (QApplication*)QCoreApplication::instance()
    qApp->exit(0);
    //close();
}
