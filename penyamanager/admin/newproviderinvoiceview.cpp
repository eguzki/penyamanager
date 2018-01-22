//
#include <QDebug>
#include <QSpinBox>
#include <QSpacerItem>

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "newproviderinvoiceview.h"
#include "ui_newproviderinvoiceview.h"

namespace PenyaManager {
    //
    NewProviderInvoiceView::NewProviderInvoiceView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::NewProviderInvoiceView),
        m_switchCentralWidgetCallback(callback),
        m_currentProviderIndex(-1),
        m_rowProviderIdMap()
    {
        ui->setupUi(this);
    }
    //
    NewProviderInvoiceView::~NewProviderInvoiceView()
    {
        delete ui;
    }
    //
    void NewProviderInvoiceView::on_savePushButton_clicked()
    {
        // validate invoice id
        QString invoiceId = this->ui->invoiceLineEdit->text();
        if (invoiceId.isEmpty()){
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Invoice ID cannot be empty"), [](){});
            return;
        }
        // validate providerID
        if (m_currentProviderIndex == -1)
        {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Select Provider"), [](){});
            return;
        }
        // validate total
        Float total = this->ui->totalDoubleSpinBox->value();
        if ( total == 0.0 )
        {
            Singletons::m_pDialogManager->questionMessageBoxTitled(this, tr("0€ invoice. Are you sure to continue?"),
                    std::bind(&NewProviderInvoiceView::onZeroInvoiceAccepted, this, _1)
                    );
            return;
        }
        createProviderInvoice();
    }
    //
    void NewProviderInvoiceView::onZeroInvoiceAccepted(QMessageBox::StandardButton answerButton)
    {
        if (answerButton != QMessageBox::Yes)
        {
            return;
        }
        createProviderInvoice();
    }
    //
    void NewProviderInvoiceView::createProviderInvoice()
    {
        QString invoiceId = this->ui->invoiceLineEdit->text();
        Float total = this->ui->totalDoubleSpinBox->value();
        // create invoice
        ProviderInvoicePtr pProviderInvoicePtr(new ProviderInvoice);
        pProviderInvoicePtr->m_id = invoiceId;
        pProviderInvoicePtr->m_regDate = QDate::currentDate();
        pProviderInvoicePtr->m_total = total;
        pProviderInvoicePtr->m_providerid = this->ui->providerComboBox->currentData().toInt();
        bool ok = Singletons::m_pDAO->createProviderInvoice(pProviderInvoicePtr);
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

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
                Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                        QString("NewProviderInvoiceView failed taking SpinBox"));
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }

            Int32 productId = pProductItem->data(Constants::kIdRole).toInt();
            // only those with non zero count
            if (pCountSpinBox->value() > 0) {
                // create provider invoice product item
                bool ok = Singletons::m_pDAO->createProviderInvoiceProduct(pProviderInvoicePtr->m_id, productId, pCountSpinBox->value());
                if (!ok) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                // update stock
                ok = Singletons::m_pDAO->updateStock(productId, pCountSpinBox->value());
                if (!ok) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
            }
        }
        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                QString("new invoice id: %1, provider id %2").arg(pProviderInvoicePtr->m_id).arg(pProviderInvoicePtr->m_providerid));
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Saved Successfully"),
                std::bind(&NewProviderInvoiceView::onProviderInvoiceDone, this)
                );
        // nothing should be added here
    }
    //
    void NewProviderInvoiceView::onProviderInvoiceDone()
    {
        // call provider invoice list
        m_switchCentralWidgetCallback(WindowKey::kProviderInvoiceListViewKey);
    }
    //
    void NewProviderInvoiceView::initialize()
    {
        m_currentProviderIndex = -1;
        this->ui->invoiceLineEdit->clear();
        this->ui->totalDoubleSpinBox->setValue(0.0);
        this->ui->providerComboBox->clear();
        this->ui->productsListWidget->clear();

        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // internal data structure reset
        this->m_rowProviderIdMap.clear();
        Int32 idx = 0;
        for (auto iter = pProviderListResultPtr->m_list->begin(); iter != pProviderListResultPtr->m_list->end(); ++iter) {
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
    void NewProviderInvoiceView::init()
    {
        initialize();
    }
    //
    void NewProviderInvoiceView::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void NewProviderInvoiceView::on_providerComboBox_activated(int index)
    {
        if (index < 0 || index == m_currentProviderIndex){
            return;
        }
        m_currentProviderIndex = index;

        auto rowMap = m_rowProviderIdMap.find(m_currentProviderIndex);
        if (rowMap == m_rowProviderIdMap.end()) {
            //this should never happen
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                    QString("providerId not found and should be in the map"));
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Unexpected error"), [](){});
            return;
        }

        // get provider ID
        Int32 providerId = rowMap->second;

        this->ui->productsListWidget->clear();

        ProductItemListResultPtr pfListPtr = Singletons::m_pDAO->getProductsFromProvider(providerId);
        if (pfListPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        for (ProductItemList::iterator iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            createProductItemRow(*iter);
        }
    }
    //
    void NewProviderInvoiceView::createProductItemRow(const ProductItemPtr &pIPtr)
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
        QLabel *pTextLabel = new QLabel(Singletons::m_pTranslationManager->getStringTranslation(pIPtr->m_nameEus, pIPtr->m_nameEs));
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

