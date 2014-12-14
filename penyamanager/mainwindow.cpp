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

    //loadUserProfile();

    ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies();

    this->ui->productListWidget->clear();

    fillFamilyProducts(pfListPtr);

    showFullScreen();
}

//
void MainWindow::createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList)
{
    QListWidgetItem *pProductItem = new QListWidgetItem(pList);
    pProductItem->setData(Constants::kIdRole, pfPtr->m_id);
    pList->addItem(pProductItem);

    QWidget *pProduceItemWidget = new QWidget;
    // load family image
    QLabel *pImageLabel = new QLabel;
    QString imagePath = QDir(Constants::kImageRootPath).filePath(pfPtr->m_imagePath);
    QPixmap productItemPixmap = Utils::getImage(imagePath);
    pImageLabel->setPixmap(productItemPixmap);
    pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
    pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
    pImageLabel->setScaledContents(true);

    QLabel *pTextLabel = new QLabel(pfPtr->m_name);
    pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
    pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addWidget(pImageLabel);
    pLayout->addWidget(pTextLabel);
    pProduceItemWidget->setLayout(pLayout);
    pProductItem->setSizeHint(pLayout->minimumSize());
    pProductItem->setFlags(Qt::ItemIsSelectable);
    pProductItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
    pList->setItemWidget(pProductItem, pProduceItemWidget);
}

//
void MainWindow::createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList)
{
    QListWidgetItem *pFamilyItem = new QListWidgetItem(pList);
    pFamilyItem->setData(Constants::kIdRole, pfPtr->m_id);
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
    pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
    pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addWidget(pImageLabel);
    pLayout->addWidget(pTextLabel);
    pFamilyWidget->setLayout(pLayout);
    pFamilyItem->setSizeHint(pLayout->minimumSize());
    pFamilyItem->setFlags(Qt::ItemIsSelectable);
    pFamilyItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
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
void MainWindow::fillProductItems(Int32 familyId)
{
    this->ui->productListWidget->clear();

    ProductItemListPtr pfListPtr = Singletons::m_pDAO->getProductsFromFamily(familyId);

    for (ProductItemList::iterator iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
    {
        createProductItemWidget(*iter, this->ui->productListWidget);
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
    Int32 familyId = item->data(Constants::kIdRole).toInt();
    fillProductItems(familyId);
}

}
