//

#include <QDebug>
#include <QSpinBox>
#include <QSpacerItem>
#include <QMessageBox>

#include "utils.h"
#include "singletons.h"
#include "providerinvoiceview.h"
#include "ui_providerinvoiceview.h"

namespace PenyaManager {
    //
    ProviderInvoiceView::ProviderInvoiceView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::ProviderInvoiceView),
        m_currentProviderIndex(-1),
        m_rowProviderIdMap()
    {
        ui->setupUi(this);
    }
    //
    ProviderInvoiceView::~ProviderInvoiceView()
    {
        delete ui;
    }
    //
    void ProviderInvoiceView::on_savePushButton_clicked()
    {
        // TODO validate invoice id
        // TODO validate total
        for (auto idx = 0; idx < this->ui->productsListWidget->count(); ++idx)
        {
            QListWidgetItem *pProductItem = this->ui->productsListWidget->item(idx);
            QWidget *pProductItemWidget = this->ui->productsListWidget->itemWidget(pProductItem);
            QLayout *pLayout = pProductItemWidget->layout();
            // layout contains 4 elements, itemAt fourth
            QWidget *pCountWidget = pLayout->itemAt(3)->widget();
            QSpinBox *pCountSpinBox = qobject_cast<QSpinBox *>(pCountWidget);
            if (pCountSpinBox == 0) {
                QMessageBox::critical(this, "Unexpected error",
                        "ProviderInvoiceView failed taking SpinBox");
                return;
            }

            Int32 productId = pProductItem->data(Constants::kIdRole).toInt();
            qDebug() << productId << ": " << pCountSpinBox->value();
        }

    }
    //
    void ProviderInvoiceView::initialize()
    {
        m_currentProviderIndex = -1;
        this->ui->invoiceLineEdit->clear();
        this->ui->totalLineEdit->clear();
        this->ui->providerComboBox->clear();
        this->ui->productsListWidget->clear();

        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();

        // internal data structure reset
        this->m_rowProviderIdMap.clear();
        Int32 idx = 0;
        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Constants::kImageRootPath).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = Utils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(idx, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            this->m_rowProviderIdMap[idx] = pProviderPtr->m_id;
            idx++;
        }
        // do not show any provider by default (-1)
        this->ui->providerComboBox->setCurrentIndex(m_currentProviderIndex);
    }
    //
    void ProviderInvoiceView::init()
    {
        initialize();
        //
        // Show
        //

        show();
    }
    //
    void ProviderInvoiceView::on_providerComboBox_activated(int index)
    {
        if (index < 0 || index == m_currentProviderIndex){
            return;
        }
        m_currentProviderIndex = index;

        auto rowMap = m_rowProviderIdMap.find(m_currentProviderIndex);
        if (rowMap == m_rowProviderIdMap.end()) {
            //this should never happen
            qDebug() << "[ERROR] providerId not found and should be in the map";
            return;
        }

        // get provider ID
        Int32 providerId = rowMap->second;

        this->ui->productsListWidget->clear();

        ProductItemListPtr pfListPtr = Singletons::m_pDAO->getProductsFromProvider(providerId);

        for (ProductItemList::iterator iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
        {
            createProductItemRow(*iter);
        }
    }
    //
    void ProviderInvoiceView::createProductItemRow(const ProductItemPtr &pIPtr)
    {
        QListWidgetItem *pProductItem = new QListWidgetItem(this->ui->productsListWidget);
        pProductItem->setData(Constants::kIdRole, pIPtr->m_id);
        this->ui->productsListWidget->addItem(pProductItem);

        // main product widget
        QWidget *pProduceItemWidget = new QWidget(this);
        // load product image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pIPtr->m_imagePath);
        QPixmap productItemPixmap = Utils::getImage(imagePath);
        pImageLabel->setPixmap(productItemPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        // name
        QLabel *pTextLabel = new QLabel(pIPtr->m_name);
        pTextLabel->setFixedWidth(250);

        // count widget
        QSpinBox *pCountWidget = new QSpinBox;
        pCountWidget->setFixedWidth(150);
        // Default max is only 99
        pCountWidget->setMaximum(99999);
        // layout
        QHBoxLayout *pLayout = new QHBoxLayout(pProduceItemWidget);
        // layout must have 4 elements.
        // Later, 4th element will be fetched
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pTextLabel);
        QSpacerItem *pHorizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        pLayout->addItem(pHorizontalSpacer);
        pLayout->addWidget(pCountWidget);
        pProduceItemWidget->setLayout(pLayout);
        pProductItem->setSizeHint(pLayout->minimumSize());
        pProductItem->setBackgroundColor(this->ui->productsListWidget->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        this->ui->productsListWidget->setItemWidget(pProductItem, pProduceItemWidget);
    }
}

