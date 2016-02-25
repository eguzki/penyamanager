//

#include <QDebug>
#include <QSpinBox>
#include <QSpacerItem>
#include <QMessageBox>

#include <QsLog.h>

#include <commons/guiutils.h>
#include <commons/singletons.h>
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
        // validate invoice id
        QString invoiceId = this->ui->invoiceLineEdit->text();
        if (invoiceId.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Invoice ID cannot be empty");
            return;
        }
        // validate total
        Float total = this->ui->totalDoubleSpinBox->value();
        if ( total == 0.0 )
        {
            QMessageBox msgBox;
            msgBox.setText("Invoice has 0.0 as total value");
            msgBox.setInformativeText("Are you sure to continue?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Cancel)
            {
                return;
            }
        }
        // validate providerID
        if (m_currentProviderIndex == -1)
        {
            QMessageBox::warning(this, "Data missing", "Select Provider");
            return;
        }

        // create invoice
        ProviderInvoicePtr pProviderInvoicePtr(new ProviderInvoice);
        pProviderInvoicePtr->m_id = invoiceId;
        pProviderInvoicePtr->m_regDate = QDate::currentDate();
        pProviderInvoicePtr->m_total = total;
        pProviderInvoicePtr->m_providerid = this->ui->providerComboBox->currentData().toInt();
        Singletons::m_pDAO->createProviderInvoice(pProviderInvoicePtr);

        // create invoice products
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
            // only those with non zero count
            if (pCountSpinBox->value() > 0) {
                // create provider invoice product item
                Singletons::m_pDAO->createProviderInvoiceProduct(pProviderInvoicePtr->m_id, productId, pCountSpinBox->value());
                // update stock
                Singletons::m_pDAO->updateStock(productId, pCountSpinBox->value());
            }
        }
        QLOG_INFO() << QString("[ProviderInvoice] ID %1 providerID %2").arg(pProviderInvoicePtr->m_id).arg(pProviderInvoicePtr->m_providerid);
        QMessageBox::information(this, "New provider invoice", "Saved Successfully");
        initialize();
    }
    //
    void ProviderInvoiceView::initialize()
    {
        m_currentProviderIndex = -1;
        this->ui->invoiceLineEdit->clear();
        this->ui->totalDoubleSpinBox->setValue(0.0);
        this->ui->providerComboBox->clear();
        this->ui->productsListWidget->clear();

        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();

        // internal data structure reset
        this->m_rowProviderIdMap.clear();
        Int32 idx = 0;
        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
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
    }
    //
    void ProviderInvoiceView::retranslate()
    {
        this->ui->retranslateUi(this);
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
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pIPtr->m_imagePath);
        QPixmap productItemPixmap = GuiUtils::getImage(imagePath);
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

