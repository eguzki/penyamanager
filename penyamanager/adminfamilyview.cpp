//

#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>

#include "utils.h"
#include "singletons.h"
#include "adminfamilyview.h"
#include "ui_adminfamilyview.h"

namespace PenyaManager {
    //
    AdminFamilyView::AdminFamilyView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AdminFamilyView),
        m_switchCentralWidgetCallback(callback),
        m_familyImageFilename()
    {
        ui->setupUi(this);
    }
    //
    AdminFamilyView::~AdminFamilyView()
    {
        delete ui;
    }
    //
    void AdminFamilyView::init()
    {
        //
        // Family info
        //

        if (Singletons::m_currentFamilyId >= 0) {
            fillFamilyInfo(Singletons::m_currentFamilyId);
        } else {
            initialize();
        }

        //
        // Show
        //

        show();
    }
    //
    void AdminFamilyView::on_savePushButton_clicked()
    {
        // validate name is not empty
        QString familyName = this->ui->nameLineEdit->text();
        if (familyName.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Name cannot be empty");
            return;
        }

        // save in ddbb
        ProductFamilyPtr pFamilyPtr;
        if (Singletons::m_currentFamilyId >= 0) {
            // edit previous item
            pFamilyPtr = Singletons::m_pDAO->getProductFamily(Singletons::m_currentFamilyId);
            if (!pFamilyPtr) {
                QMessageBox::warning(this, "Unexpected state", QString("Editing item [id: %1] not found in ddbb").arg(Singletons::m_currentFamilyId));
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pFamilyPtr->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pFamilyPtr->m_name = this->ui->nameLineEdit->text();
            // imagePath
            if (!this->m_familyImageFilename.isEmpty()) {
                // new image was selected
                pFamilyPtr->m_imagePath = Utils::newImageName("prodcategory", this->m_familyImageFilename);;
                QString destFilePath = QDir(Constants::kImageRootPath).filePath(pFamilyPtr->m_imagePath);
                QFile::copy(this->m_familyImageFilename, destFilePath);
            }
            // active
            pFamilyPtr->m_active = this->ui->activeCheckBox->isChecked();
            // regDate -> no change

            // update in ddbb
            Singletons::m_pDAO->updateProductFamilyItem(pFamilyPtr);
            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_familyImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Constants::kImageRootPath).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
        } else {
            // new item
            pFamilyPtr = ProductFamilyPtr(new ProductFamily);
            //
            // get new attribute values
            //

            // id -> no needed
            // name
            pFamilyPtr->m_name = this->ui->nameLineEdit->text();
            // imagePath
            QString destFileName;
            // can be null, allowed by ddbb schema
            pFamilyPtr->m_imagePath = destFileName;
            if (!this->m_familyImageFilename.isEmpty()) {
                // new image was selected
                pFamilyPtr->m_imagePath = Utils::newImageName("prodcategory", this->m_familyImageFilename);;
                QString destFilePath = QDir(Constants::kImageRootPath).filePath(pFamilyPtr->m_imagePath);
                QFile::copy(this->m_familyImageFilename, destFilePath);
            }
            // active
            pFamilyPtr->m_active = this->ui->activeCheckBox->isChecked();
            // regDate
            pFamilyPtr->m_regDate = QDateTime::currentDateTime();
            // create in ddbb
            Singletons::m_pDAO->createProductFamilyItem(pFamilyPtr);
        }

        // reset var
        this->m_familyImageFilename.clear();
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kFamilyItemManagementWindowKey);

    }
    //
    void AdminFamilyView::on_imagePushButton_clicked()
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
        this->m_familyImageFilename = fn;
        // show image
        QPixmap familyPixmap = Utils::getImage(fn);
        // setting pixmap clears any previous content
        this->ui->imageLabel->setPixmap(familyPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
    //
    void AdminFamilyView::fillFamilyInfo(Int32 familyId)
    {
        ProductFamilyPtr pProductFamilyPtr = Singletons::m_pDAO->getProductFamily(familyId);
        // name
        this->ui->nameLineEdit->setText(pProductFamilyPtr->m_name);
        // show image
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pProductFamilyPtr->m_imagePath);
        QPixmap familyPixmap = Utils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(familyPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(pProductFamilyPtr->m_active);
    }
    //
    void AdminFamilyView::initialize()
    {
        // name
        this->ui->nameLineEdit->clear();
        // show image
        QPixmap familyPixmap = Utils::getImage("");
        this->ui->imageLabel->setPixmap(familyPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(true);
    }
}
