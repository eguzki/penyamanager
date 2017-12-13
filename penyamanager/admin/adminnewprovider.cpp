//

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>

#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include "adminnewprovider.h"
#include "ui_adminnewprovider.h"

namespace PenyaManager {
    //
    AdminNewProvider::AdminNewProvider(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AdminNewProvider),
        m_switchCentralWidgetCallback(callback),
        m_providerImageFilename()
    {
        ui->setupUi(this);
    }
    //
    AdminNewProvider::~AdminNewProvider()
    {
        delete ui;
    }
    //
    void AdminNewProvider::init()
    {
        m_providerImageFilename.clear();
        //
        // Provider info
        //
        if (Singletons::m_currentProviderId >= 0) {
            fillProviderInfo(Singletons::m_currentProviderId);
        } else {
            initialize();
        }
    }
    //
    void AdminNewProvider::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void AdminNewProvider::initialize()
    {
        this->ui->providerInfoWidget->setHidden(true);
        this->ui->nameLineEdit->clear();
        this->ui->phoneLineEdit->clear();
        // no image, show default image
        QPixmap memberPixmap = GuiUtils::getImage("");
        this->ui->imageLabel->setPixmap(memberPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // notes
        this->ui->notesTextEdit->clear();
    }
    //
    void AdminNewProvider::fillProviderInfo(Int32 providerId)
    {
        ProviderResultPtr pProviderResultPtr = Singletons::m_pDAO->getProviderById(providerId);
        if (pProviderResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (!pProviderResultPtr->m_provider){
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                    QString("Unable to find providerId by id %1").arg(QString::number(providerId)));
            return;
        }
        this->ui->providerInfoWidget->setHidden(false);
        // id
        this->ui->idValueLabel->setText(QString::number(pProviderResultPtr->m_provider->m_id));
        // reg date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pProviderResultPtr->m_provider->m_regDate, QLocale::NarrowFormat);
        this->ui->regDateValueLabel->setText(dateLocalized);
        // name
        this->ui->nameLineEdit->setText(pProviderResultPtr->m_provider->m_name);
        // phone
        this->ui->phoneLineEdit->setText(pProviderResultPtr->m_provider->m_phone);
        // show image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProviderResultPtr->m_provider->m_image);
        QPixmap providerPixmap = GuiUtils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // notes
        this->ui->notesTextEdit->setPlainText(pProviderResultPtr->m_provider->m_notes);
    }
    //
    void AdminNewProvider::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                    QString("Unable to write to %1").arg(imagePath.absoluteFilePath()));
            QMessageBox::warning(this, tr("Unable to upload image"),
                    QString("Unable to write to %1").arg(imagePath.absoluteFilePath()));
            return;
        }
        // open file dialog
        // start in home dir
        // fn has absolute path
        QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                QDir::homePath(), tr("Image Files (*.gif *.jpeg *.jpg *.png)"));
        if (fn.isEmpty()) {
            QMessageBox::information(this, tr("Information"), tr("No file selected"));
            return;
        }
        // this object member is being assigned only on image push.
        // On save, it will be known new image has been assigned
        this->m_providerImageFilename = fn;
        // show image
        QPixmap providerPixmap = GuiUtils::getImage(fn);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
    //
    void AdminNewProvider::on_savePushButton_clicked()
    {
        // validate name is not empty
        QString providerName = this->ui->nameLineEdit->text().trimmed();
        if (providerName.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Name cannot be empty");
            return;
        }

        //
        // get new attribute values
        //
        ProviderPtr pProviderPtr(new Provider);
        // name
        pProviderPtr->m_name = providerName;
        // phone
        pProviderPtr->m_phone = this->ui->phoneLineEdit->text().trimmed();

        // save in ddbb
        if (Singletons::m_currentProviderId >= 0) {
            ProviderResultPtr pProviderResultPtr = Singletons::m_pDAO->getProviderById(Singletons::m_currentProviderId);
            if (pProviderResultPtr->m_error) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            if (!pProviderResultPtr->m_provider){
                Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                        QString("Unable to find providerId by id %1").arg(Singletons::m_currentProviderId));
                return;
            }
            // id
            pProviderPtr->m_id = Singletons::m_currentProviderId;
            // reg_date
            pProviderPtr->m_regDate = pProviderResultPtr->m_provider->m_regDate;
            // imagePath (optional)
            // save old image in case we need to delete it
            QString oldImage = pProviderResultPtr->m_provider->m_image;
            pProviderPtr->m_image = oldImage;
            if (!this->m_providerImageFilename.isEmpty()) {
                // this->m_providerImageFilename only not empty when user has selected image
                // user has selected new image
                QString destFileName = Utils::newImageName("provider", this->m_providerImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
                QFile::copy(this->m_providerImageFilename, destFilePath);
                // new image was selected
                pProviderPtr->m_image = destFileName;
            }
            // notes (optional)
            pProviderPtr->m_notes = this->ui->notesTextEdit->toPlainText();
            // update in ddbb
            bool ok = Singletons::m_pDAO->updateProvider(pProviderPtr);
            if (!ok) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_providerImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                    QString("editprovider %1").arg(Singletons::m_currentProviderId));
            QMessageBox::information(this, tr("Update provider"), tr("Done successfully"));
        } else {
            // new provider
            // reg_date
            pProviderPtr->m_regDate = QDateTime::currentDateTimeUtc().date();
            // imagePath (optional)
            if (!this->m_providerImageFilename.isEmpty()) {
                // new image was selected
                QString destFileName = Utils::newImageName("provider", this->m_providerImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
                QFile::copy(this->m_providerImageFilename, destFilePath);
                pProviderPtr->m_image = destFileName;
            }
            // notes (optional)
            pProviderPtr->m_notes = this->ui->notesTextEdit->toPlainText();
            Int32 providerId = Singletons::m_pDAO->createProvider(pProviderPtr);
            if (providerId < 0) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                    QString("newprovider %1").arg(providerId));
            QMessageBox::information(this, tr("Create new provider"), tr("Done successfully"));
        }

        // reset var
        this->m_providerImageFilename.clear();
        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminProviderWindowKey);
    }
    //
    void AdminNewProvider::on_backPushButton_clicked()
    {
        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminProviderWindowKey);
    }
}

