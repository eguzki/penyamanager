//

#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>

#include "utils.h"
#include "singletons.h"
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

        //
        // Show
        //

        show();
    }
    //
    void AdminProductItem::on_savePushButton_clicked()
    {
        // validate name is not empty
        QString productName = this->ui->nameLineEdit->text();
        if (productName.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Name cannot be empty");
            return;
        }

        // validate price field
        //
        if (this->ui->priceLineEdit->text().isEmpty())
        {
            QMessageBox::warning(this, "Data missing", "price cannot be empty");
            return;
        }
        bool ok;
        Float price = this->ui->priceLineEdit->text().toFloat(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Data not valid", "price is not valid");
            return;
        }

        // image file
        QString destFileName;

        if (!this->m_productImageFilename.isEmpty()) {
            QFileInfo imageInfo(this->m_productImageFilename);
            // Copy file to destination
            QDateTime currentDateTime = QDateTime::currentDateTime();
            QString nameTemplate("product-%1.%2");
            destFileName = nameTemplate.arg(QString::number(currentDateTime.toMSecsSinceEpoch()/1000)).arg(imageInfo.suffix());
            QString destFilePath = QDir(Constants::kImageRootPath).filePath(destFileName);
            QFile::copy(this->m_productImageFilename, destFilePath);
        }

        // save in ddbb
        ProductItemPtr pProductPtr;
        if (Singletons::m_currentProductId >= 0) {
            // edit previous item
            pProductPtr = Singletons::m_pDAO->getProductItem(Singletons::m_currentProductId);
            // save old image in case we need to delete it
            QString oldImage = pProductPtr->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pProductPtr->m_name = this->ui->nameLineEdit->text();
            // imagePath
            if (!this->m_productImageFilename.isEmpty()) {
                // new image was selected
                pProductPtr->m_imagePath = destFileName;
            }
            // active
            pProductPtr->m_active = this->ui->activeCheckBox->isEnabled();
            // regDate -> no change
            // family
            pProductPtr->m_familyId = this->ui->familyComboBox->currentData().toInt();
            // price -> no change
            // providerId
            pProductPtr->m_providerId = this->ui->providerComboBox->currentData().toInt();
            // stock -> no change

            // update in ddbb
            Singletons::m_pDAO->updateProductItem(pProductPtr);
            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_productImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Constants::kImageRootPath).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
        } else {
            // new item
            pProductPtr = ProductItemPtr(new ProductItem);
            //
            // get new attribute values
            //

            // id -> no needed
            // name
            pProductPtr->m_name = this->ui->nameLineEdit->text();
            // imagePath
            pProductPtr->m_imagePath = destFileName;
            // active
            pProductPtr->m_active = this->ui->activeCheckBox->isEnabled();
            // regDate
            pProductPtr->m_regDate = QDateTime::currentDateTime();
            // family
            pProductPtr->m_familyId = this->ui->familyComboBox->currentData().toInt();
            // price (already validated)
            pProductPtr->m_price = this->ui->priceLineEdit->text().toFloat();
            // providerId
            pProductPtr->m_providerId = this->ui->providerComboBox->currentData().toInt();
            // stock -> no change
            pProductPtr->m_stock = 0;
            // create in ddbb
            Singletons::m_pDAO->createProductItem(pProductPtr);
        }

        // reset var
        this->m_productImageFilename.clear();
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kFamilyItemManagementWindowKey);
    }
    //
    void AdminProductItem::fillProductInfo(Int32 productId)
    {
        ProductItemPtr pProductPtr = Singletons::m_pDAO->getProductItem(productId);
        // name
        this->ui->nameLineEdit->setText(pProductPtr->m_name);
        // show image
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pProductPtr->m_imagePath);
        QPixmap productPixmap = Utils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(productPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setEnabled(pProductPtr->m_active);
        // price, disable edit
        this->ui->priceLineEdit->setText(QString("%1 €").arg(pProductPtr->m_price));
        this->ui->priceLineEdit->setReadOnly(true);
        // provider
        this->ui->providerComboBox->clear();
        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();
        Int32 currentIndex = 0;
        Int32 productProviderIndex = -1;
        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Constants::kImageRootPath).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = Utils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(currentIndex, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            if (pProviderPtr->m_id == pProductPtr->m_providerId) {
                productProviderIndex = currentIndex;
            }
            currentIndex++;
        }
        // get current provider
        this->ui->providerComboBox->setCurrentIndex(productProviderIndex);
        // family
        this->ui->familyComboBox->clear();
        ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies();
        currentIndex = 0;
        Int32 productFamilyIndex = -1;
        for (auto iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
        {
            ProductFamilyPtr pFamilyPtr = *iter;
            QString providerImagePath = QDir(Constants::kImageRootPath).filePath(pFamilyPtr->m_imagePath);
            QPixmap productPixmap = Utils::getImage(providerImagePath);
            this->ui->familyComboBox->insertItem(currentIndex, QIcon(productPixmap), pFamilyPtr->m_name, pFamilyPtr->m_id);
            if (pFamilyPtr->m_id == pProductPtr->m_familyId) {
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
        QPixmap memberPixmap = Utils::getImage("");
        this->ui->imageLabel->setPixmap(memberPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setEnabled(true);
        // price, disable edit
        this->ui->priceLineEdit->clear();
        this->ui->priceLineEdit->setReadOnly(false);
        // provider
        this->ui->providerComboBox->clear();
        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();
        Int32 currentIndex = 0;
        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Constants::kImageRootPath).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = Utils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(currentIndex, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            currentIndex++;
        }
        // family
        this->ui->familyComboBox->clear();
        ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies();
        currentIndex = 0;
        for (auto iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
        {
            ProductFamilyPtr pFamilyPtr = *iter;
            QString providerImagePath = QDir(Constants::kImageRootPath).filePath(pFamilyPtr->m_imagePath);
            QPixmap productPixmap = Utils::getImage(providerImagePath);
            this->ui->familyComboBox->insertItem(currentIndex, QIcon(productPixmap), pFamilyPtr->m_name, pFamilyPtr->m_id);
            currentIndex++;
        }
    }
    //
    void AdminProductItem::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Constants::kImageRootPath);
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            QMessageBox::warning(this, "Could not write", Constants::kImageRootPath);
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
        QPixmap providerPixmap = Utils::getImage(fn);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
}

