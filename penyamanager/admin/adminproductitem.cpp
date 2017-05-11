//

#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>

#include <QsLog.h>

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
        QString productName = this->ui->nameLineEdit->text();
        if (productName.isEmpty()){
            QMessageBox::warning(this, tr("Data missing"), tr("Name cannot be empty"));
            return;
        }

        // validate price field
        Float price = this->ui->priceDoubleSpinBox->value();
        if (!price) {
            QMessageBox::warning(this, tr("Data not valid"), tr("price cannot be 0.00€"));
            return;
        }
        // validate providers
        if (!this->ui->providerComboBox->count())
        {
            QMessageBox::warning(this, tr("Data missing"), tr("Providers list is empty. Add some providers first"));
            return;
        }
        // validate families
        if (!this->ui->familyComboBox->count())
        {
            QMessageBox::warning(this, tr("Data missing"), tr("Family list is empty. Add some families first"));
            return;
        }

        // save in ddbb
        if (Singletons::m_currentProductId >= 0) {
            // edit previous item
            ProductItemResultPtr pProductResultPtr = Singletons::m_pDAO->getProductItem(Singletons::m_currentProductId);
            if (pProductResultPtr->m_error) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
                return;
            }
            if (!pProductResultPtr->m_item) {
                QLOG_WARN() << QString("Editing item [id: %1] not found in ddbb").arg(Singletons::m_currentProductId);
                QMessageBox::warning(this, tr("Unexpected state"), tr("Operation not performed. Contact administrator"));
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pProductResultPtr->m_item->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pProductResultPtr->m_item->m_name = this->ui->nameLineEdit->text();
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
            // price -> no change
            // providerId
            pProductResultPtr->m_item->m_providerId = this->ui->providerComboBox->currentData().toInt();
            // stock -> no change

            // update in ddbb
            bool ok = Singletons::m_pDAO->updateProductItem(pProductResultPtr->m_item);
            if (!ok) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
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
            QLOG_INFO() << QString("[EditItem] ID %1").arg(pProductResultPtr->m_item->m_id);
        } else {
            // new item
            ProductItemPtr pProductItemPtr(new ProductItem);
            //
            // get new attribute values
            //

            // id -> no needed
            // name
            pProductItemPtr->m_name = this->ui->nameLineEdit->text();
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
            pProductItemPtr->m_regDate = QDateTime::currentDateTime();
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
                QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
                return;
            }
            QLOG_INFO() << QString("[NewItem] ID %1").arg(itemId);
        }

        // reset var
        this->m_productImageFilename.clear();
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kFamilyItemManagementWindowKey);
    }
    //
    void AdminProductItem::fillProductInfo(Int32 productId)
    {
        ProductItemResultPtr pProductItemResultPtr = Singletons::m_pDAO->getProductItem(productId);
        if (pProductItemResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        // name
        this->ui->nameLineEdit->setText(pProductItemResultPtr->m_item->m_name);
        // show image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductItemResultPtr->m_item->m_imagePath);
        QPixmap productPixmap = GuiUtils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(productPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(pProductItemResultPtr->m_item->m_active);
        // price, disable edit
        this->ui->priceDoubleSpinBox->setValue(pProductItemResultPtr->m_item->m_price);
        this->ui->priceDoubleSpinBox->setReadOnly(true);
        // provider
        this->ui->providerComboBox->clear();
        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
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
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        currentIndex = 0;
        Int32 productFamilyIndex = -1;
        for (auto iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            ProductFamilyPtr pFamilyPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pFamilyPtr->m_imagePath);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->familyComboBox->insertItem(currentIndex, QIcon(productPixmap), pFamilyPtr->m_name, pFamilyPtr->m_id);
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
        this->ui->nameLineEdit->clear();
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
        this->ui->priceDoubleSpinBox->setReadOnly(false);
        // provider
        this->ui->providerComboBox->clear();
        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
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
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        currentIndex = 0;
        for (auto iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            ProductFamilyPtr pFamilyPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pFamilyPtr->m_imagePath);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->familyComboBox->insertItem(currentIndex, QIcon(productPixmap), pFamilyPtr->m_name, pFamilyPtr->m_id);
            currentIndex++;
        }
    }
    //
    void AdminProductItem::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            QMessageBox::warning(this, "Could not write", Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
            return;
        }
        // open file dialog
        // start in home dir
        // fn has absolute path
        QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                QDir::homePath(), tr("Image Files (*.gif *.jpeg *.jpg *.png)"));
        if (fn.isEmpty()) {
            QMessageBox::information(this, "Information", "No file selected");
            return;
        }
        this->m_productImageFilename = fn;
        // show image
        QPixmap providerPixmap = GuiUtils::getImage(fn);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
}

