//

#include "utils.h"
#include "singletons.h"
#include "memberlistview.h"
#include "ui_memberlistview.h"

namespace PenyaManager {
    //
    MemberListView::MemberListView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::MemberListView),
        m_switchCentralWidgetCallback(callback),
        m_currentPage(0)
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
        this->ui->memberTableWidget->setColumnCount(6);

        // invoice table Header
        QStringList headers;
        headers.append("Image");
        headers.append("Surnames");
        headers.append("Name");
        headers.append("MemberID");
        headers.append("Email");
        headers.append("Active");
        Uint32 column = 0;
        this->ui->memberTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->memberTableWidget->setColumnWidth(column++, Constants::kFamilyImageWidth);
        this->ui->memberTableWidget->setColumnWidth(column++, 300);
        this->ui->memberTableWidget->setColumnWidth(column++, 150);
        this->ui->memberTableWidget->setColumnWidth(column++, 100);
        this->ui->memberTableWidget->setColumnWidth(column++, 300);
    }
    //
    void MemberListView::init()
    {
        //
        // Loading User profile
        //
        m_currentPage = 0;
        updateResults();

        //
        // Show
        //

        show();
    }
    //
    void MemberListView::updateResults()
    {
        MemberListPtr pMemberListPtr;
        MemberListStatsPtr pMemberListStatsPtr;

        pMemberListPtr = Singletons::m_pDAO->getMemberList(m_currentPage, Constants::kInvoiceListPageCount);
        pMemberListStatsPtr = Singletons::m_pDAO->getMemberListStats();
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pMemberListStatsPtr->m_totalMembers/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalMembersValueLabel->setText(QString::number(pMemberListStatsPtr->m_totalMembers));
        // fill invoice list
        fillMemberList(pMemberListPtr);
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
    void MemberListView::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void MemberListView::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void MemberListView::fillMemberList(const MemberListPtr &pMemberListPtr)
    {
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
            QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
            QPixmap productItemPixmap = Utils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            memberImageWidget->setData(Qt::DecorationRole, productItemPixmap);
            Uint32 column = 0;
            this->ui->memberTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->memberTableWidget->setItem(rowCount, column++, memberImageWidget);
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pMemberPtr->m_surname));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pMemberPtr->m_name));
            this->ui->memberTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pMemberPtr->m_id)));
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
            qDebug() << "[ERROR] memberID not found and should be in the map";
            return;
        }
        Int32 memberId = rowMap->second;
        // use static global variable to pass argument
        Singletons::m_currentMemberId = memberId;

        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kMemberViewKey);
    }
}

