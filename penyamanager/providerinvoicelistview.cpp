//

#include <QDebug>
#include "guiutils.h"
#include "singletons.h"
#include "providerinvoicelistview.h"
#include "ui_providerinvoicelistview.h"

namespace PenyaManager {
    //
    ProviderInvoiceListView::ProviderInvoiceListView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::ProviderInvoiceListView),
        m_currentPage(0),
        m_firstTime(true)
    {
        ui->setupUi(this);
        initializeTable();
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
        headers.append(tr("provider ID"));
        this->ui->invoicesTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void ProviderInvoiceListView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void ProviderInvoiceListView::initializeTable()
    {
        // table
        this->ui->invoicesTableWidget->setColumnCount(4);
        translateTable();
        this->ui->invoicesTableWidget->setColumnWidth(0, 200);
        this->ui->invoicesTableWidget->setColumnWidth(1, 100);
        this->ui->invoicesTableWidget->setColumnWidth(2, 150);
        this->ui->invoicesTableWidget->setColumnWidth(3, 150);
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

        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();

        Int32 idx = 0;
        // first element: No Provider
        this->ui->providerComboBox->insertItem(idx, "No Provider", -1);
        idx++;
        // providers
        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
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
        ProviderInvoiceListPtr pProviderInvoiceList;
        ProviderInvoiceListStatsPtr pProviderInvoiceListStats;
        Int32 providerId = this->ui->providerComboBox->currentData().toInt();
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        if (providerId >= 0) {
            pProviderInvoiceList = Singletons::m_pDAO->getProviderInvoiceListByProviderId(providerId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pProviderInvoiceListStats = Singletons::m_pDAO->getProviderInvoiceListByProviderIdStats(providerId, fromDate, toDate);
        } else {
            pProviderInvoiceList = Singletons::m_pDAO->getProviderInvoiceList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pProviderInvoiceListStats = Singletons::m_pDAO->getProviderInvoiceListStats(fromDate, toDate);
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pProviderInvoiceListStats->m_totalNumInvoices/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalInvoicesValueLabel->setText(QString::number(pProviderInvoiceListStats->m_totalNumInvoices));
        this->ui->totalCostValueLabel->setText(tr("%1 €").arg(pProviderInvoiceListStats->m_totalAmount));
        // fill dates used for query
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_translationManager.getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillInvoiceList(pProviderInvoiceList);
    }
    //
    void ProviderInvoiceListView::fillInvoiceList(ProviderInvoiceListPtr pProviderInvoiceListPtr)
    {
        // invoice table reset
        this->ui->invoicesTableWidget->clearContents();
        this->ui->invoicesTableWidget->setRowCount(pProviderInvoiceListPtr->size());
        // fill data
        Uint32 rowCount = 0;
        for (ProviderInvoiceList::iterator iter = pProviderInvoiceListPtr->begin(); iter != pProviderInvoiceListPtr->end(); ++iter)
        {
            ProviderInvoicePtr pInvoicePtr = *iter;
            this->ui->invoicesTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoicePtr->m_id));
            this->ui->invoicesTableWidget->setItem(rowCount, 1, new QTableWidgetItem(tr("%1 €").arg(pInvoicePtr->m_total)));
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_regDate, QLocale::NarrowFormat);
            this->ui->invoicesTableWidget->setItem(rowCount, 2, new QTableWidgetItem(dateLocalized));
            this->ui->invoicesTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(pInvoicePtr->m_providerid)));
            rowCount++;
        }
    }
}

