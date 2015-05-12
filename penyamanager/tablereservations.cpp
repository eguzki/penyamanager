//

#include "utils.h"
#include "singletons.h"
#include "tablereservations.h"
#include "ui_tablereservations.h"

namespace PenyaManager {

    //
    TableReservations::TableReservations(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::TableReservations)
    {
        ui->setupUi(this);
    }
    //
    TableReservations::~TableReservations()
    {
        delete ui;
    }
    //
    void TableReservations::init()
    {
        //
        // Loading User profile
        //

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillMemberProfile(pCurrMemberPtr);

        //
        // Show
        //

        show();
    }
    //
    void TableReservations::fillMemberProfile(const MemberPtr &pMemberPtr)
    {
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
        QPixmap memberPixmap = Utils::getImage(imagePath);
        this->ui->memberImage->setPixmap(memberPixmap);
        this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->memberImage->setScaledContents(true);
        this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
        this->ui->memberIdInfoLabel->setText(QString::number(pMemberPtr->m_id));
        this->ui->memberAccountInfoLabel->setText(QString::number(pMemberPtr->m_balance, 'f', 2));
    }
    //
    void TableReservations::on_backButton_clicked()
    {
        this->hide();
        // call main window
        IPartner* pMainWindow = Singletons::m_pParnetFinder->getPartner(Constants::kMainWindowKey);
        pMainWindow->init();
    }
    //
    void TableReservations::on_lunchButton_clicked()
    {

    }
    //
    void TableReservations::on_dinnerButton_clicked()
    {

    }
}


