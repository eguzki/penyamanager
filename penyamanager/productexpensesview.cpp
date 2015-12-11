//

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "guiutils.h"
#include "constants.h"
#include "singletons.h"
#include "productexpensesview.h"
#include "ui_productexpensesview.h"

namespace PenyaManager {
    //
    ProductExpensesView::ProductExpensesView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::ProductExpensesView),
        m_currentPage(0),
        m_firstTime(true)
    {
        ui->setupUi(this);

        initializeTable();

        // initialize calendar inital values
        QDate toInitialDate = QDate::currentDate();
        // from 30 days before
        QDate fromIntialDate = toInitialDate.addDays(-30);

        this->ui->fromCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
        this->ui->toCalendarWidget->setSelectedDate(toInitialDate);

        this->ui->fromDateResultValueLabel->clear();
        this->ui->toDateResultValueLabel->clear();
    }
    //
    ProductExpensesView::~ProductExpensesView()
    {
        delete ui;
    }
    //
    void ProductExpensesView::init()
    {
        if (this->m_firstTime) {
            updateResults();
        }
    }
    //
    void ProductExpensesView::translateTable()
    {
        QStringList headers;
        headers.append(tr("Icon"));
        headers.append(tr("Name"));
        headers.append(tr("Count"));
        headers.append(tr("Total"));
        this->ui->productTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void ProductExpensesView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
        this->ui->fromCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_translationManager.getLocale());
    }
    //
    void ProductExpensesView::initializeTable()
    {
        // table
        this->ui->productTableWidget->setColumnCount(4);
        translateTable();
        // invoice table Header
        this->ui->productTableWidget->setColumnWidth(0, Constants::kFamilyImageWidth);
        this->ui->productTableWidget->setColumnWidth(1, 300);
        this->ui->productTableWidget->setColumnWidth(2, 100);
        this->ui->productTableWidget->setColumnWidth(3, 100);
    }
    //
    void ProductExpensesView::on_clearPushButton_clicked()
    {
        this->ui->memberIdLineEdit->clear();
    }
    //
    void ProductExpensesView::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void ProductExpensesView::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void ProductExpensesView::on_searchPushButton_clicked()
    {
        // when user pushes search, afterwards, on init() results are not updated
        this->m_firstTime = false;
        m_currentPage = 0;
        updateResults();
    }
    //
    void ProductExpensesView::fillProductList(const InvoiceProductItemListPtr &pInvoiceProductItemListPtr)
    {
        if (pInvoiceProductItemListPtr->size() > 0) {
            this->ui->csvPushButton->setEnabled(true);
            this->ui->printPushButton->setEnabled(true);
        } else {
            this->ui->csvPushButton->setEnabled(false);
            this->ui->printPushButton->setEnabled(false);
        }
        // num rows
        this->ui->productTableWidget->setRowCount(pInvoiceProductItemListPtr->size());
        // invoice table reset
        this->ui->productTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItem = *iter;
            // image
            QTableWidgetItem *productImage = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pInvoiceProductItem->m_imagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImage->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->productTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->productTableWidget->setItem(rowCount, 0, productImage);
            this->ui->productTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pInvoiceProductItem->m_productname));
            this->ui->productTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pInvoiceProductItem->m_count)));
            this->ui->productTableWidget->setItem(rowCount, 3, new QTableWidgetItem(tr("%1 €").arg(pInvoiceProductItem->m_count * pInvoiceProductItem->m_priceperunit)));
            rowCount++;
        }
    }
    //
    void ProductExpensesView::updateResults()
    {
        InvoiceProductItemListPtr pInvoiceProductItemListPtr;
        InvoiceProductItemStatsPtr pInvoiceProductItemStatsPtr;
        bool ok;
        Int32 memberId = this->ui->memberIdLineEdit->text().toInt(&ok);
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        if (!ok) {
            this->ui->memberIdLineEdit->clear();
            pInvoiceProductItemListPtr = Singletons::m_pDAO->getProductExpensesList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pInvoiceProductItemStatsPtr = Singletons::m_pDAO->getProductExpensesListStats(fromDate, toDate);
        } else {
            pInvoiceProductItemListPtr = Singletons::m_pDAO->getProductExpensesListByMemberId(memberId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
            pInvoiceProductItemStatsPtr = Singletons::m_pDAO->getProductExpensesListByMemberIdStats(memberId, fromDate, toDate);
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceProductItemStatsPtr->m_totalProducts/Constants::kInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalProductsValueLabel->setText(QString::number(pInvoiceProductItemStatsPtr->m_totalProducts));
        // fill dates used for query
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_translationManager.getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillProductList(pInvoiceProductItemListPtr);
    }
    //
    void ProductExpensesView::on_csvPushButton_clicked()
    {
        // Assume slow payers list is not empty (buttons should be disabled)
        QString filename = QFileDialog::getSaveFileName(this, tr("Export CSV"));

        if (filename.isNull()){
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            QMessageBox::warning(this, "Unable to save file", "Error opening " + filename);
            return;
        }
        QTextStream out(&f);

        // fetch data
        InvoiceProductItemListPtr pInvoiceProductItemListPtr;
        InvoiceProductItemStatsPtr pInvoiceProductItemStatsPtr;
        bool ok;
        Int32 memberId = this->ui->memberIdLineEdit->text().toInt(&ok);
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        if (!ok) {
            this->ui->memberIdLineEdit->clear();
            pInvoiceProductItemListPtr = Singletons::m_pDAO->getProductExpensesList(fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
        } else {
            pInvoiceProductItemListPtr = Singletons::m_pDAO->getProductExpensesListByMemberId(memberId, fromDate, toDate, m_currentPage, Constants::kInvoiceListPageCount);
        }

        // header
        out << tr("product ID") << ", " << tr("name") << ", " << tr("count") << "\n";
        // iterate over results
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItem = *iter;
            out << pInvoiceProductItem->m_productId << ", " << pInvoiceProductItem->m_productname << ", " << pInvoiceProductItem->m_count << "\n";
        }
        f.close();
    }
    //
    void ProductExpensesView::on_printPushButton_clicked()
    {
        // TODO
    }
}


