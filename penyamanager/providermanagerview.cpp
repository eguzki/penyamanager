//

#include <QLabel>

#include "utils.h"
#include "singletons.h"
#include "providermanagerview.h"
#include "ui_providermanagerview.h"

namespace PenyaManager {
    //
    ProviderManagerView::ProviderManagerView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::ProviderManagerView)
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
        //
        // Loading providers
        //
        fillProviders();

        //
        // Show
        //

        show();
    }
    //
    void ProviderManagerView::fillProviders()
    {
        this->ui->providersListWidget->clear();

        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();

        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
        {
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
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pProviderPtr->m_image);
        QPixmap providerPixmap = Utils::getImage(imagePath);
        pImageLabel->setPixmap(providerPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        QLabel *pTextLabel = new QLabel(pProviderPtr->m_name);
        pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
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
}
