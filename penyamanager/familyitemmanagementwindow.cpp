//

#include <QLabel>

#include "utils.h"
#include "singletons.h"
#include "familyitemmanagementwindow.h"
#include "ui_familyitemmanagementwindow.h"

namespace PenyaManager {
    //
    FamilyItemManagementWindow::FamilyItemManagementWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::FamilyItemManagementWindow),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->connect(this->ui->familyListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(familyItemClicked(QListWidgetItem*)));
        this->connect(this->ui->productListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(productItemClicked(QListWidgetItem*)));
    }
    //
    FamilyItemManagementWindow::~FamilyItemManagementWindow()
    {
        delete ui;
    }
    //
    void FamilyItemManagementWindow::init()
    {
        //
        // Loading families
        //

        ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies(false);

        this->ui->productListWidget->clear();

        fillFamilyProducts(pfListPtr);

        //
        // Show
        //

        show();
    }
    //
    void FamilyItemManagementWindow::on_newItemPushButton_clicked()
    {
        // setting m_currentProductId < 0, AdminProductItemWindow will initialize empty
        Singletons::m_currentProductId = -1;
        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminProductItemKey);
    }
    //
    void FamilyItemManagementWindow::on_newFamilyPushButton_clicked()
    {

    }
    //
    void FamilyItemManagementWindow::fillFamilyProducts(const ProductFamilyListPtr &pflPtr)
    {
        this->ui->familyListWidget->clear();

        for (ProductFamilyList::iterator iter = pflPtr->begin(); iter != pflPtr->end(); ++iter)
        {
            createFamilyWidget(*iter, this->ui->familyListWidget);
        }
    }
    //
    void FamilyItemManagementWindow::createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList)
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
    void FamilyItemManagementWindow::familyItemClicked(QListWidgetItem* item)
    {
        Int32 familyId = item->data(Constants::kIdRole).toInt();
        fillProductItems(familyId);
    }
    //
    void FamilyItemManagementWindow::productItemClicked(QListWidgetItem* item)
    {
        Int32 productId = item->data(Constants::kIdRole).toInt();
        Singletons::m_currentProductId = productId;
        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminProductItemKey);
    }
    //
    void FamilyItemManagementWindow::fillProductItems(Int32 familyId)
    {
        this->ui->productListWidget->clear();

        ProductItemListPtr pfListPtr = Singletons::m_pDAO->getProductsFromFamily(familyId, false);

        for (ProductItemList::iterator iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
        {
            createProductItemWidget(*iter, this->ui->productListWidget);
        }
    }
    //
    void FamilyItemManagementWindow::createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pProductItem = new QListWidgetItem(pList);
        pProductItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pProductItem);

        // main product widget
        QWidget *pProduceItemWidget = new QWidget;

        // load product image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pfPtr->m_imagePath);
        QPixmap productItemPixmap = Utils::getImage(imagePath);
        pImageLabel->setPixmap(productItemPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        // product info: name and price
        QWidget *pProductItemInfoWidget = new QWidget;
        QVBoxLayout *pInfoLayout = new QVBoxLayout;
        QLabel *pTextLabel = new QLabel(pfPtr->m_name);
        pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        //pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        QLabel *pProductPriceLabel = new QLabel(QString("%1 €").arg(pfPtr->m_price));
        pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        //pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pInfoLayout->addWidget(pTextLabel);
        pInfoLayout->addWidget(pProductPriceLabel);
        pProductItemInfoWidget->setLayout(pInfoLayout);

        QHBoxLayout *pLayout = new QHBoxLayout;
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pProductItemInfoWidget);
        pProduceItemWidget->setLayout(pLayout);
        pProductItem->setSizeHint(pLayout->minimumSize());
        pProductItem->setFlags(Qt::ItemIsSelectable);
        pProductItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        pList->setItemWidget(pProductItem, pProduceItemWidget);
    }
}

