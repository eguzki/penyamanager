//

#include "utils.h"
#include "singletons.h"
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
    void StockManagementWindow::initializeTable()
    {
        // table
        this->ui->productsTableWidget->setColumnCount(8);
        // invoice table Header
        QStringList headers;
        headers.append("Image");
        headers.append("Ref#");
        headers.append("name");
        headers.append("active");
        headers.append("registration date");
        headers.append("price/unit");
        headers.append("familyId");
        headers.append("providerId");

        this->ui->productsTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->productsTableWidget->setColumnWidth(0, Constants::kFamilyImageWidth);
        this->ui->productsTableWidget->setColumnWidth(1, 100);
        this->ui->productsTableWidget->setColumnWidth(2, 300);
        this->ui->productsTableWidget->setColumnWidth(3, 50);
        this->ui->productsTableWidget->setColumnWidth(4, 200);
        this->ui->productsTableWidget->setColumnWidth(5, 100);
        this->ui->productsTableWidget->setColumnWidth(6, 100);
        this->ui->productsTableWidget->setColumnWidth(7, 100);
    }
    //
    void StockManagementWindow::init()
    {
        //
        // Load initial list
        //
        updateResults();

        //
        // Show
        //

        show();
    }
    //
    void StockManagementWindow::on_csvPushButton_clicked()
    {

    }
    //
    void StockManagementWindow::on_printPushButton_clicked()
    {

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
        ProductItemListPtr pfListPtr = Singletons::m_pDAO->getProductsList(m_currentPage, Constants::kProductListPageCount);
        ProductListStatsPtr pProductListStats = Singletons::m_pDAO->getProductsListStats();
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pProductListStats->m_totalNumProducts/Constants::kProductListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalProductsValueLabel->setText(QString::number(pProductListStats->m_totalNumProducts));
        // fill product list
        fillProductList(pfListPtr);
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
            QString imagePath = QDir(Constants::kImageRootPath).filePath(pProductPtr->m_imagePath);
            QPixmap productItemPixmap = Utils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImage->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->productsTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->productsTableWidget->setItem(rowCount, 0, productImage);
            //  product id
            this->ui->productsTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(pProductPtr->m_id)));
            //  product name
            this->ui->productsTableWidget->setItem(rowCount, 2, new QTableWidgetItem(pProductPtr->m_name));
            //  product active status
            this->ui->productsTableWidget->setItem(rowCount, 3, new QTableWidgetItem((pProductPtr->m_active)?(QString::number(1)):(QString::number(1))));
            //  product reg date
            this->ui->productsTableWidget->setItem(rowCount, 4, new QTableWidgetItem(pProductPtr->m_regDate.toString()));
            //  product price
            this->ui->productsTableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(pProductPtr->m_price)));
            //  product familyid
            this->ui->productsTableWidget->setItem(rowCount, 6, new QTableWidgetItem(QString::number(pProductPtr->m_familyId)));
            //  product productid
            this->ui->productsTableWidget->setItem(rowCount, 7, new QTableWidgetItem(QString::number(pProductPtr->m_providerId)));
            rowCount++;
        }
    }
}
