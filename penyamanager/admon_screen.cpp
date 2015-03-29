#include "admon_screen.h"
#include "ui_admon_screen.h"

namespace PenyaManager {

admon_screen::admon_screen(QWidget *parent) :
    IPartner(parent),
    ui(new Ui::admon_screen)
{
    ui->setupUi(this);
}
void admon_screen::setParner(IPartner *partner)
{
    if(partner == 0)
        return;

    connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(this->ui->exitButton, SIGNAL(clicked()), partner, SLOT(init()));
}

admon_screen::~admon_screen()
{
    delete ui;
}

void admon_screen::init()
{
    //
    // Loading User profile
    //

    //MemberPtr pCurrMember = Singletons::m_pCurrMember;
    //fillAdminData();


    //
    // Show
    //

    show();
}

/*void admin_screen::fillAdminData(const MemberPtr &pMemberPtr)
{
    QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
    QPixmap memberPixmap = Utils::getImage(imagePath);
    this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
    this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
    this->ui->memberImage->setScaledContents(true);
    this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
    this->ui->memberIdInfo->setText(QString::number(pMemberPtr->m_id));
    this->ui->memberBalanceInfo->setText(QString::number(pMemberPtr->m_balance, 'f', 2));

}*/



}
