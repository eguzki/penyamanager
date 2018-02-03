//

#include <QLabel>

#include <commons/guiutils.h>
#include <commons/utils.h>
#include <commons/singletons.h>
#include "providermanagerview.h"
#include "ui_providermanagerview.h"

namespace PenyaManager {
    //
    ProviderManagerView::ProviderManagerView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::ProviderManagerView),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
    }
    //
    ProviderManagerView::~ProviderManagerView()
    {
        delete ui;
    }
    //
    void ProviderManagerView::init()
    {
        Singletons::m_currentProviderId = -1;
        this->ui->editProviderPushButton->setEnabled(false);
        clearAll();
        //
        // Loading providers
        //
        fillProviders();
    }
    //
    void ProviderManagerView::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void ProviderManagerView::clearAll()
    {
        this->ui->providersListWidget->clear();
        this->ui->productsListWidget->clear();
    }
    //
    void ProviderManagerView::fillProviders()
    {
        this->ui->providersListWidget->clear();

        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        for (auto iter = pProviderListResultPtr->m_list->begin(); iter != pProviderListResultPtr->m_list->end(); ++iter) {
            createProviderWidget(*iter);
        }
    }
    //
    void ProviderManagerView::createProviderWidget(ProviderPtr pProviderPtr)
    {
        QListWidgetItem *pProviderItem = new QListWidgetItem(this->ui->providersListWidget);
        pProviderItem->setData(Constants::kIdRole, pProviderPtr->m_id);
        this->ui->providersListWidget->addItem(pProviderItem);

        QWidget *pProviderWidget = new QWidget;
        // load providers image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProviderPtr->m_image);
        QPixmap providerPixmap = GuiUtils::getImage(imagePath);
        pImageLabel->setPixmap(providerPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        QLabel *pTextLabel = new QLabel(pProviderPtr->m_name);
        pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);

        QHBoxLayout *pLayout = new QHBoxLayout;
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pTextLabel);
        pProviderWidget->setLayout(pLayout);
        pProviderItem->setSizeHint(pLayout->minimumSize());
        pProviderItem->setFlags(Qt::ItemIsSelectable);
        pProviderItem->setBackgroundColor(this->ui->providersListWidget->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        this->ui->providersListWidget->setItemWidget(pProviderItem, pProviderWidget);
    }
    //
    void ProviderManagerView::fillProductItems(Int32 providerId)
    {
        this->ui->productsListWidget->clear();

        ProductItemListResultPtr pfListPtr = Singletons::m_pDAO->getProductsFromProvider(providerId);
        if (pfListPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        for (ProductItemList::iterator iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            createProductItemWidget(*iter, this->ui->productsListWidget);
        }
    }
    //
    void ProviderManagerView::createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pProductItem = new QListWidgetItem(pList);
        pProductItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pProductItem);

        // main product widget
        QWidget *pProduceItemWidget = new QWidget;

        // load product image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap productItemPixmap = GuiUtils::getImage(imagePath);
        pImageLabel->setPixmap(productItemPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        // product info: name and price
        QWidget *pProductItemInfoWidget = new QWidget;
        QVBoxLayout *pInfoLayout = new QVBoxLayout;
        QLabel *pTextLabel = new QLabel(Singletons::m_pTranslationManager->getStringTranslation(pfPtr->m_nameEus, pfPtr->m_nameEs));
        QLabel *pProductPriceLabel = new QLabel(QString("%1 €").arg(pfPtr->m_price, 0, 'f', 2));
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
    //
    void ProviderManagerView::on_newProviderPushButton_clicked()
    {
        Singletons::m_currentProviderId = -1;
        // call new provider window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminNewProviderKey);
    }
    //
    void ProviderManagerView::on_providersListWidget_itemClicked(QListWidgetItem *item)
    {
        Int32 providerId = item->data(Constants::kIdRole).toInt();
        Singletons::m_currentProviderId = providerId;
        if (!this->ui->editProviderPushButton->isEnabled()) {
            this->ui->editProviderPushButton->setEnabled(true);
        }
        fillProductItems(providerId);
    }
    //
    void ProviderManagerView::on_editProviderPushButton_clicked()
    {
        // call new provider window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminNewProviderKey);
    }
}





