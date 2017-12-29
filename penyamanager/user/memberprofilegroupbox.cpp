//

#include <QDir>

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include <commons/constants.h>
#include "memberprofilegroupbox.h"
#include "ui_memberprofilegroupbox.h"

namespace PenyaManager {
    //
    MemberProfileGroupBox::MemberProfileGroupBox(QWidget *parent) :
        QGroupBox(parent),
        ui(new Ui::MemberProfileGroupBox)
    {
        ui->setupUi(this);
    }
    //
    MemberProfileGroupBox::~MemberProfileGroupBox()
    {
        delete ui;
    }
    //
    void MemberProfileGroupBox::init(const MemberPtr &pMemberPtr)
    {
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pMemberPtr->m_imagePath);
        QPixmap memberPixmap = GuiUtils::getImage(imagePath);
        this->ui->memberImageLabel->setPixmap(memberPixmap);
        this->ui->memberImageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->memberImageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->memberImageLabel->setScaledContents(true);
        this->ui->membernameLabel->setText(pMemberPtr->m_name);
        this->ui->surname1Label->setText(pMemberPtr->m_surname1);
        this->ui->surname2Label->setText(pMemberPtr->m_surname2);
        this->ui->memberUsernameValueLabel->setText(QString::number(pMemberPtr->m_username));
        this->ui->memberAccountValueLabel->setText(QString("%1 €").arg(pMemberPtr->m_balance, 0, 'f', 2));
    }
    //
    void MemberProfileGroupBox::retranslate()
    {
        this->ui->retranslateUi(this);
    }
}
