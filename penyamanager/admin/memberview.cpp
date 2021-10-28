//
#include <QCalendarWidget>

#include <commons/guiutils.h>
#include <commons/utils.h>
#include <commons/singletons.h>
#include <commons/timedmessagebox.h>
#include "timedfiledialog.h"
#include "timedpasschangedialog.h"
#include "timedmemberdropdialog.h"
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

        this->ui->regDateDateEdit->calendarWidget()->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->birthdateDateEdit->calendarWidget()->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->inactivityStartDateEdit->calendarWidget()->setLocale(Singletons::m_pTranslationManager->getLocale());
        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // set maximum selectable date
        this->ui->inactivityStartDateEdit->setMaximumDate(toInitialDate);
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
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // RegDate
        this->ui->regDateDateEdit->setDate(QDate::currentDate());
        // proposed username
        this->ui->usernameLineEdit->setText(QString::number(proposedUsername + 1));
        // last login date
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
        // Account balance
        this->ui->accountBalanceValueLabel->setText(QString("%1 €").arg(0.0, 0, 'f', 2));
        // New Account Entry button
        this->ui->depositButton->setEnabled(false);
        // Drop member button
        this->ui->dropPushButton->setVisible(false);
    }
    //
    void MemberView::init()
    {
        this->m_memberImageFilename.clear();
        // change password button
        this->ui->changePasswordPushButton->setEnabled(Singletons::m_currentMemberId >= 0);
        // status
        this->ui->statusWidget->setVisible(Singletons::m_currentMemberId >= 0);
        //
        // Member info
        //
        if (Singletons::m_currentMemberId >= 0) {
            fillMemberInfo(Singletons::m_currentMemberId);
        } else {
            initialize();
        }
        //
        hideNewAccountEntryForm();
    }
    //
    void MemberView::retranslate()
    {
        this->ui->retranslateUi(this);
        this->ui->regDateDateEdit->calendarWidget()->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->birthdateDateEdit->calendarWidget()->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->inactivityStartDateEdit->calendarWidget()->setLocale(Singletons::m_pTranslationManager->getLocale());
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
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Username must be correct number"), [](){});
            return;
        }
        // name
        QString memberName = this->ui->nameLineEdit->text();
        if (memberName.isEmpty()){
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Name cannot be empty"), [](){});
            return;
        }
        // surname1
        QString memberSurname1 = this->ui->memberSurname1LineEdit->text();
        if (memberSurname1.isEmpty()){
            TimedMessageBox::criticalMessageBoxTitled(this, tr("First surname cannot be empty"), [](){});
            return;
        }
        // surname2
        QString memberSurname2 = this->ui->memberSurname2LineEdit->text();
        if (memberSurname2.isEmpty()){
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Second surname cannot be empty"), [](){});
            return;
        }
        // bank_account
        // TODO check bank account format
        QString bankAccount = this->ui->bankAccountLineEdit->text();
        if (bankAccount.isEmpty()){
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Bank Account cannot be empty"), [](){});
            return;
        }

        // save in ddbb
        if (Singletons::m_currentMemberId >= 0) {
            // edit previous item
            MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
            if (pMemberResultPtr->m_error) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            if (!pMemberResultPtr->m_member) {
                Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                        QString("Editing itemid %1 not found in ddbb").arg(Singletons::m_currentMemberId));
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pMemberResultPtr->m_member->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pMemberResultPtr->m_member->m_name = this->ui->nameLineEdit->text().trimmed();
            // username
            pMemberResultPtr->m_member->m_username = this->ui->usernameLineEdit->text().toInt();
            // surname1
            pMemberResultPtr->m_member->m_surname1 = this->ui->memberSurname1LineEdit->text().trimmed();
            // surname2
            pMemberResultPtr->m_member->m_surname2 = this->ui->memberSurname2LineEdit->text().trimmed();
            // imagePath (optional)
            if (!this->m_memberImageFilename.isEmpty()) {
                QString destFileName = Utils::newImageName("member", this->m_memberImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
                QFile::copy(this->m_memberImageFilename, destFilePath);
                // new image was selected
                pMemberResultPtr->m_member->m_imagePath = destFileName;
            }
            // isAdmin
            pMemberResultPtr->m_member->m_isAdmin = this->ui->isAdminCheckBox->isChecked();
            // bank account
            pMemberResultPtr->m_member->m_bank_account = this->ui->bankAccountLineEdit->text().trimmed();
            // birthdate
            QDate birthdate = this->ui->birthdateDateEdit->date();
            pMemberResultPtr->m_member->m_birthdate = (birthdate == this->m_minDate)?(QDate()):(birthdate);
            // postal send
            pMemberResultPtr->m_member->m_postalSend = this->ui->postalSendCheckBox->isChecked();
            // email (optional)
            pMemberResultPtr->m_member->m_email = this->ui->emailLineEdit->text().trimmed();
            // address (optional)
            pMemberResultPtr->m_member->m_address = this->ui->addressLineEdit->text().trimmed();
            // zip code (optional)
            pMemberResultPtr->m_member->m_zipCode = this->ui->zipCodeLineEdit->text().trimmed();
            // town (optional)
            pMemberResultPtr->m_member->m_town = this->ui->townLineEdit->text().trimmed();
            // state (optional)
            pMemberResultPtr->m_member->m_state = this->ui->stateLineEdit->text().trimmed();
            // phone (optional)
            pMemberResultPtr->m_member->m_phone = this->ui->phoneLineEdit->text().trimmed();
            // phone 2 (optional)
            pMemberResultPtr->m_member->m_phone2 = this->ui->phone2LineEdit->text().trimmed();
            // notes (optional)
            pMemberResultPtr->m_member->m_notes = this->ui->notesTextEdit->toPlainText();
            // regDate
            pMemberResultPtr->m_member->m_regDate = this->ui->regDateDateEdit->date().startOfDay();
            pMemberResultPtr->m_member->m_regDate.setTimeSpec(Qt::UTC);
            // lastmodified
            pMemberResultPtr->m_member->m_lastModified = QDateTime::currentDateTimeUtc();
            // card id
            pMemberResultPtr->m_member->m_idCard = this->ui->idCardLineEdit->text().trimmed();
            // card number
            pMemberResultPtr->m_member->m_cardNumber = this->ui->cardLineEdit->text().trimmed();
            // member type
            pMemberResultPtr->m_member->m_memberType = this->ui->memberTypeComboBox->currentData().toUInt();

            // update in ddbb
            bool ok = Singletons::m_pDAO->updateMember(pMemberResultPtr->m_member);
            if (!ok) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
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
            Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                    QString("editmember %1").arg(pMemberResultPtr->m_member->m_id));
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
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            if (usernameUsed.result) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("username already in use"), [](){});
                return;
            }
            // name
            pMemberPtr->m_name = this->ui->nameLineEdit->text().trimmed();
            // surname1
            pMemberPtr->m_surname1 = this->ui->memberSurname1LineEdit->text().trimmed();
            pMemberPtr->m_surname2 = this->ui->memberSurname2LineEdit->text().trimmed();
            // imagePath (optional)
            if (!this->m_memberImageFilename.isEmpty()) {
                // new image was selected
                QString destFileName = Utils::newImageName("member", this->m_memberImageFilename);
                QString destFilePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(destFileName);
                QFile::copy(this->m_memberImageFilename, destFilePath);
                pMemberPtr->m_imagePath = destFileName;
            }
            // active
            // By default will be activated
            pMemberPtr->m_active = Member::ACTIVE;
            // isAdmin
            pMemberPtr->m_isAdmin = this->ui->isAdminCheckBox->isChecked();
            // bank account
            pMemberPtr->m_bank_account = this->ui->bankAccountLineEdit->text().trimmed();
            // birthdate
            QDate birthdate = this->ui->birthdateDateEdit->date();
            pMemberPtr->m_birthdate = (birthdate == this->m_minDate)?(QDate()):(birthdate);
            // postal send
            pMemberPtr->m_postalSend = this->ui->postalSendCheckBox->isChecked();
            // email (optional)
            pMemberPtr->m_email = this->ui->emailLineEdit->text().trimmed();
            // address (optional)
            pMemberPtr->m_address = this->ui->addressLineEdit->text().trimmed();
            // zip code (optional)
            pMemberPtr->m_zipCode = this->ui->zipCodeLineEdit->text().trimmed();
            // town (optional)
            pMemberPtr->m_town = this->ui->townLineEdit->text().trimmed();
            // state (optional)
            pMemberPtr->m_state = this->ui->stateLineEdit->text().trimmed();
            // phone (optional)
            pMemberPtr->m_phone = this->ui->phoneLineEdit->text().trimmed();
            // phone 2 (optional)
            pMemberPtr->m_phone2 = this->ui->phone2LineEdit->text().trimmed();
            // notes (optional)
            pMemberPtr->m_notes = this->ui->notesTextEdit->toPlainText();
            // regDate
            pMemberPtr->m_regDate = this->ui->regDateDateEdit->date().startOfDay();
            pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
            // lastmodfies
            pMemberPtr->m_lastModified = QDateTime::currentDateTimeUtc();
            // last Login
            pMemberPtr->m_lastLogin = QDateTime::currentDateTimeUtc();
            // default password: "0000"
            pMemberPtr->m_pwd = Utils::hashSHA256asHex("0000");
            // card id
            pMemberPtr->m_idCard = this->ui->idCardLineEdit->text().trimmed();
            // card number
            pMemberPtr->m_cardNumber = this->ui->cardLineEdit->text().trimmed();
            // member type
            pMemberPtr->m_memberType = this->ui->memberTypeComboBox->currentData().toUInt();
            // create in ddbb
            Int32 memberId = Singletons::m_pDAO->createMember(pMemberPtr);
            if (memberId < 0) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            // create account
            bool ok = Singletons::m_pServices->createAccountTransaction(memberId, 0.0, QString(""), TransactionType::NewAccount);
            if (!ok) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                    QString("newmember %1").arg(memberId));
            Singletons::m_currentMemberId = memberId;
        }

        // reset var
        this->m_memberImageFilename.clear();
        TimedMessageBox::infoMessageBoxTitled(this, tr("Done successfully"),
                std::bind(&MemberView::onMemberUpdated, this)
                );
        // nothing should be added here
    }
    //
    void MemberView::onMemberUpdated()
    {
        init();
    }
    //
    void MemberView::fillMemberInfo(Int32 memberId)
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(memberId);
        if (pMemberResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }
        // reg date
        this->ui->regDateDateEdit->setDate(pMemberResultPtr->m_member->m_regDate.date());
        // last login date
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pMemberResultPtr->m_member->m_lastLogin, QLocale::NarrowFormat);
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
        // Account balance
        this->ui->accountBalanceValueLabel->setText(QString("%1 €").arg(pMemberResultPtr->m_member->m_balance, 0, 'f', 2));
        // New Account Entry button
        this->ui->depositButton->setEnabled(true);

        // Status
        this->ui->activatePushButton->setVisible(!pMemberResultPtr->m_member->IsActive());
        this->ui->deactivatePushButton->setVisible(pMemberResultPtr->m_member->IsActive());
        this->ui->label_5->setVisible(pMemberResultPtr->m_member->IsActive());
        this->ui->inactivityStartDateEdit->setDate(QDate::currentDate());
        this->ui->inactivityStartDateEdit->setVisible(pMemberResultPtr->m_member->IsActive());
        this->ui->renewalWidget->setVisible(!pMemberResultPtr->m_member->IsActive());
        this->ui->renewPushButton->setEnabled(
                !pMemberResultPtr->m_member->IsActive() &&
                pMemberResultPtr->m_member->m_inactiveStartDate.isValid() &&
                pMemberResultPtr->m_member->m_inactiveModificationDate.isValid() &&
                pMemberResultPtr->m_member->m_inactiveModificationDate != QDate::currentDate()
                );
        QPixmap statusPixmap = GuiUtils::getImage(pMemberResultPtr->m_member->IsActive() ? (":images/icon-active.png"):(":images/icon-inactive.png"));
        this->ui->memberStatus->setPixmap(statusPixmap);
        this->ui->memberStatus->setFixedWidth(25);
        this->ui->memberStatus->setFixedHeight(25);
        this->ui->memberStatus->setScaledContents(true);

        if (!pMemberResultPtr->m_member->IsActive()) {
            // inactive_start
            if (pMemberResultPtr->m_member->m_inactiveStartDate.isValid()) {
                QString tmp = Singletons::m_pTranslationManager->getLocale().toString(pMemberResultPtr->m_member->m_inactiveStartDate, QLocale::NarrowFormat);
                this->ui->inactiveStartDateLabel->setText(tmp);
            } else {
                this->ui->inactiveStartDateLabel->setText("-");
            }
            // inactive_modification_date
            if (pMemberResultPtr->m_member->m_inactiveModificationDate.isValid()) {
                QString tmp = Singletons::m_pTranslationManager->getLocale().toString(pMemberResultPtr->m_member->m_inactiveModificationDate, QLocale::NarrowFormat);
                this->ui->lastRenewalDateLabel->setText(tmp);
            } else {
                this->ui->lastRenewalDateLabel->setText("-");
            }
        }

        // Drop member button
        this->ui->dropPushButton->setVisible(Singletons::m_pCurrMember->m_id != memberId);
    }
    //
    void MemberView::on_imagePushButton_clicked()
    {
        // Check write permissions
        QFileInfo imagePath(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString());
        if (!imagePath.isDir() || !imagePath.isWritable()) {
            Singletons::m_pLogger->Warn(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                    QString("Unable to write to %1").arg(imagePath.absoluteFilePath()));
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Unable to write to %1").arg(imagePath.absoluteFilePath()), [](){});
            return;
        }
        // open file dialog
        // start in home dir
        TimedFileDialog::fileDialog(this, tr("Open File..."), QDir::homePath(),
                tr("Image Files (*.gif *.jpeg *.jpg *.png)"), QFileDialog::AcceptOpen,
                std::bind(&MemberView::onMemberImageSelected, this, _1)
                );
        // nothing should be added here
        return;
    }
    //
    void MemberView::onMemberImageSelected(const QString &fn)
    {
        // fn has absolute path
        if (fn.isEmpty()) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("No file selected"), [](){});
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

        TimedPassChangeDialog::passChangeDialog(this, std::bind(&MemberView::onPassGiven, this, _1, _2));
        // nothing should be added here
        return;
    }
    //
    void MemberView::onPassGiven(int res, QString pass)
    {
        if (res == QDialog::Rejected) {
            return;
        }

        QString pwdHash = Utils::hashSHA256asHex(pass);

        // save new password in ddbb
        bool ok = Singletons::m_pDAO->changeMemberPassword(Singletons::m_currentMemberId, pwdHash, QDateTime::currentDateTimeUtc());
        if (!ok) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                QString("passchange memberid %1").arg(Singletons::m_currentMemberId));
        TimedMessageBox::infoMessageBoxTitled(this, tr("Password changed successfully"), [](){});
        // nothing should be added here
    }
    //
    void MemberView::hideNewAccountEntryForm() {
        this->ui->newAccountEntryGroupBox->setMaximumHeight(0);
    }
    //
    void MemberView::showNewAccountEntryForm() {
        this->ui->errorLabel->setHidden(true);
        this->ui->descriptionLineEdit->clear();
        this->ui->entryDoubleSpinBox->setValue(0.0);
        this->ui->entryDoubleRepeatedSpinBox->setValue(0.0);
        // Show animation
        QPropertyAnimation *animation = new QPropertyAnimation(ui->newAccountEntryGroupBox, "maximumHeight");
        animation->setDuration(2000);
        animation->setStartValue(this->ui->newAccountEntryGroupBox->maximumHeight());
        animation->setEndValue(1550);
        animation->start();
    }
    //
    bool MemberView::newAccountEntryFormEnabled() {
        return this->ui->newAccountEntryGroupBox->maximumHeight() == 0;
    }
    //
    void MemberView::on_depositButton_clicked()
    {
        if (newAccountEntryFormEnabled()) {
            showNewAccountEntryForm();
        }
    }
    //
    void MemberView::on_newAccountSavePushButton_clicked()
    {
        // Check entry values match
        if (this->ui->entryDoubleSpinBox->value() != this->ui->entryDoubleRepeatedSpinBox->value()) {
            this->ui->errorLabel->setHidden(false);
            this->ui->errorLabel->setText(tr("Entry values do not match"));
            return;
        }
        // Check description not empty
        if (this->ui->descriptionLineEdit->text().isEmpty()) {
            this->ui->errorLabel->setHidden(false);
            this->ui->errorLabel->setText(tr("Description value cannot be empty"));
            return;
        }

        // create account register info
        bool ok = Singletons::m_pServices->createAccountTransaction(Singletons::m_currentMemberId,
                this->ui->entryDoubleSpinBox->value(), this->ui->descriptionLineEdit->text(), TransactionType::AccountFix);
        if (!ok) {
            TimedMessageBox::infoMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                QString("new account fix entry: %1 €; memberId %2 ").arg(this->ui->entryDoubleSpinBox->value(), 0, 'f', 2).arg(Singletons::m_currentMemberId));
        TimedMessageBox::infoMessageBoxTitled(this, tr("New account entry created successfully"),
                std::bind(&MemberView::newAccountEntrySaved, this));
    }
    //
    void MemberView::newAccountEntrySaved()
    {
        init();
    }
    //
    void MemberView::on_activatePushButton_clicked()
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
        if (pMemberResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }

        pMemberResultPtr->m_member->m_active = Member::ACTIVE;
        pMemberResultPtr->m_member->m_inactiveStartDate = QDate();
        pMemberResultPtr->m_member->m_inactiveModificationDate = QDate();

        // update in ddbb
        bool ok = Singletons::m_pDAO->updateMember(pMemberResultPtr->m_member);
        if (!ok) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                QString("activated %1").arg(Singletons::m_currentMemberId));
        init();
    }
    //
    void MemberView::on_deactivatePushButton_clicked()
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
        if (pMemberResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }

        pMemberResultPtr->m_member->m_active = Member::INACTIVE;
        pMemberResultPtr->m_member->m_inactiveStartDate = this->ui->inactivityStartDateEdit->date();
        pMemberResultPtr->m_member->m_inactiveModificationDate = this->ui->inactivityStartDateEdit->date();

        // update in ddbb
        bool ok = Singletons::m_pDAO->updateMember(pMemberResultPtr->m_member);
        if (!ok) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                QString("deactivated %1").arg(Singletons::m_currentMemberId));
        init();
    }
    //
    void MemberView::on_renewPushButton_clicked()
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
        if (pMemberResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }

        if (!pMemberResultPtr->m_member->IsActive()) {
            bool ok = Singletons::m_pDAO->renewInactiveMember(Singletons::m_currentMemberId, QDate::currentDate());
            if (!ok) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                    QString("inactivity renewed %1").arg(Singletons::m_currentMemberId));
        }
        init();
    }
    //
    void MemberView::on_dropPushButton_clicked()
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
        if (pMemberResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }

        TimedMemberDropDialog::memberDropDialog(this, pMemberResultPtr->m_member->m_name,
                std::bind(&MemberView::onMemberDroped, this));
        // no code should be added after infoMessageBox
        return;
    }
    //
    void MemberView::onMemberDroped()
    {
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_currentMemberId);
        if (pMemberResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member){
            return;
        }

        pMemberResultPtr->m_member->m_active = Member::DROPPED;
        // lastmodified
        pMemberResultPtr->m_member->m_lastModified = QDateTime::currentDateTimeUtc();

        // update in ddbb
        bool ok = Singletons::m_pDAO->updateMember(pMemberResultPtr->m_member);
        if (!ok) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                QString("dropped %1").arg(Singletons::m_currentMemberId));

        m_switchCentralWidgetCallback(WindowKey::kMemberListViewWindowKey);
        return;
    }
}
