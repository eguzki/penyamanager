//

#include <QDate>

#include "utils.h"
#include "singletons.h"
#include "memberview.h"
#include "ui_memberview.h"

namespace PenyaManager {
    //
    MemberView::MemberView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::MemberView),
        m_memberImageFilename()
    {
        ui->setupUi(this);
    }
    //
    MemberView::~MemberView()
    {
        delete ui;
    }
    //
    void MemberView::initialize()
    {
        // memberId
        this->ui->memberIdValueLabel->clear();
        // reg date
        this->ui->regDateValueLabel->setText(QDate::currentDate().toString());
        // name
        this->ui->nameLineEdit->clear();
        // surname
        this->ui->memberSurnameLineEdit->clear();
        // show image
        QPixmap memberPixmap = Utils::getImage("");
        this->ui->imageLabel->setPixmap(memberPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(true);
        // isAdmin
        this->ui->isAdminCheckBox->setChecked(false);
        // bank account
        this->ui->bankAccountLineEdit->clear();
        // birthdate
        // invalid date
        this->ui->birthdateDateEdit->setDate(this->ui->birthdateDateEdit->minimumDate());
        // email
        this->ui->emailLineEdit->clear();
        // address
        this->ui->addressLineEdit->clear();
        // zip code
        this->ui->zipCodeLineEdit->clear();
        // town
        this->ui->townLineEdit->clear();
        // state
        this->ui->stateLineEdit->clear();
        // phone
        this->ui->phoneLineEdit->clear();
        // phone 2
        this->ui->phone2LineEdit->clear();
        // postal send
        this->ui->postalSendCheckBox->setChecked(false);
        // notes
        this->ui->notesLineEdit->clear();
    }
    //
    void MemberView::init()
    {
        //
        // Product info
        //
        if (Singletons::m_currentMemberId >= 0) {
            fillMemberInfo(Singletons::m_currentMemberId);
        } else {
            initialize();
        }

        //
        // Show
        //

        show();
    }
    //
    void MemberView::on_savePushButton_clicked()
    {
        QDate date = this->ui->birthdateDateEdit->date();
        // on insert, if empty, leave it null in mysql
        if (date.year() == this->ui->birthdateDateEdit->minimumDate().year()) {
            qDebug() << "empty";
        } else {
            qDebug() << date.toString();
        }
    }
    //
    void MemberView::fillMemberInfo(Int32 memberId)
    {
        MemberPtr pMemberPtr = Singletons::m_pDAO->getMemberById(memberId);
        if (!pMemberPtr){
            return;
        }
        // memberId
        this->ui->memberIdValueLabel->setText(QString::number(pMemberPtr->m_id));
        // reg date
        this->ui->regDateValueLabel->setText(pMemberPtr->m_regDate.toString());
        // name
        this->ui->nameLineEdit->setText(pMemberPtr->m_name);
        // surname
        this->ui->memberSurnameLineEdit->setText(pMemberPtr->m_surname);
        // show image
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
        QPixmap productPixmap = Utils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(productPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(pMemberPtr->m_active);
        // isAdmin
        this->ui->isAdminCheckBox->setChecked(pMemberPtr->m_isAdmin);
        // bank account
        this->ui->bankAccountLineEdit->setText(pMemberPtr->m_bank_account);
        // birthdate
        if (pMemberPtr->m_birthdate.isValid()) {
            this->ui->birthdateDateEdit->setDate(pMemberPtr->m_birthdate);
        } else {
            this->ui->birthdateDateEdit->setDate(this->ui->birthdateDateEdit->minimumDate());
        }
        // email
        this->ui->emailLineEdit->setText(pMemberPtr->m_email);
        // address
        this->ui->addressLineEdit->setText(pMemberPtr->m_address);
        // zip code
        this->ui->zipCodeLineEdit->setText(pMemberPtr->m_zipCode);
        // town
        this->ui->townLineEdit->setText(pMemberPtr->m_town);
        // state
        this->ui->stateLineEdit->setText(pMemberPtr->m_state);
        // phone
        this->ui->phoneLineEdit->setText(pMemberPtr->m_phone);
        // phone 2
        this->ui->phone2LineEdit->setText(pMemberPtr->m_phone2);
        // postal send
        this->ui->postalSendCheckBox->setChecked(pMemberPtr->m_postalSend);
        // notes
        this->ui->notesLineEdit->setText(pMemberPtr->m_notes);
    }
}

