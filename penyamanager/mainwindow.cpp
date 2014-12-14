//

#include <QLabel>
#include <QListWidgetItem>
#include <QMessageBox>

#include "constants.h"
#include "utils.h"
#include "singletons.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace PenyaManager {

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
    connect(this->ui->familyListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(familyItemClicked(QListWidgetItem*)));
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
    // load family image
    QLabel *pImageLabel = new QLabel;
    QString imagePath = QDir(Constants::kImageRootPath).filePath(pfPtr->m_imagePath);
    QPixmap familyPixmap = Utils::getImage(imagePath);
    pImageLabel->setPixmap(familyPixmap);
    pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
    pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
    pImageLabel->setScaledContents(true);

    QLabel *pTextLabel = new QLabel(pfPtr->m_name);
    pTextLabel->setFixedWidth(Constants::kFamilyImageWidth);
    pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addWidget(pImageLabel);
    pLayout->addWidget(pTextLabel);
    pFamilyWidget->setLayout(pLayout);
    pFamilyItem->setSizeHint(pLayout->minimumSize());
    pFamilyItem->setFlags(Qt::ItemIsSelectable);
    pFamilyItem->setBackgroundColor(Qt::blue);
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

//
void MainWindow::familyItemClicked(QListWidgetItem* item)
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime xmas(QDate(now.date().year(), 12, 25), QTime(0, 0));
    QString str;
    str.sprintf("slsls %lli", now.secsTo(xmas) % 10);
    this->ui->label->setText(str);
}

}
