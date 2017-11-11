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
        headers.append(tr("Ref#"));
        headers.append(tr("name"));
        headers.append(tr("active"));
        headers.append(tr("registration date"));
        headers.append(tr("price/unit"));
        headers.append(tr("familyId"));
        headers.append(tr("providerId"));
        headers.append(tr("# units"));
        this->ui->productsTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void StockManagementWindow::initializeTable()
    {
        // table
        this->ui->productsTableWidget->setColumnCount(9);
        translateTable();
        this->ui->productsTableWidget->setColumnWidth(0, Constants::kFamilyImageWidth);
        this->ui->productsTableWidget->setColumnWidth(1, 100);
        this->ui->productsTableWidget->setColumnWidth(2, 300);
        this->ui->productsTableWidget->setColumnWidth(3, 50);
        this->ui->productsTableWidget->setColumnWidth(4, 200);
        this->ui->productsTableWidget->setColumnWidth(5, 100);
        this->ui->productsTableWidget->setColumnWidth(6, 100);
        this->ui->productsTableWidget->setColumnWidth(7, 100);
        this->ui->productsTableWidget->setColumnWidth(8, 100);
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
        ProductItemListResultPtr pfListPtr = Singletons::m_pDAO->getProductsList(0, 100000);
        if (pfListPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            QMessageBox::warning(this, "Unable to save file", "Error opening " + filename);
            return;
        }

        QTextStream out(&f);
        // print header
        out << tr("name") << "," << tr("stock") << endl;

        for (ProductItemList::iterator iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter)
        {
            ProductItemPtr pProductPtr = *iter;
            out << pProductPtr->m_name << ", " << QString::number(pProductPtr->m_stock) << endl;
        }
        f.close();
        QMessageBox::information(this, tr("CSV export"), tr("Successfully exported. Filename: %1").arg(filename));
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
        ProductItemListResultPtr pfListPtr = Singletons::m_pDAO->getProductsList(m_currentPage, Constants::kProductListPageCount);
        if (pfListPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        ProductListStatsResultPtr pProductListStatsResultPtr = Singletons::m_pDAO->getProductsListStats();
        if (pProductListStatsResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact adminstrator"));
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pProductListStatsResultPtr->m_stats->m_totalNumProducts/Constants::kProductListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalProductsValueLabel->setText(QString::number(pProductListStatsResultPtr->m_stats->m_totalNumProducts));
        // fill product list
        fillProductList(pfListPtr->m_list);
        //
        this->ui->csvPushButton->setEnabled(pfListPtr->m_list->size() > 0);
    }
    //
    void StockManagementWindow::fillProductList(const ProductItemListPtr &pProductItemListPtr)
    {
        // num rows
        this->ui->productsTableWidget->setRowCount(pProductItemListPtr->size());
        // invoice table reset
        this->ui->productsTableWidget->clearContents();
        // fill data
        Uint32 rowCount = 0;
        for (ProductItemList::iterator iter = pProductItemListPtr->begin(); iter != pProductItemListPtr->end(); ++iter)
        {
            ProductItemPtr pProductPtr = *iter;
            // image
            QTableWidgetItem *productImage = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductPtr->m_imagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImage->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->productsTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->productsTableWidget->setItem(rowCount, 0, productImage);
            //  product id
            this->ui->productsTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(pProductPtr->m_id)));
            //  product name
            this->ui->productsTableWidget->setItem(rowCount, 2, new QTableWidgetItem(pProductPtr->m_name));
            //  product active status
            this->ui->productsTableWidget->setItem(rowCount, 3, new QTableWidgetItem((pProductPtr->m_active)?(QString::number(1)):(QString::number(0))));
            //  product reg date
            QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pProductPtr->m_regDate, QLocale::NarrowFormat);
            this->ui->productsTableWidget->setItem(rowCount, 4, new QTableWidgetItem(dateLocalized));
            //  product price
            this->ui->productsTableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(pProductPtr->m_price)));
            //  product familyid
            this->ui->productsTableWidget->setItem(rowCount, 6, new QTableWidgetItem(QString::number(pProductPtr->m_familyId)));
            //  product productid
            this->ui->productsTableWidget->setItem(rowCount, 7, new QTableWidgetItem(QString::number(pProductPtr->m_providerId)));
            //  product stock
            this->ui->productsTableWidget->setItem(rowCount, 8, new QTableWidgetItem(QString::number(pProductPtr->m_stock)));
            rowCount++;
        }
    }
}

