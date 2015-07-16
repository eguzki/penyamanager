#include "admon_screen.h"
#include "ui_admon_screen.h"
#include "dao.h"
#include "singletons.h"
#include <qmessagebox.h>



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


void admon_screen::fillMemberProfile(const MemberPtr &pMemberPtr)
{
    //QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
    //QPixmap memberPixmap = Utils::getImage(imagePath);
    //this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
    //this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
    //this->ui->memberImage->setScaledContents(true);
    //this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
    this->ui->textidmember->setText(QString::number(pMemberPtr->m_id));
    this->ui->textname->setText(pMemberPtr->m_name);
    this->ui->textsurname->setText(pMemberPtr->m_surname);
    this->ui->textreg_date->setText(pMemberPtr->m_regDate.toString());
    this->ui->activeCheckbox->setChecked(pMemberPtr->m_active);
    //this->ui->textisAdmin->setText(pMemberPtr->m_isAdmin);
    //this->ui->textbirth->setText(pMemberPtr->m_birth);
    this->ui->textaddress->setText(pMemberPtr->m_address);
    this->ui->textzip_code->setText(pMemberPtr->m_zipCode);
    this->ui->texttown->setText(pMemberPtr->m_town);
    this->ui->textstate->setText(pMemberPtr->m_state);
    this->ui->texttel->setText(QString::number(pMemberPtr->m_phone));
    this->ui->texttel2->setText(QString::number(pMemberPtr->m_phone2));
    this->ui->textemail->setText(pMemberPtr->m_email);
    this->ui->textbank_account->setText(pMemberPtr->m_bank_account);
    //this->ui->textpostal_send->setText(QString::number(pMemberPtr->m_postal_send));
    this->ui->textnotes->setText(pMemberPtr->m_notes);



    //this->ui->memberBalanceInfo->setText(QString::number(pMemberPtr->m_balance, 'f', 2));
}

}

void PenyaManager::admon_screen::on_pushButton_clicked()
{

}
