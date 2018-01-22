//

#include <QLabel>

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include <commons/familyitemwidget.h>
#include <commons/productitemwidget.h>
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

        ProductFamilyListResultPtr pfListPtr = Singletons::m_pDAO->getProductFamilies(false);
        if (pfListPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        this->ui->productListWidget->clear();

        this->ui->editFamilyPushButton->hide();

        fillFamilyProducts(pfListPtr->m_list);
    }
    //
    void FamilyItemManagementWindow::retranslate()
    {
        this->ui->retranslateUi(this);
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
        // setting m_currentFamilyId < 0, AdminFamilyView will initialize empty
        Singletons::m_currentFamilyId = -1;
        // call adminfamilyview window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminFamilyViewKey);
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

        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap familyPixmap = GuiUtils::getImage(imagePath);
        QWidget *pFamilyWidget = new FamilyItemWidget(pList, familyPixmap, Singletons::m_pTranslationManager->getStringTranslation(pfPtr->m_nameEus, pfPtr->m_nameEs));
        // load family image
        pFamilyItem->setSizeHint(pFamilyWidget->minimumSize());
        pFamilyItem->setFlags(Qt::ItemIsSelectable);
        pList->setItemWidget(pFamilyItem, pFamilyWidget);
    }
    //
    void FamilyItemManagementWindow::familyItemClicked(QListWidgetItem* item)
    {
        Int32 familyId = item->data(Constants::kIdRole).toInt();
        this->ui->editFamilyPushButton->show();
        Singletons::m_currentFamilyId = familyId;
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

        ProductItemListResultPtr pfListPtr = Singletons::m_pDAO->getProductsFromFamily(familyId, false);
        if (pfListPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        for (ProductItemList::iterator iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
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
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap productItemPixmap = GuiUtils::getImage(imagePath);
        QWidget *pProduceItemWidget = new ProductItemWidget(pList, productItemPixmap, Singletons::m_pTranslationManager->getStringTranslation(pfPtr->m_nameEus, pfPtr->m_nameEs), pfPtr->m_price);

        // load product image
        pProductItem->setSizeHint(pProduceItemWidget->minimumSize());
        pProductItem->setFlags(Qt::ItemIsSelectable);
        pProductItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        pList->setItemWidget(pProductItem, pProduceItemWidget);
    }
    //
    void FamilyItemManagementWindow::on_editFamilyPushButton_clicked()
    {
        // call family edit window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminFamilyViewKey);
    }
}

