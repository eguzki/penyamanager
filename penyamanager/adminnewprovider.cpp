//

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "constants.h"
#include "adminnewprovider.h"
#include "ui_adminnewprovider.h"

namespace PenyaManager {
    //
    AdminNewProvider::AdminNewProvider(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AdminNewProvider),
        m_switchCentralWidgetCallback(callback)
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
    void AdminNewProvider::initialize()
    {
        // no image, show default image
        QPixmap memberPixmap = Utils::getImage("");
        this->ui->imageLabel->setPixmap(memberPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
    //
    void AdminNewProvider::on_imagePushButton_clicked()
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
        if (!fn.isEmpty()) {
        }
        // http://creative-punch.net/2014/02/opening-displaying-saving-images-qt/
    }
    //
    void AdminNewProvider::on_savePushButton_clicked()
    {
        // validate name is not empty

    }
    //
    void AdminNewProvider::on_backPushButton_clicked()
    {
        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kAdminProviderWindowKey);

    }
}

