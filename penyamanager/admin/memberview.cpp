//

#include <QMessageBox>
#include <QFileDialog>

#include <commons/guiutils.h>
#include <commons/utils.h>
#include <commons/singletons.h>
#include "passchangedialog.h"
#include "memberview.h"
#include "ui_memberview.h"

namespace PenyaManager {
    //
    MemberView::MemberView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::MemberView),
        m_memberImageFilename(),
        m_minDate(1900, 1, 1),
        m_switchCentralWidgetCallback(callback)
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
        // member username
        Int32 proposedUsername = Singletons::m_pDAO->getLastUsername();
        if (proposedUsername < 0) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            // call family product management window throw adminmainwindow
            m_switchCentralWidgetCallback(WindowKey::kMemberListViewWindowKey);
            return;
        }
        this->ui->usernameLineEdit->setText(QString::number(proposedUsername + 1));
        // reg date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(QDate::currentDate(), QLocale::NarrowFormat);
        this->ui->regDateValueLabel->setText(dateLocalized);
        // reg date
        this->ui->lastLoginValueLabel->setText("-");
        // name
        this->ui->nameLineEdit->clear();
        // surname1
        this->ui->memberSurname1LineEdit->clear();
        // surname2
        this->ui->memberSurname2LineEdit->clear();
        // show image
        QPixmap memberPixmap = GuiUtils::getImage("");
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
        this->ui->birthdateDateEdit->setDate(this->m_minDate);
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
        this->ui->notesTextEdit->clear();
        // idCard
        this->ui->idCardLineEdit->clear();
        // Card number
        this->ui->cardLineEdit->clear();
        // MemberType
        this->ui->memberTypeComboBox->clear();
        this->ui->memberTypeComboBox->insertItem(Member::NORMAL, GetStringFromMemberType(Member::NORMAL), Member::NORMAL);
        this->ui->memberTypeComboBox->insertItem(Member::RETIRED, GetStringFromMemberType(Member::RETIRED), Member::RETIRED);
        this->ui->memberTypeComboBox->insertItem(Member::HONORARY, GetStringFromMemberType(Member::HONORARY), Member::HONORARY);
        this->ui->memberTypeComboBox->setCurrentIndex(Member::NORMAL);
    }
    //
    void MemberView::init()
    {
        this->m_memberImageFilename.clear();
        // change password button
        this->ui->changePasswordPushButton->setEnabled(Singletons::m_currentMemberId >= 0);
        //
        // Member info
        //
        if (Singletons::m_currentMemberId >= 0) {
            fillMemberInfo(Singletons::m_currentMemberId);
        } else {
            initialize();
        }
    }
    //
    void MemberView::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void MemberView::on_savePushButton_clicked()
    {
        // Validate not empty fields
        // username
        QString memberUsernameStr = this->ui->usernameLineEdit->text();
        bool usernameOk = false;
        if (!memberUsernameStr.isEmpty()){
            memberUsernameStr.toInt(&usernameOk);
        }
        if (!usernameOk) {
            QMessageBox::warning(this, tr("Data missing"), tr("Username must be correct number"));
            return;
        }
        // name
        QString memberName = this->ui->nameLineEdit->text();
        if (memberName.isEmpty()){
            QMessageBox::warning(this, tr("Data missing"), tr("Name cannot be empty"));
            return;
        }
        // surname1
        QString memberSurname1 = this->ui->memberSurname1LineEdit->text();
        if (memberSurname1.isEmpty()){
            QMessageBox::warning(this, tr("Data missing"), tr("First surname cannot be empty"));
            return;
        }
        // surname2
        QString memberSurname2 = this->ui->memberSurname2LineEdit->text();
        if (memberSurname2.isEmpty()){
            QMessageBox::warning(this, tr("Data missing"), tr("Second surname cannot be empty"));
            return;
        }
        // bank_account
        // TODO check bank account format
        QString bankAccount = this->ui->bankAccountLineEdit->text();
        if (bankAccount.isEmpty()){
            QMessageBox::warning(this, tr("Data missing"), tr("Bank Account cannot be empty"));
            return;
        }

        // save in ddbb
        if (Singletons::m_currentMemberId >= 0) {
            // edit previous item
            MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
            if (pMemberResultPtr->m_error) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            if (!pMemberResultPtr->m_member) {
                Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kMember,
                        QString("Editing itemid %1 not found in ddbb").arg(Singletons::m_currentMemberId));
                QMessageBox::warning(this, tr("Unexpected state"), tr("Operation not performed. Contact administrator"));
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pMemberResultPtr->m_member->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pMemberResultPtr->m_member->m_name = this->ui->nameLineEdit->text();
            // username
            pMemberResultPtr->m_member->m_username = this->ui->usernameLineEdit->text().toInt();
            // surname1
            pMemberResultPtr->m_member->m_surname1 = this->ui->memberSurname1LineEdit->text();
            // surname2
            pMemberResultPtr->m_member->m_surname2 = this->ui->memberSurname2LineEdit->text();
            // imagePath (optional)
            if (!this->m_memberImageFilename.isEmpty()) {
                QString destFileName = Utils::newImageName("member", this->m_memberImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
                QFile::copy(this->m_memberImageFilename, destFilePath);
                // new image was selected
                pMemberResultPtr->m_member->m_imagePath = destFileName;
            }
            // active
            pMemberResultPtr->m_member->m_active = this->ui->activeCheckBox->isChecked();
            // isAdmin
            pMemberResultPtr->m_member->m_isAdmin = this->ui->isAdminCheckBox->isChecked();
            // bank account
            pMemberResultPtr->m_member->m_bank_account = this->ui->bankAccountLineEdit->text();
            // birthdate
            QDate birthdate = this->ui->birthdateDateEdit->date();
            pMemberResultPtr->m_member->m_birthdate = (birthdate == this->m_minDate)?(QDate()):(birthdate);
            // postal send
            pMemberResultPtr->m_member->m_postalSend = this->ui->postalSendCheckBox->isChecked();
            // email (optional)
            pMemberResultPtr->m_member->m_email = this->ui->emailLineEdit->text();
            // address (optional)
            pMemberResultPtr->m_member->m_address = this->ui->addressLineEdit->text();
            // zip code (optional)
            pMemberResultPtr->m_member->m_zipCode = this->ui->zipCodeLineEdit->text();
            // town (optional)
            pMemberResultPtr->m_member->m_town = this->ui->townLineEdit->text();
            // state (optional)
            QString state = this->ui->stateLineEdit->text();
            // phone (optional)
            pMemberResultPtr->m_member->m_phone = this->ui->phoneLineEdit->text();
            // phone 2 (optional)
            pMemberResultPtr->m_member->m_phone2 = this->ui->phone2LineEdit->text();
            // notes (optional)
            pMemberResultPtr->m_member->m_notes = this->ui->notesTextEdit->toPlainText();
            // regDate -> no change
            // lastmodfies
            pMemberResultPtr->m_member->m_lastModified = QDateTime::currentDateTimeUtc();
            // card id
            pMemberResultPtr->m_member->m_idCard = this->ui->idCardLineEdit->text();
            // card number
            pMemberResultPtr->m_member->m_cardNumber = this->ui->cardLineEdit->text();
            // member type
            pMemberResultPtr->m_member->m_memberType = this->ui->memberTypeComboBox->currentData().toUInt();

            // update in ddbb
            bool ok = Singletons::m_pDAO->updateMember(pMemberResultPtr->m_member);
            if (!ok) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_memberImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kMember,
                    QString("editmember %1").arg(pMemberResultPtr->m_member->m_id));
            QMessageBox::information(this, tr("Update Member"), tr("Done successfully"));
        } else {
            // new item
            MemberPtr pMemberPtr(new Member);
            //
            // get new attribute values
            //

            // id -> no needed
            // username
            pMemberPtr->m_username = this->ui->usernameLineEdit->text().toInt();
            // Check username is not in use
            BoolResult usernameUsed = Singletons::m_pDAO->checkUsername(pMemberPtr->m_username);
            if (usernameUsed.error) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            if (usernameUsed.result) {
                QMessageBox::warning(this, tr("Wrong username"), tr("username already in use"));
                return;
            }
            // name
            pMemberPtr->m_name = this->ui->nameLineEdit->text();
            // surname1
            pMemberPtr->m_surname1 = this->ui->memberSurname1LineEdit->text();
            pMemberPtr->m_surname2 = this->ui->memberSurname2LineEdit->text();
            // imagePath (optional)
            if (!this->m_memberImageFilename.isEmpty()) {
                // new image was selected
                QString destFileName = Utils::newImageName("member", this->m_memberImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
                QFile::copy(this->m_memberImageFilename, destFilePath);
                pMemberPtr->m_imagePath = destFileName;
            }
            // active
            pMemberPtr->m_active = this->ui->activeCheckBox->isChecked();
            // isAdmin
            pMemberPtr->m_isAdmin = this->ui->isAdminCheckBox->isChecked();
            // bank account
            pMemberPtr->m_bank_account = this->ui->bankAccountLineEdit->text();
            // birthdate
            QDate birthdate = this->ui->birthdateDateEdit->date();
            pMemberPtr->m_birthdate = (birthdate == this->m_minDate)?(QDate()):(birthdate);
            // postal send
            pMemberPtr->m_postalSend = this->ui->postalSendCheckBox->isChecked();
            // email (optional)
            pMemberPtr->m_email = this->ui->emailLineEdit->text();
            // address (optional)
            pMemberPtr->m_address = this->ui->addressLineEdit->text();
            // zip code (optional)
            pMemberPtr->m_zipCode = this->ui->zipCodeLineEdit->text();
            // town (optional)
            pMemberPtr->m_town = this->ui->townLineEdit->text();
            // state (optional)
            pMemberPtr->m_state = this->ui->stateLineEdit->text();
            // phone (optional)
            pMemberPtr->m_phone = this->ui->phoneLineEdit->text();
            // phone 2 (optional)
            pMemberPtr->m_phone2 = this->ui->phone2LineEdit->text();
            // notes (optional)
            pMemberPtr->m_notes = this->ui->notesTextEdit->toPlainText();
            // regDate
            pMemberPtr->m_regDate = QDateTime::currentDateTimeUtc();
            // lastmodfies
            pMemberPtr->m_lastModified = QDateTime::currentDateTimeUtc();
            // last Login
            pMemberPtr->m_lastLogin = QDateTime::currentDateTimeUtc();
            // default password: "0000"
            pMemberPtr->m_pwd = Utils::hashSHA256asHex("0000");
            // card id
            pMemberPtr->m_idCard = this->ui->idCardLineEdit->text();
            // card number
            pMemberPtr->m_cardNumber = this->ui->cardLineEdit->text();
            // member type
            pMemberPtr->m_memberType = this->ui->memberTypeComboBox->currentData().toUInt();
            // create in ddbb
            Int32 memberId = Singletons::m_pDAO->createMember(pMemberPtr);
            if (memberId < 0) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            // create account
            bool ok = Singletons::m_pServices->createAccountTransaction(memberId, 0.0, QString(""), TransactionType::NewAccount);
            if (!ok) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kMember,
                    QString("newmember %1").arg(memberId));
            QMessageBox::information(this, tr("Create new member"), tr("Done successfully"));
        }

        // reset var
        this->m_memberImageFilename.clear();
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kMemberListViewWindowKey);
    }
    //
    void MemberView::fillMemberInfo(Int32 memberId)
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(memberId);
        if (pMemberResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }
        // reg date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pMemberResultPtr->m_member->m_regDate, QLocale::NarrowFormat);
        this->ui->regDateValueLabel->setText(dateLocalized);
        // last login date
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pMemberResultPtr->m_member->m_lastLogin, QLocale::NarrowFormat);
        this->ui->lastLoginValueLabel->setText(dateLocalized);
        // username
        this->ui->usernameLineEdit->setText(QString::number(pMemberResultPtr->m_member->m_username));
        // name
        this->ui->nameLineEdit->setText(pMemberResultPtr->m_member->m_name);
        // surname1
        this->ui->memberSurname1LineEdit->setText(pMemberResultPtr->m_member->m_surname1);
        // surname2
        this->ui->memberSurname2LineEdit->setText(pMemberResultPtr->m_member->m_surname2);
        // show image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pMemberResultPtr->m_member->m_imagePath);
        QPixmap productPixmap = GuiUtils::getImage(imagePath);
        this->ui->imageLabel->setPixmap(productPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
        // active
        this->ui->activeCheckBox->setChecked(pMemberResultPtr->m_member->m_active);
        // isAdmin
        this->ui->isAdminCheckBox->setChecked(pMemberResultPtr->m_member->m_isAdmin);
        // bank account
        this->ui->bankAccountLineEdit->setText(pMemberResultPtr->m_member->m_bank_account);
        // birthdate
        if (pMemberResultPtr->m_member->m_birthdate.isValid()) {
            this->ui->birthdateDateEdit->setDate(pMemberResultPtr->m_member->m_birthdate);
        } else {
            this->ui->birthdateDateEdit->setDate(this->m_minDate);
        }
        // email
        this->ui->emailLineEdit->setText(pMemberResultPtr->m_member->m_email);
        // address
        this->ui->addressLineEdit->setText(pMemberResultPtr->m_member->m_address);
        // zip code
        this->ui->zipCodeLineEdit->setText(pMemberResultPtr->m_member->m_zipCode);
        // town
        this->ui->townLineEdit->setText(pMemberResultPtr->m_member->m_town);
        // state
        this->ui->stateLineEdit->setText(pMemberResultPtr->m_member->m_state);
        // phone
        this->ui->phoneLineEdit->setText(pMemberResultPtr->m_member->m_phone);
        // phone 2
        this->ui->phone2LineEdit->setText(pMemberResultPtr->m_member->m_phone2);
        // postal send
        this->ui->postalSendCheckBox->setChecked(pMemberResultPtr->m_member->m_postalSend);
        // notes
        this->ui->notesTextEdit->setPlainText(pMemberResultPtr->m_member->m_notes);
        // id card
        this->ui->idCardLineEdit->setText(pMemberResultPtr->m_member->m_idCard);
        // card number
        this->ui->cardLineEdit->setText(pMemberResultPtr->m_member->m_cardNumber);
        // member type
        this->ui->memberTypeComboBox->clear();
        this->ui->memberTypeComboBox->insertItem(Member::NORMAL, GetStringFromMemberType(Member::NORMAL), Member::NORMAL);
        this->ui->memberTypeComboBox->insertItem(Member::RETIRED, GetStringFromMemberType(Member::RETIRED), Member::RETIRED);
        this->ui->memberTypeComboBox->insertItem(Member::HONORARY, GetStringFromMemberType(Member::HONORARY), Member::HONORARY);
        this->ui->memberTypeComboBox->setCurrentIndex(pMemberResultPtr->m_member->m_memberType);
    }
    //
    void MemberView::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kMember,
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
        this->m_memberImageFilename = fn;
        // show image
        QPixmap providerPixmap = GuiUtils::getImage(fn);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
    //
    void MemberView::on_changePasswordPushButton_clicked()
    {
        if (Singletons::m_currentMemberId < 0)
        {
            return;
        }

        PassChangeDialog passChangeDialg;
        int result = passChangeDialg.exec();
        if (result == QDialog::Rejected) {
            return;
        }

        QString pwdHash = Utils::hashSHA256asHex(passChangeDialg.getPassword());

        // save new password in ddbb
        bool ok = Singletons::m_pDAO->changeMemberPassword(Singletons::m_currentMemberId, pwdHash, QDateTime::currentDateTimeUtc());
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kMember,
                QString("passchange memberid %1").arg(Singletons::m_currentMemberId));
        QMessageBox::information(this, tr("Change password"), tr("Password changed successfully"));
    }
}

