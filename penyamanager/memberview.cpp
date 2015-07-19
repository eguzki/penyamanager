//

#include <QMessageBox>
#include <QFileDialog>

#include "utils.h"
#include "singletons.h"
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
        // Validate not empty fields
        // name
        QString memberName = this->ui->nameLineEdit->text();
        if (memberName.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Name cannot be empty");
            return;
        }
        // surname
        QString memberSurname = this->ui->memberSurnameLineEdit->text();
        if (memberSurname.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Surname cannot be empty");
            return;
        }
        // bank_account
        QString bankAccount = this->ui->bankAccountLineEdit->text();
        if (bankAccount.isEmpty()){
            QMessageBox::warning(this, "Data missing", "Bank Account cannot be empty");
            return;
        }
        // TODO check bank account format
        // image file
        QString destFileName;

        if (!this->m_memberImageFilename.isEmpty()) {
            QFileInfo imageInfo(this->m_memberImageFilename);
            // Copy file to destination
            QDateTime currentDateTime = QDateTime::currentDateTime();
            QString nameTemplate("product-%1.%2");
            destFileName = nameTemplate.arg(QString::number(currentDateTime.toMSecsSinceEpoch()/1000)).arg(imageInfo.suffix());
            QString destFilePath = QDir(Constants::kImageRootPath).filePath(destFileName);
            QFile::copy(this->m_memberImageFilename, destFilePath);
        }

        // save in ddbb
        MemberPtr pMemberPtr;
        if (Singletons::m_currentMemberId >= 0) {
            // edit previous item
            pMemberPtr = Singletons::m_pDAO->getMemberById(Singletons::m_currentMemberId);
            if (!pMemberPtr) {
                QMessageBox::warning(this, "Unexpected state", QString("Editing item [id: %1] not found in ddbb").arg(Singletons::m_currentMemberId));
                return;
            }
            // save old image in case we need to delete it
            QString oldImage = pMemberPtr->m_imagePath;

            //
            // get new attribute values
            //

            // id -> no change
            // name
            pMemberPtr->m_name = this->ui->nameLineEdit->text();
            // surname
            pMemberPtr->m_surname = this->ui->memberSurnameLineEdit->text();
            // imagePath (optional)
            if (!this->m_memberImageFilename.isEmpty()) {
                // new image was selected
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
            QString state = this->ui->stateLineEdit->text();
            // phone (optional)
            pMemberPtr->m_phone = this->ui->phoneLineEdit->text();
            // phone 2 (optional)
            pMemberPtr->m_phone2 = this->ui->phone2LineEdit->text();
            // notes (optional)
            pMemberPtr->m_notes = this->ui->notesLineEdit->text();
            // regDate -> no change
            // lastmodfies
            pMemberPtr->m_lastModified = QDateTime::currentDateTime();

            // update in ddbb
            Singletons::m_pDAO->updateMember(pMemberPtr);
            // if there is previously one image, and it has been changed -> delete it
            // make sure it is after being updated in ddbb
            if (!this->m_memberImageFilename.isEmpty() && !oldImage.isEmpty()) {
                // delete previous file
                QString oldImagePath = QDir(Constants::kImageRootPath).filePath(oldImage);
                QFile oldFile(oldImagePath);
                oldFile.remove();
            }
        } else {
            // new item
            pMemberPtr = MemberPtr(new Member);
            //
            // get new attribute values
            //

            // id -> no needed
            // name
            pMemberPtr->m_name = this->ui->nameLineEdit->text();
            // surname
            pMemberPtr->m_surname = this->ui->memberSurnameLineEdit->text();
            // imagePath (optional)
            if (!this->m_memberImageFilename.isEmpty()) {
                // new image was selected
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
            pMemberPtr->m_notes = this->ui->notesLineEdit->text();
            // regDate
            pMemberPtr->m_regDate = QDateTime::currentDateTime();
            // lastmodfies
            pMemberPtr->m_lastModified = QDateTime::currentDateTime();
            // create in ddbb
            Int32 memberId = Singletons::m_pDAO->createMember(pMemberPtr);

            // create account
            Singletons::m_pServices->createAccountTransaction(memberId, 0.0, "new account", TransactionType::DepositFix);
        }

        // reset var
        this->m_memberImageFilename.clear();
        QMessageBox::information(this, "Create Member", "Done successfully");
        // call family product management window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kMemberListViewWindowKey);
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
            this->ui->birthdateDateEdit->setDate(this->m_minDate);
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
    //
    void MemberView::on_imagePushButton_clicked()
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
        if (fn.isEmpty()) {
            QMessageBox::information(this, "Information", "No file selected");
            return;
        }
        this->m_memberImageFilename = fn;
        // show image
        QPixmap providerPixmap = Utils::getImage(fn);
        this->ui->imageLabel->setPixmap(providerPixmap);
        this->ui->imageLabel->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->imageLabel->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->imageLabel->setScaledContents(true);
    }
}

