//

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "memberlistview.h"
#include "ui_memberlistview.h"

namespace PenyaManager {
    //
    MemberListView::MemberListView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::MemberListView),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        initializeTable();
    }
    //
    MemberListView::~MemberListView()
    {
        delete ui;
    }
    //
    void MemberListView::initializeTable()
    {
        // table
        this->ui->memberTableWidget->setColumnCount(7);
        translateTable();
        Uint32 column = 0;
        this->ui->memberTableWidget->setColumnWidth(column++, Constants::kFamilyImageWidth);
        this->ui->memberTableWidget->setColumnWidth(column++, 200);
        this->ui->memberTableWidget->setColumnWidth(column++, 100);
        this->ui->memberTableWidget->setColumnWidth(column++, 80);
        this->ui->memberTableWidget->setColumnWidth(column++, 60);
        this->ui->memberTableWidget->setColumnWidth(column++, 300);
        this->ui->memberTableWidget->setColumnWidth(column++, 60);
    }
    //
    void MemberListView::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("Image"));
        headers.append(tr("Surnames"));
        headers.append(tr("Name"));
        headers.append(tr("Username"));
        headers.append(tr("Balance"));
        headers.append(tr("Email"));
        headers.append(tr("Active"));
        this->ui->memberTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void MemberListView::init()
    {
        // will emit valueChanged() if the new value is different from the old one
        int page = this->ui->pageNumberSpinBox->value();
        if (page != 1) {
            this->ui->pageNumberSpinBox->setValue(1);
        } else {
            updateResults();
        }
    }
    //
    void MemberListView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void MemberListView::updateResults()
    {
        MemberListResultPtr pMemberListResultPtr;
        MemberListStatsResultPtr pMemberListStatsResultPtr;

        Int32 currentPage = this->ui->pageNumberSpinBox->value();
        bool filterPostalSend = this->ui->filterPostalUsersCheckBox->checkState() == Qt::CheckState::Checked;
        pMemberListResultPtr = Singletons::m_pDAO->getMemberList(filterPostalSend, currentPage-1, Constants::kInvoiceListPageCount);
        if (pMemberListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        pMemberListStatsResultPtr = Singletons::m_pDAO->getMemberListStats(filterPostalSend);
        if (pMemberListStatsResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Int32 numPages = (Int32)ceil((Float)pMemberListStatsResultPtr->m_stats->m_totalMembers/Constants::kInvoiceListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(currentPage > 1);
            this->ui->prev10PagePushButton->setEnabled(currentPage > 10);
            this->ui->nextPagePushButton->setEnabled(currentPage < numPages);
            this->ui->next10PagePushButton->setEnabled(currentPage < numPages-9);
            this->ui->totalPagesValueLabel->setText(QString::number(numPages));
            this->ui->pageNumberSpinBox->setRange(1, numPages);
        }
        // fill total stats view
        this->ui->totalMembersValueLabel->setText(QString::number(pMemberListStatsResultPtr->m_stats->m_totalMembers));
        // fill invoice list
        fillMemberList(pMemberListResultPtr->m_list);
    }
    //
    void MemberListView::on_newMemberPushButton_clicked()
    {
        // setting m_currentMemberId < 0, MemberView will initialize empty
        Singletons::m_currentMemberId = -1;
        // call member window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kMemberViewKey);
    }
    //
    void MemberListView::fillMemberList(const MemberListPtr &pMemberListPtr)
    {
        if (pMemberListPtr->size() > 0) {
            this->ui->csvPushButton->setEnabled(true);
        } else {
            this->ui->csvPushButton->setEnabled(false);
        }
        // num rows
        this->ui->memberTableWidget->setRowCount(pMemberListPtr->size());
        // member table reset
        this->ui->memberTableWidget->clearContents();
        // internal data structure reset
        this->m_rowProductIdMap.clear();

        // fill data
        Uint32 rowCount = 0;
        for (MemberList::iterator iter = pMemberListPtr->begin(); iter != pMemberListPtr->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            // image
            QTableWidgetItem *memberImageWidget = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pMemberPtr->m_imagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            memberImageWidget->setData(Qt::DecorationRole, productItemPixmap);
            Uint32 column = 0;
            this->ui->memberTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->memberTableWidget->setItem(rowCount, column++, memberImageWidget);
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString("%1 %2").arg(pMemberPtr->m_surname1).arg(pMemberPtr->m_surname2)));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pMemberPtr->m_name));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pMemberPtr->m_username)));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pMemberPtr->m_balance, 'f', 2)));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pMemberPtr->m_email));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem((pMemberPtr->m_active)?(QString::number(1)):(QString::number(0))));
            this->m_rowProductIdMap[rowCount] = pMemberPtr->m_id;
            rowCount++;
        }
    }
    //
    void MemberListView::on_memberTableWidget_cellDoubleClicked(int row, int column)
    {
        UNUSEDPARAMETER(column);
        auto rowMap = m_rowProductIdMap.find(row);
        if (rowMap == m_rowProductIdMap.end()) {
            //this should never happen
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kMember,
                    QString("memberlistview. MemberID not found and should be in the map"));
            return;
        }
        Int32 memberId = rowMap->second;
        // use static global variable to pass argument
        Singletons::m_currentMemberId = memberId;

        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kMemberViewKey);
    }
    //
    void MemberListView::on_csvPushButton_clicked()
    {
        // Assume member list is not empty (buttons should be disabled)
        // open file dialog
        // start in home dir
        Singletons::m_pDialogManager->getOpenFileName(this, tr("Open File..."), QDir::homePath(),
                tr("CSV Files (*.csv)"), QFileDialog::AnyFile,
                std::bind(&MemberListView::onMemberListCsvSelected, this, _1)
                );
        // nothing should be added here
    }
    //
    void MemberListView::onMemberListCsvSelected(const QString &fn)
    {
        if (fn.isNull()){
            return;
        }

        QString filename = Utils::addSuffix(fn, "csv");

        // fetch data
        bool filterPostalSend = this->ui->filterPostalUsersCheckBox->checkState() == Qt::CheckState::Checked;
        // max 1M users
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getMemberList(filterPostalSend, 0, 1000000);
        if (pMemberListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Error opening %1").arg(filename), [](){});
            return;
        }
        QTextStream out(&f);
        out.setCodec("UTF-8");

        // header
        // print header
        out << tr("Username") << ","
            << tr("Name") << ","
            << tr("Surname 1") << ","
            << tr("Surname 2") << ","
            << tr("Card ID") << ","
            << tr("Card Number") << ","
            << tr("Member Type") << ","
            << tr("Registration Date") << ","
            << tr("Active") << ","
            << tr("Is Admin") << ","
            << tr("Birthdate") << ","
            << tr("Address") << ","
            << tr("Zipcode") << ","
            << tr("Town") << ","
            << tr("State") << ","
            << tr("Phone") << ","
            << tr("Phone 2") << ","
            << tr("Email") << ","
            << tr("Banc Account") << ","
            << tr("Postal Send") << ","
            << tr("Notes") << ","
            << tr("Balance") << ","
            << endl;

        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            QString regDateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pMemberPtr->m_regDate.toLocalTime(), QLocale::NarrowFormat);
            QString birthDateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pMemberPtr->m_birthdate, QLocale::NarrowFormat);
            QString cleanAddress = QString("\"%1\"").arg(pMemberPtr->m_address.replace('"', '\''));
            QString cleanNotes = QString("\"%1\"").arg(pMemberPtr->m_notes.replace('"', '\'').simplified());
            QString memberType = GetStringFromMemberType(pMemberPtr->m_memberType);
            out << pMemberPtr->m_username << ", "
                << pMemberPtr->m_name << ", "
                << pMemberPtr->m_surname1 << ", "
                << pMemberPtr->m_surname2 << ", "
                << pMemberPtr->m_idCard << ", "
                << pMemberPtr->m_cardNumber << ", "
                << memberType << ", "
                << regDateLocalized << ", "
                << pMemberPtr->m_active << ", "
                << pMemberPtr->m_isAdmin << ", "
                << birthDateLocalized << ", "
                << cleanAddress << ", "
                << pMemberPtr->m_zipCode << ", "
                << pMemberPtr->m_town << ", "
                << pMemberPtr->m_state << ", "
                << pMemberPtr->m_phone << ", "
                << pMemberPtr->m_phone2 << ", "
                << pMemberPtr->m_email << ", "
                << pMemberPtr->m_bank_account << ", "
                << pMemberPtr->m_postalSend << ", "
                << cleanNotes << ", "
                << QString("%1").arg(pMemberPtr->m_balance, 0, 'f', 2)
                << endl;
        }
        f.close();
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Successfully exported. Filename: %1").arg(filename), [](){});
        // nothing should be added here
    }
    //
    void MemberListView::on_filterPostalUsersCheckBox_clicked()
    {
        updateResults();
    }
    //
    void MemberListView::on_printPostalMembersPushButton_clicked()
    {
        // get post activated members
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getMemberList(true, 0, 1000000);
        if (pMemberListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (pMemberListResultPtr->m_list->size() == 0) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("There are no users with postsend activated"), [](){});
            return;
        }
        // print post activated member list
        GuiUtils::printPostalMembers(pMemberListResultPtr->m_list);
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("successfull"), [](){});
        // nothing should be added here
    }
    //
    void MemberListView::on_prevPagePushButton_clicked()
    {
        Uint32 currentPage = this->ui->pageNumberSpinBox->value();
        this->ui->pageNumberSpinBox->setValue(currentPage-1);
    }
    //
    void MemberListView::on_nextPagePushButton_clicked()
    {
        Uint32 currentPage = this->ui->pageNumberSpinBox->value();
        this->ui->pageNumberSpinBox->setValue(currentPage+1);
    }
    //
    void MemberListView::on_prev10PagePushButton_clicked()
    {
        Uint32 currentPage = this->ui->pageNumberSpinBox->value();
        this->ui->pageNumberSpinBox->setValue(currentPage-10);
    }
    //
    void MemberListView::on_next10PagePushButton_clicked()
    {
        Uint32 currentPage = this->ui->pageNumberSpinBox->value();
        this->ui->pageNumberSpinBox->setValue(currentPage+10);
    }
    void MemberListView::on_pageNumberSpinBox_valueChanged(int page)
    {
        UNUSEDPARAMETER(page);
        updateResults();
    }
}

