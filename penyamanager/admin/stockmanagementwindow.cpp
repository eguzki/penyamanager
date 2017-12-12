//

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "stockmanagementwindow.h"
#include "ui_stockmanagementwindow.h"

namespace PenyaManager {
    //
    StockManagementWindow::StockManagementWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::StockManagementWindow),
        m_currentPage(0)
    {
        ui->setupUi(this);
        initializeTable();
    }
    //
    StockManagementWindow::~StockManagementWindow()
    {
        delete ui;
    }
    //
    void StockManagementWindow::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("Image"));
        headers.append(tr("name"));
        headers.append(tr("active"));
        headers.append(tr("registration date"));
        headers.append(tr("price/unit"));
        headers.append(tr("family"));
        headers.append(tr("provider"));
        headers.append(tr("# units"));
        this->ui->productsTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void StockManagementWindow::initializeTable()
    {
        // table
        this->ui->productsTableWidget->setColumnCount(8);
        translateTable();

        Uint32 column = 0;
        this->ui->productsTableWidget->setColumnWidth(column++, Constants::kFamilyImageWidth);
        this->ui->productsTableWidget->setColumnWidth(column++, 200);
        this->ui->productsTableWidget->setColumnWidth(column++, 50);
        this->ui->productsTableWidget->setColumnWidth(column++, 150);
        this->ui->productsTableWidget->setColumnWidth(column++, 100);
        this->ui->productsTableWidget->setColumnWidth(column++, 80);
        this->ui->productsTableWidget->setColumnWidth(column++, 100);
        this->ui->productsTableWidget->setColumnWidth(column++, 80);
    }
    //
    void StockManagementWindow::init()
    {
        //
        // Load initial list
        //
        updateResults();
    }
    //
    void StockManagementWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void StockManagementWindow::on_csvPushButton_clicked()
    {
        // Assume product list is not empty (buttons should be disabled)
        QString filename = QFileDialog::getSaveFileName(this, tr("Export CSV"));

        if (filename.isNull()){
            return;
        }

        // fetch data
        StockProductItemListResultPtr pStockProductItemListResultPtr = Singletons::m_pDAO->getAllStockProductsList();
        if (pStockProductItemListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            QMessageBox::warning(this, "Unable to save file", "Error opening " + filename);
            return;
        }

        QTextStream out(&f);
        out.setCodec("UTF-8");
        // print header
        out << tr("name") << "," << tr("stock") << endl;

        for (StockProductItemList::iterator iter = pStockProductItemListResultPtr->m_list->begin(); iter != pStockProductItemListResultPtr->m_list->end(); ++iter)
        {
            StockProductItemPtr pStockProductItemPtr = *iter;
            out << pStockProductItemPtr->m_name << ", " << QString::number(pStockProductItemPtr->m_stock) << endl;
        }
        f.close();
        QMessageBox::information(this, tr("Export CSV"), tr("Successfully exported. Filename: %1").arg(filename));
    }
    //
    void StockManagementWindow::on_prevPagePushButton_clicked()
    {
        m_currentPage--;
        updateResults();
    }
    //
    void StockManagementWindow::on_nextPagePushButton_clicked()
    {
        m_currentPage++;
        updateResults();
    }
    //
    void StockManagementWindow::updateResults()
    {
        StockProductItemListResultPtr pStockProductItemListResultPtr = Singletons::m_pDAO->getStockProductsList(m_currentPage, Constants::kAdminProductListPageCount);
        if (pStockProductItemListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        ProductListStatsResultPtr pProductListStatsResultPtr = Singletons::m_pDAO->getProductsListStats();
        if (pProductListStatsResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pProductListStatsResultPtr->m_stats->m_totalNumProducts/Constants::kAdminProductListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
            // fill total stats view
            this->ui->totalProductsValueLabel->setText(QString::number(pProductListStatsResultPtr->m_stats->m_totalNumProducts));
        }

        // fill product list
        fillProductList(pStockProductItemListResultPtr->m_list);
        //
        this->ui->csvPushButton->setEnabled(pStockProductItemListResultPtr->m_list->size() > 0);
    }
    //
    void StockManagementWindow::fillProductList(const StockProductItemListPtr &pStockProductItemListPtr)
    {
        // invoice table reset
        this->ui->productsTableWidget->clearContents();
        // num rows
        this->ui->productsTableWidget->setRowCount(pStockProductItemListPtr->size());
        // fill data
        Uint32 rowCount = 0;
        for (StockProductItemList::iterator iter = pStockProductItemListPtr->begin(); iter != pStockProductItemListPtr->end(); ++iter)
        {
            StockProductItemPtr pStockProductItemPtr = *iter;
            Uint32 column = 0;
            // image
            QTableWidgetItem *productImage = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pStockProductItemPtr->m_imagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImage->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->productsTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->productsTableWidget->setItem(rowCount, column++, productImage);
            //  product name
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pStockProductItemPtr->m_name));
            //  product active status
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem((pStockProductItemPtr->m_active)?(QString::number(1)):(QString::number(0))));
            //  product reg date
            QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(pStockProductItemPtr->m_regDate, QLocale::NarrowFormat);
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(dateLocalized));
            //  product price
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pStockProductItemPtr->m_price)));
            //  product familyid
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pStockProductItemPtr->m_familyName));
            //  product productid
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pStockProductItemPtr->m_providerName));
            //  product stock
            this->ui->productsTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pStockProductItemPtr->m_stock)));
            rowCount++;
        }
    }
}

