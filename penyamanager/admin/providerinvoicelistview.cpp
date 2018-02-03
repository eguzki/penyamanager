//

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "providerinvoicelistview.h"
#include "ui_providerinvoicelistview.h"

namespace PenyaManager {
    //
    ProviderInvoiceListView::ProviderInvoiceListView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::ProviderInvoiceListView),
        m_switchCentralWidgetCallback(callback),
        m_currentPage(0),
        m_firstTime(true)
    {
        ui->setupUi(this);
        initializeTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    ProviderInvoiceListView::~ProviderInvoiceListView()
    {
        delete ui;
    }
    //
    void ProviderInvoiceListView::init()
    {
        if (this->m_firstTime) {
            initialize();
            updateResults();
        }
    }
    //
    void ProviderInvoiceListView::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("invoice ID"));
        headers.append(tr("Total"));
        headers.append(tr("Date"));
        headers.append(tr("Provider"));
        this->ui->invoicesTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void ProviderInvoiceListView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
    }
    //
    void ProviderInvoiceListView::initializeTable()
    {
        // table
        this->ui->invoicesTableWidget->setColumnCount(4);
        translateTable();
        Uint32 column = 0;
        this->ui->invoicesTableWidget->setColumnWidth(column++, 200);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 100);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 150);
        this->ui->invoicesTableWidget->setColumnWidth(column++, 150);
    }
    //
    void ProviderInvoiceListView::on_searchPushButton_clicked()
    {
        // when user pushes search, afterwards, on init() results are not updated
        this->m_firstTime = false;
        m_currentPage = 0;
        updateResults();
    }
    //
    void ProviderInvoiceListView::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void ProviderInvoiceListView::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void ProviderInvoiceListView::initialize()
    {
        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        this->ui->fromDateResultValueLabel->clear();
        this->ui->toDateResultValueLabel->clear();
        this->ui->providerComboBox->clear();
        this->ui->invoicesTableWidget->clearContents();

        ProviderListResultPtr pProviderListResultPtr = Singletons::m_pDAO->getProviderList();
        if (pProviderListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Int32 idx = 0;
        // first element: No Provider
        this->ui->providerComboBox->insertItem(idx, tr("All providers"), -1);
        idx++;
        // providers
        for (auto iter = pProviderListResultPtr->m_list->begin(); iter != pProviderListResultPtr->m_list->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = GuiUtils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(idx, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            idx++;
        }
        this->ui->providerComboBox->setCurrentIndex(0);
    }
    //
    void ProviderInvoiceListView::updateResults()
    {
        ProviderInvoiceListResultPtr pProviderInvoiceListResult;
        ProviderInvoiceListStatsResultPtr pProviderInvoiceListStatsResult;
        Int32 providerId = this->ui->providerComboBox->currentData().toInt();
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        if (providerId >= 0) {
            pProviderInvoiceListResult = Singletons::m_pDAO->getProviderInvoiceListByProviderId(providerId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            if (pProviderInvoiceListResult->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            pProviderInvoiceListStatsResult = Singletons::m_pDAO->getProviderInvoiceListByProviderIdStats(providerId, fromDate, toDate);
            if (pProviderInvoiceListStatsResult->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        } else {
            pProviderInvoiceListResult = Singletons::m_pDAO->getProviderInvoiceList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            if (pProviderInvoiceListResult->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            pProviderInvoiceListStatsResult = Singletons::m_pDAO->getProviderInvoiceListStats(fromDate, toDate);
            if (pProviderInvoiceListStatsResult->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pProviderInvoiceListStatsResult->m_stats->m_totalNumInvoices/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pProviderInvoiceListStatsResult->m_stats->m_totalNumInvoices));
        this->ui->totalCostValueLabel->setText(QString("%1 €").arg(pProviderInvoiceListStatsResult->m_stats->m_totalAmount, 0, 'f', 2));
        // fill dates used for query
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillInvoiceList(pProviderInvoiceListResult->m_list);
    }
    //
    void ProviderInvoiceListView::fillInvoiceList(ProviderInvoiceListPtr pProviderInvoiceListPtr)
    {
        // invoice table reset
        this->ui->invoicesTableWidget->setRowCount(pProviderInvoiceListPtr->size());
        this->ui->invoicesTableWidget->clearContents();
        // internal data structure reset
        this->m_rowProviderInvoiceIdMap.clear();
        // fill data
        Uint32 rowCount = 0;
        for (ProviderInvoiceList::iterator iter = pProviderInvoiceListPtr->begin(); iter != pProviderInvoiceListPtr->end(); ++iter)
        {
            ProviderInvoicePtr pInvoicePtr = *iter;
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoicePtr->m_id));
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoicePtr->m_total, 0, 'f', 2)));
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pInvoicePtr->m_regDate, QLocale::NarrowFormat);
            this->ui->invoicesTableWidget->setItem(rowCount, 2, new QTableWidgetItem(dateLocalized));
            this->ui->invoicesTableWidget->setItem(rowCount, 3, new QTableWidgetItem(pInvoicePtr->m_providerName));
            this->m_rowProviderInvoiceIdMap[rowCount] = pInvoicePtr->m_id;
            rowCount++;
        }
    }
    //
    void ProviderInvoiceListView::on_invoicesTableWidget_cellDoubleClicked(int row, int column)
    {
        UNUSEDPARAMETER(column);
        auto rowMap = m_rowProviderInvoiceIdMap.find(row);
        if (rowMap == m_rowProviderInvoiceIdMap.end()) {
            //this should never happen
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kProvider,
                    QString("providerinvoicelistview provider invoice Id not found and should be in the map"));
            return;
        }
        QString providerInvoiceId = rowMap->second;
        // use static global variable to pass argument
        Singletons::m_currentProviderInvoiceId = providerInvoiceId;

        // call invoice details window throw adminmainwindow
        m_switchCentralWidgetCallback(WindowKey::kProviderInvoiceViewKey);
    }
}

