//

#include <QDir>

#include "guiutils.h"
#include "singletons.h"
#include "constants.h"
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
        this->ui->nameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
        this->ui->memberIdValueLabel->setText(QString::number(pMemberPtr->m_id));
        this->ui->memberAccountValueLabel->setText(QString("%1 €").arg(pMemberPtr->m_balance, 0, 'f', 2));
    }
}
