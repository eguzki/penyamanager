//

#include <QFileDialog>
#include <QTextStream>

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/constants.h>
#include <commons/singletons.h>
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

        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->fromCalendarWidget->setSelectedDate(fromIntialDate);
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
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
        this->ui->fromCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
        this->ui->toCalendarWidget->setLocale(Singletons::m_pTranslationManager->getLocale());
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
            this->ui->productTableWidget->setItem(rowCount, 1, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItem->m_productnameEus, pInvoiceProductItem->m_productnameEs)));
            this->ui->productTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(pInvoiceProductItem->m_count)));
            // pricePerUnit is already sum of all invoices grouped by product item. Different invoices may have same product with different prices.
            this->ui->productTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItem->m_pricePerUnit, 0, 'f', 2)));
            rowCount++;
        }
    }
    //
    void ProductExpensesView::updateResults()
    {
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr;
        InvoiceProductItemCounterStatsResultPtr pInvoiceProductItemCounterStatsResultPtr;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);

        QString usernameStr = this->ui->memberIdLineEdit->text().trimmed();
        if (usernameStr.isEmpty()) {
            this->ui->memberIdLineEdit->clear();
            pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getProductExpensesList(fromDate, toDate, m_currentPage, Constants::kAdminInvoiceListPageCount);
            if (pInvoiceProductItemListResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
            pInvoiceProductItemCounterStatsResultPtr = Singletons::m_pDAO->getProductExpensesListStats(fromDate, toDate);
            if (pInvoiceProductItemCounterStatsResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        } else {
            bool ok;
            Int32 memberUsername = usernameStr.toInt(&ok);
            if (!ok) {
                this->ui->memberIdLineEdit->clear();
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Username not valid"), [](){});
                return;
            } else {
                MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(memberUsername);
                if (pMemberResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                if (!pMemberResultPtr->m_member) {
                    // User could not be found
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Username not found"), [](){});
                    return;
                }
                pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getProductExpensesListByMemberId(pMemberResultPtr->m_member->m_id, fromDate, toDate, m_currentPage, Constants::kAdminInvoiceListPageCount);
                if (pInvoiceProductItemListResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                pInvoiceProductItemCounterStatsResultPtr = Singletons::m_pDAO->getProductExpensesListByMemberIdStats(pMemberResultPtr->m_member->m_id, fromDate, toDate);
                if (pInvoiceProductItemCounterStatsResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
            }
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)pInvoiceProductItemCounterStatsResultPtr->m_stats->m_totalProducts/Constants::kAdminInvoiceListPageCount);
        this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
        this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
        // fill page view
        this->ui->pageInfoLabel->setText(tr("page %1 out of %2").arg(m_currentPage+1).arg(numPages));
        // fill total stats view
        this->ui->totalProductsValueLabel->setText(QString::number(pInvoiceProductItemCounterStatsResultPtr->m_stats->m_totalProducts));
        // fill dates used for query
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(fromDate, QLocale::NarrowFormat);
        this->ui->fromDateResultValueLabel->setText(dateLocalized);
        dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(toDate.addDays(-1), QLocale::NarrowFormat);
        this->ui->toDateResultValueLabel->setText(dateLocalized);
        // fill invoice list
        fillProductList(pInvoiceProductItemListResultPtr->m_list);
    }
    //
    void ProductExpensesView::on_csvPushButton_clicked()
    {
        // open file dialog
        // start in home dir
        Singletons::m_pDialogManager->getOpenFileName(this, tr("Open File..."), QDir::homePath(),
                tr("CSV Files (*.csv)"), QFileDialog::AnyFile,
                std::bind(&ProductExpensesView::onProductExpensesCsvSelected, this, _1)
                );
        // nothing should be added here
    }
    //
    void ProductExpensesView::onProductExpensesCsvSelected(const QString &fn)
    {
        if (fn.isNull()){
            return;
        }

        QString filename = Utils::addSuffix(fn, "csv");
        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Error opening %1").arg(filename), [](){});
            return;
        }

        // fetch data
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr;
        InvoiceProductItemStatsResultPtr pInvoiceProductItemStatsResultPtr;
        QDate fromDate = this->ui->fromCalendarWidget->selectedDate();
        // add one day to "toDate" to be included
        QDate toDate = this->ui->toCalendarWidget->selectedDate().addDays(1);
        QString usernameStr = this->ui->memberIdLineEdit->text().trimmed();
        if (usernameStr.isEmpty()) {
            this->ui->memberIdLineEdit->clear();
            pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getProductExpensesList(fromDate, toDate, m_currentPage, Constants::kAdminInvoiceListPageCount);
            if (pInvoiceProductItemListResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        } else {
            bool ok;
            Int32 memberUsername = usernameStr.toInt(&ok);
            if (!ok) {
                this->ui->memberIdLineEdit->clear();
                Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Username not valid"), [](){});
                return;
            } else {
                MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberByUsername(memberUsername);
                if (pMemberResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
                if (!pMemberResultPtr->m_member)
                {
                    // User could not be found
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Username not found"), [](){});
                    return;
                }
                pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getProductExpensesListByMemberId(pMemberResultPtr->m_member->m_id, fromDate, toDate, m_currentPage, Constants::kAdminInvoiceListPageCount);
                if (pInvoiceProductItemListResultPtr->m_error) {
                    Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                    return;
                }
            }
        }

        // save to file
        QTextStream out(&f);
        out.setCodec("UTF-8");

        // header
        out << tr("product ID") << ", " << tr("name") << ", " << tr("count") << endl;
        // iterate over results
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItem = *iter;
            out << pInvoiceProductItem->m_productId << ", " << Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItem->m_productnameEus, pInvoiceProductItem->m_productnameEs) << ", " << pInvoiceProductItem->m_count << endl;
        }
        f.close();
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Successfully exported. Filename: %1").arg(filename), [](){});
        // nothing should be added here
    }
}

