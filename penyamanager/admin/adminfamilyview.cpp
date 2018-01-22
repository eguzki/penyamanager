//
#include <QDateTime>

#include <commons/singletons.h>
#include <commons/utils.h>
#include <commons/guiutils.h>
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
        this->m_familyImageFilename.clear();
        //
        // Family info
        //

        if (Singletons::m_currentFamilyId >= 0) {
            fillFamilyInfo(Singletons::m_currentFamilyId);
        } else {
            initialize();
        }
    }
    //
    void AdminFamilyView::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void AdminFamilyView::on_savePushButton_clicked()
    {
        // validate name is not empty
        QString familyEusName = this->ui->nameEusLineEdit->text();
        if (familyEusName.isEmpty()){
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Basque name cannot be empty"), [](){});
            return;
        }
        QString familyEsName = this->ui->nameEsLineEdit->text();
        if (familyEsName.isEmpty()){
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Spanish name cannot be empty"), [](){});
            return;
        }

        // save in ddbb
        if (Singletons::m_currentFamilyId >= 0) {
            // edit previous item
            ProductFamilyResultPtr pFamilyResultPtr = Singletons::m_pDAO->getProductFamily(Singletons::m_currentFamilyId);
            if (pFamilyResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            if (!pFamilyResultPtr->m_family) {
                Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kFamily,
                        QString("item not found %1").arg(Singletons::m_currentFamilyId));
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pFamilyResultPtr->m_family->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pFamilyResultPtr->m_family->m_nameEus = this->ui->nameEusLineEdit->text();
            pFamilyResultPtr->m_family->m_nameEs = this->ui->nameEsLineEdit->text();
            // imagePath
            if (!this->m_familyImageFilename.isEmpty()) {
                // new image was selected
                pFamilyResultPtr->m_family->m_imagePath = Utils::newImageName("prodcategory", this->m_familyImageFilename);;
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pFamilyResultPtr->m_family->m_imagePath);
                QFile::copy(this->m_familyImageFilename, destFilePath);
            }
            // active
            pFamilyResultPtr->m_family->m_active = this->ui->activeCheckBox->isChecked();
            // regDate -> no change

            // update in ddbb
            bool ok = Singletons::m_pDAO->updateProductFamilyItem(pFamilyResultPtr->m_family);
            if (!ok) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_familyImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kFamily,
                    QString("edititem %1").arg(pFamilyResultPtr->m_family->m_id));
        } else {
            // new item
            ProductFamilyPtr pFamilyPtr(new ProductFamily);
            //
            // get new attribute values
            //

            // id -> no needed
            // name
            pFamilyPtr->m_nameEus = this->ui->nameEusLineEdit->text();
            pFamilyPtr->m_nameEs = this->ui->nameEsLineEdit->text();
            // imagePath
            QString destFileName;
            // can be null, allowed by ddbb schema
            pFamilyPtr->m_imagePath = destFileName;
            if (!this->m_familyImageFilename.isEmpty()) {
                // new image was selected
                pFamilyPtr->m_imagePath = Utils::newImageName("prodcategory", this->m_familyImageFilename);;
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pFamilyPtr->m_imagePath);
                QFile::copy(this->m_familyImageFilename, destFilePath);
            }
            // active
            pFamilyPtr->m_active = this->ui->activeCheckBox->isChecked();
            // regDate
            pFamilyPtr->m_regDate = QDateTime::currentDateTimeUtc();
            // create in ddbb
            Int32 familyId = Singletons::m_pDAO->createProductFamilyItem(pFamilyPtr);
            if (familyId < 0) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kFamily,
                    QString("newitem %1").arg(familyId));
        }

        // reset var
        this->m_familyImageFilename.clear();
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Done successfully"),
                std::bind(&AdminFamilyView::onFamilyUpdated, this)
                );
        // nothing should be added here
    }
    //
    void AdminFamilyView::onFamilyUpdated()
    {
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kFamilyItemManagementWindowKey);
    }
    //
    void AdminFamilyView::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kFamily,
                    QString("Unable to write to %1").arg(imagePath.absoluteFilePath()));
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Unable to write to %1").arg(imagePath.absoluteFilePath()), [](){});
            return;
        }

        // open file dialog
        // start in home dir
        Singletons::m_pDialogManager->getOpenFileName(this, tr("Open File..."), QDir::homePath(),
                tr("Image Files (*.gif *.jpeg *.jpg *.png)"), QFileDialog::FileMode::ExistingFile,
                std::bind(&AdminFamilyView::onFamilyImageSelected, this, _1)
                );
        // nothing should be added here
    }
    //
    void AdminFamilyView::onFamilyImageSelected(const QString &fn)
    {
        if (fn.isEmpty()) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("No file selected"), [](){});
            return;
        }
        // fn has absolute path
        this->m_familyImageFilename = fn;
        // show image
        QPixmap familyPixmap = GuiUtils::getImage(fn);
        // setting pixmap clears any previous content
        this->ui->imageLabel->setPixmap(familyPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
    //
    void AdminFamilyView::fillFamilyInfo(Int32 familyId)
    {
        ProductFamilyResultPtr pProductFamilyResultPtr = Singletons::m_pDAO->getProductFamily(familyId);
        if (pProductFamilyResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pProductFamilyResultPtr->m_family) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kFamily,
                    QString("item not found %1").arg(familyId));
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // name
        this->ui->nameEusLineEdit->setText(pProductFamilyResultPtr->m_family->m_nameEus);
        this->ui->nameEsLineEdit->setText(pProductFamilyResultPtr->m_family->m_nameEs);
        // show image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductFamilyResultPtr->m_family->m_imagePath);
        QPixmap familyPixmap = GuiUtils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(familyPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(pProductFamilyResultPtr->m_family->m_active);
    }
    //
    void AdminFamilyView::initialize()
    {
        // name
        this->ui->nameEusLineEdit->clear();
        this->ui->nameEsLineEdit->clear();
        // show image
        QPixmap familyPixmap = GuiUtils::getImage("");
        this->ui->imageLabel->setPixmap(familyPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(true);
    }
}

