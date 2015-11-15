//

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>

#include <QsLog.h>

#include "guiutils.h"
#include "constants.h"
#include "singletons.h"
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

        // initialize
        initialize();

        //
        // Show
        //

        show();
    }
    //
    void AdminNewProvider::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void AdminNewProvider::initialize()
    {
        this->ui->nameLineEdit->clear();
        this->ui->phoneLineEdit->clear();
        // no image, show default image
        QPixmap memberPixmap = GuiUtils::getImage("");
        this->ui->imageLabel->setPixmap(memberPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
    //
    void AdminNewProvider::on_imagePushButton_clicked()
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
        QString providerName = this->ui->nameLineEdit->text();
        if (providerName.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Name cannot be empty");
            return;
        }

        QString destFileName;

        if (!this->m_providerImageFilename.isEmpty()) {
            destFileName = Utils::newImageName("provider", this->m_providerImageFilename);
            QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
            QFile::copy(this->m_providerImageFilename, destFilePath);
        }

        // save in ddbb
        Singletons::m_pDAO->createProvider(providerName, destFileName, this->ui->phoneLineEdit->text());
        QLOG_INFO() << QString("[NewProvider] name %1").arg(providerName);
        QMessageBox::information(this, tr("New Provider"), tr("Provider created successfully"));

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

