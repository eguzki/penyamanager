//

#include <QFileDialog>
#include <QDateTime>

#include <commons/guiutils.h>
#include <commons/utils.h>
#include <commons/singletons.h>
#include "adminproductitem.h"
#include "ui_adminproductitem.h"

namespace PenyaManager {
    //
    AdminProductItem::AdminProductItem(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AdminProductItem),
        m_switchCentralWidgetCallback(callback),
        m_productImageFilename()
    {
        ui->setupUi(this);
    }
    //
    AdminProductItem::~AdminProductItem()
    {
        delete ui;
    }
    //
    void AdminProductItem::init()
    {
        this->m_productImageFilename.clear();
        //
        // Product info
        //

        if (Singletons::m_currentProductId >= 0) {
            fillProductInfo(Singletons::m_currentProductId);
        } else {
            initialize();
        }
    }
    //
    void AdminProductItem::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void AdminProductItem::on_savePushButton_clicked()
    {
        // validate name is not empty
        QString productNameEus = this->ui->nameEusLineEdit->text();
        if (productNameEus.isEmpty()){
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Basque name cannot be empty"), [](){});
            return;
        }
        // validate nameEs is not empty
        QString productNameEs = this->ui->nameEsLineEdit->text();
        if (productNameEs.isEmpty()){
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Spanish name cannot be empty"), [](){});
            return;
        }

        // validate price field
        Float price = this->ui->priceDoubleSpinBox->value();
        if (!price) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("price cannot be 0.00€"), [](){});
            return;
        }
        // validate providers
        if (!this->ui->providerComboBox->count())
        {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Providers list is empty. Add some providers first"), [](){});
            return;
        }
        // validate families
        if (!this->ui->familyComboBox->count())
        {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Family list is empty. Add some families first"), [](){});
            return;
        }

        // save in ddbb
        if (Singletons::m_currentProductId >= 0) {
            // edit previous item
            ProductItemResultPtr pProductResultPtr = Singletons::m_pDAO->getProductItem(Singletons::m_currentProductId);
            if (pProductResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            if (!pProductResultPtr->m_item) {
                Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProduct,
                        QString("item not found %1").arg(Singletons::m_currentProductId));
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pProductResultPtr->m_item->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pProductResultPtr->m_item->m_nameEus = this->ui->nameEusLineEdit->text();
            pProductResultPtr->m_item->m_nameEs = this->ui->nameEsLineEdit->text();
            // imagePath
            if (!this->m_productImageFilename.isEmpty()) {
                // new image was selected
                pProductResultPtr->m_item->m_imagePath = Utils::newImageName("product", this->m_productImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductResultPtr->m_item->m_imagePath);
                QFile::copy(this->m_productImageFilename, destFilePath);
            }
            // active
            pProductResultPtr->m_item->m_active = this->ui->activeCheckBox->isChecked();
            // regDate -> no change
            // family
            pProductResultPtr->m_item->m_familyId = this->ui->familyComboBox->currentData().toInt();
            // price (already validated)
            pProductResultPtr->m_item->m_price = price;
            // providerId
            pProductResultPtr->m_item->m_providerId = this->ui->providerComboBox->currentData().toInt();
            // stock -> no change

            // update in ddbb
            bool ok = Singletons::m_pDAO->updateProductItem(pProductResultPtr->m_item);
            if (!ok) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }

            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_productImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kProduct,
                    QString("edititem %1").arg(pProductResultPtr->m_item->m_id));
        } else {
            // new item
            ProductItemPtr pProductItemPtr(new ProductItem);
            //
            // get new attribute values
            //

            // id -> no needed
            // name
            pProductItemPtr->m_nameEus = this->ui->nameEusLineEdit->text();
            pProductItemPtr->m_nameEs = this->ui->nameEsLineEdit->text();
            // imagePath
            QString destFileName;
            // can be null, allowed by ddbb schema
            pProductItemPtr->m_imagePath = destFileName;
            if (!this->m_productImageFilename.isEmpty()) {
                // new image was selected
                pProductItemPtr->m_imagePath = Utils::newImageName("product", this->m_productImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductItemPtr->m_imagePath);
                QFile::copy(this->m_productImageFilename, destFilePath);
            }
            // active
            pProductItemPtr->m_active = this->ui->activeCheckBox->isChecked();
            // regDate
            pProductItemPtr->m_regDate = QDateTime::currentDateTimeUtc();
            // family
            pProductItemPtr->m_familyId = this->ui->familyComboBox->currentData().toInt();
            // price (already validated)
            pProductItemPtr->m_price = price;
            // providerId
            pProductItemPtr->m_providerId = this->ui->providerComboBox->currentData().toInt();
            // stock -> no change
            pProductItemPtr->m_stock = 0;
            // create in ddbb
            Int32 itemId = Singletons::m_pDAO->createProductItem(pProductItemPtr);
            if (itemId < 0) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kProduct,
                    QString("new item %1").arg(itemId));
        }

        // reset var
        this->m_productImageFilename.clear();
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Done successfully"),
                std::bind(&AdminProductItem::onProductItemUpdated, this)
                );
        // nothing should be added here
    }
    //
    void AdminProductItem::onProductItemUpdated()
    {
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kFamilyItemManagementWindowKey);
    }
    //
    void AdminProductItem::fillProductInfo(Int32 productId)
    {
        ProductItemResultPtr pProductItemResultPtr = Singletons::m_pDAO->getProductItem(productId);
        if (pProductItemResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pProductItemResultPtr->m_item) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProduct,
                    QString("item not found %1").arg(productId));
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // name
        this->ui->nameEusLineEdit->setText(pProductItemResultPtr->m_item->m_nameEus);
        this->ui->nameEsLineEdit->setText(pProductItemResultPtr->m_item->m_nameEs);
        // show image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductItemResultPtr->m_item->m_imagePath);
        QPixmap productPixmap = GuiUtils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(productPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(pProductItemResultPtr->m_item->m_active);
        // price
        this->ui->priceDoubleSpinBox->setValue(pProductItemResultPtr->m_item->m_price);
        // provider
        this->ui->providerComboBox->clear();
        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        Int32 currentIndex = 0;
        Int32 productProviderIndex = -1;
        for (auto iter = pProviderListResultPtr->m_list->begin(); iter != pProviderListResultPtr->m_list->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(currentIndex, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            if (pProviderPtr->m_id == pProductItemResultPtr->m_item->m_providerId) {
                productProviderIndex = currentIndex;
            }
            currentIndex++;
        }
        // get current provider
        this->ui->providerComboBox->setCurrentIndex(productProviderIndex);
        // family
        this->ui->familyComboBox->clear();
        ProductFamilyListResultPtr pfListPtr = Singletons::m_pDAO->getProductFamilies(false);
        if (pfListPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        currentIndex = 0;
        Int32 productFamilyIndex = -1;
        for (auto iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            ProductFamilyPtr pFamilyPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pFamilyPtr->m_imagePath);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->familyComboBox->insertItem(currentIndex, QIcon(productPixmap),
                    Singletons::m_pTranslationManager->getStringTranslation(pFamilyPtr->m_nameEus, pFamilyPtr->m_nameEs),
                    pFamilyPtr->m_id);
            if (pFamilyPtr->m_id == pProductItemResultPtr->m_item->m_familyId) {
                productFamilyIndex = currentIndex;
            }
            currentIndex++;
        }
        // get current family
        this->ui->familyComboBox->setCurrentIndex(productFamilyIndex);
    }
    //
    void AdminProductItem::initialize()
    {
        // name
        this->ui->nameEusLineEdit->clear();
        this->ui->nameEsLineEdit->clear();
        // show image
        QPixmap memberPixmap = GuiUtils::getImage("");
        this->ui->imageLabel->setPixmap(memberPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(true);
        // price, disable edit
        this->ui->priceDoubleSpinBox->setValue(0.0);
        // provider
        this->ui->providerComboBox->clear();
        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        Int32 currentIndex = 0;
        for (auto iter = pProviderListResultPtr->m_list->begin(); iter != pProviderListResultPtr->m_list->end(); ++iter) {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(currentIndex, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            currentIndex++;
        }
        // family
        this->ui->familyComboBox->clear();
        ProductFamilyListResultPtr pfListPtr = Singletons::m_pDAO->getProductFamilies(false);
        if (pfListPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        currentIndex = 0;
        for (auto iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            ProductFamilyPtr pFamilyPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pFamilyPtr->m_imagePath);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->familyComboBox->insertItem(currentIndex,
                    QIcon(productPixmap),
                    Singletons::m_pTranslationManager->getStringTranslation(pFamilyPtr->m_nameEus, pFamilyPtr->m_nameEs),
                    pFamilyPtr->m_id);
            currentIndex++;
        }
    }
    //
    void AdminProductItem::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProduct,
                    QString("Unable to write to %1").arg(imagePath.absoluteFilePath()));
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Unable to write to %1").arg(imagePath.absoluteFilePath()), [](){});
            return;
        }
        // open file dialog
        // start in home dir
        Singletons::m_pDialogManager->getOpenFileName(this, tr("Open File..."), QDir::homePath(),
                tr("Image Files (*.gif *.jpeg *.jpg *.png)"), QFileDialog::ExistingFile,
                std::bind(&AdminProductItem::onProductImageSelected, this, _1)
                );
        // nothing should be added here
    }
    //
    void AdminProductItem::onProductImageSelected(const QString &fn)
    {
        if (fn.isEmpty()) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("No file selected"), [](){});
            return;
        }
        // fn has absolute path
        this->m_productImageFilename = fn;
        // show image
        QPixmap providerPixmap = GuiUtils::getImage(fn);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
}
