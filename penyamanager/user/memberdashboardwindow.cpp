//

#include <QLabel>
#include <QDateTime>
#include <QMessageBox>
#include <QsLog.h>

#include <commons/constants.h>
#include <commons/guiutils.h>
#include <commons/singletons.h>
#include <commons/numitemdialog.h>
#include <commons/familyitemwidget.h>
#include <commons/productitemwidget.h>
#include "memberdashboardwindow.h"
#include "ui_memberdashboardwindow.h"

namespace PenyaManager {

    //
    MemberDashboardWindow::MemberDashboardWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::MemberDashboardWindow),
        m_pMemberProfileGroupBox(new MemberProfileGroupBox),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
        this->ui->topPanelWidget->layout()->addWidget(m_pMemberProfileGroupBox);
        initializeTable();
    }
    //
    MemberDashboardWindow::~MemberDashboardWindow()
    {
        m_rowProductIdMap.clear();
        delete ui;
    }
    //
    void MemberDashboardWindow::initializeTable()
    {
        this->ui->invoiceTableWidget->setColumnCount(5);
        QHeaderView* header = this->ui->invoiceTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Fixed);
        translateTable();

        Uint32 column = 0;
        this->ui->invoiceTableWidget->setColumnWidth(column++, 168);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 83);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 45);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 100);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 58);


    }
    //
    void MemberDashboardWindow::translateTable()
    {
        // table Header
        QStringList headers;
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append("#");
        headers.append(tr("total"));
        headers.append(tr("Remove"));
        this->ui->invoiceTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void MemberDashboardWindow::init()
    {
        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QLOG_ERROR() << QString("Unable to initialize Database: %1").arg(err.text());
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            qApp->exit(1);
            return;
        }

        //
        // Loading User profile
        //
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_pCurrMember->m_id);
        if (pMemberResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            QLOG_WARN() << QString("Unable to find owner by id: %1").arg(Singletons::m_pCurrMember->m_id);
            qDebug() << QString("Unable to find owner by id: %1").arg(Singletons::m_pCurrMember->m_id);
            return;
        }

        MemberPtr pCurrMemberPtr = pMemberResultPtr->m_member;
        Singletons::m_pCurrMember = pCurrMemberPtr;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);


        //
        // Loading families
        //
        ProductFamilyListResultPtr pfListPtr = Singletons::m_pDAO->getProductFamilies(true);
        if (pfListPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        this->ui->productListWidget->clear();

        fillFamilyProducts(pfListPtr->m_list);

        //
        // Loading Current Invoice (if it exists)
        //
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // pInvoicePtr could be null
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);

        //
        // check credir limit
        //
        if (pCurrMemberPtr->m_balance < -Constants::kCreditLimit)
        {
            // User has gone over credit limit. Do not allow creating invoice
            QMessageBox::warning(this, tr("Slow Payer"),
                    tr("Your current balance is over limit (%1 €): %2 €").arg(Constants::kCreditLimit, 0, 'f', 2).arg(pCurrMemberPtr->m_balance, 0, 'f', 2));
            this->ui->familyListWidget->setDisabled(true);
            this->ui->invoiceCloseButton->setDisabled(true);
        } else {
            this->ui->familyListWidget->setDisabled(false);
            this->ui->invoiceCloseButton->setDisabled(false);
        }
    }
    //
    void MemberDashboardWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void MemberDashboardWindow::createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pProductItem = new QListWidgetItem(pList);
        pProductItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pProductItem);

        // main product widget
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap productItemPixmap = GuiUtils::getImage(imagePath);
        QWidget *pProduceItemWidget = new ProductItemWidget(pList, productItemPixmap, pfPtr->m_name, pfPtr->m_price);

        // load product image
        pProductItem->setSizeHint(pProduceItemWidget->minimumSize());
        pProductItem->setFlags(Qt::ItemIsSelectable);
        //pProductItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        pList->setItemWidget(pProductItem, pProduceItemWidget);
    }

    //
    void MemberDashboardWindow::createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pFamilyItem = new QListWidgetItem(pList);
        pFamilyItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pFamilyItem);

        // main family widget
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap familyPixmap = GuiUtils::getImage(imagePath);
        QWidget *pFamilyWidget = new FamilyItemWidget(pList, familyPixmap, pfPtr->m_name);

        // load family image
        pFamilyItem->setSizeHint(pFamilyWidget->minimumSize());
        pFamilyItem->setFlags(Qt::ItemIsSelectable);
        pList->setItemWidget(pFamilyItem, pFamilyWidget);
    }
    //
    void MemberDashboardWindow::fillFamilyProducts(const ProductFamilyListPtr &pflPtr)
    {
        this->ui->familyListWidget->clear();

        for (ProductFamilyList::iterator iter = pflPtr->begin(); iter != pflPtr->end(); ++iter)
        {
            createFamilyWidget(*iter, this->ui->familyListWidget);
        }


    }

    //
    void MemberDashboardWindow::fillProductItems(Int32 familyId)
    {
        this->ui->productListWidget->clear();

        ProductItemListResultPtr pfListPtr = Singletons::m_pDAO->getProductsFromFamily(familyId, true);
        if (pfListPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        for (ProductItemList::iterator iter = pfListPtr->m_list->begin(); iter != pfListPtr->m_list->end(); ++iter) {
            createProductItemWidget(*iter, this->ui->productListWidget);
        }
    }
    void MemberDashboardWindow::on_familyListWidget_itemClicked(QListWidgetItem *item)
    {
        Int32 familyId = item->data(Constants::kIdRole).toInt();
        // highlight clicked item and un-highlight others
        this->ui->familyListWidget->setCurrentItem(item);
        // fill product of the family
        fillProductItems(familyId);
    }
    //
    void MemberDashboardWindow::fillInvoiceData(const InvoicePtr &pInvoicePtr)
    {
        if (!pInvoicePtr) {
            // clean all

            // invoice table reset
            this->ui->invoiceTableWidget->clearContents();
            this->ui->invoiceTableWidget->setRowCount(0);
            this->ui->totalDisplayLabel->setText("0 €");
            return;
        }


        // get invoice products
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        if (pInvoiceProductItemListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        // table
        this->ui->invoiceTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());

        // invoice table reset
        this->ui->invoiceTableWidget->clearContents();
        // internal data structure reset
        this->m_rowProductIdMap.clear();

        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            QTableWidgetItem *item = new QTableWidgetItem(pInvoiceProductItemPtr->m_productname);
            item->setData(Qt::TextAlignmentRole, Qt::AlignLeft);
            this->ui->invoiceTableWidget->setItem(rowCount, 0, item);
            item = new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2));
            item->setData(Qt::TextAlignmentRole, Qt::AlignRight);
            this->ui->invoiceTableWidget->setItem(rowCount, 1, item);
            item = new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count));
            item->setData(Qt::TextAlignmentRole, Qt::AlignRight);
            this->ui->invoiceTableWidget->setItem(rowCount, 2, item);
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            item = new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2));
            item->setData(Qt::TextAlignmentRole, Qt::AlignRight);
            this->ui->invoiceTableWidget->setItem(rowCount, 3, item);
            totalInvoice += totalPrice;
            this->m_rowProductIdMap[rowCount] = pInvoiceProductItemPtr->m_productId;
            // show remove action
            QPushButton *pRemoveButton = new QPushButton("", this->ui->invoiceTableWidget);
            QPixmap pixmap(":images/trash.png");
            QIcon buttonIcon(pixmap);
            pRemoveButton->setIcon(buttonIcon);
            this->connect(pRemoveButton, &QPushButton::clicked, std::bind(&MemberDashboardWindow::on_productRemoveButton_clicked, this,
                  pInvoiceProductItemPtr->m_productId,
                  pInvoiceProductItemPtr->m_productname,
                  totalPrice));
            this->ui->invoiceTableWidget->setCellWidget(rowCount, 4, pRemoveButton);

            // ROW HEIGHT
            this->ui->invoiceTableWidget->setRowHeight(rowCount, 35);
            rowCount++;
        }
        this->ui->totalDisplayLabel->setText(QString("%1 €").arg(totalInvoice));
    }
    //
    void MemberDashboardWindow::on_invoiceCloseButton_clicked()
    {
        // check invoice is not empty
        if (!this->ui->invoiceTableWidget->rowCount()) {
            QMessageBox::information(this, tr("Note"),
                    tr("Current invoice is empty"));
            return;
        }
        m_switchCentralWidgetCallback(WindowKey::kInvoiceWindowKey);
    }
    //
    void MemberDashboardWindow::on_invoiceResetButton_clicked()
    {
        // ask for confirmation
        QMessageBox::StandardButton answerButton = QMessageBox::question(this, tr("reset invoice"), tr("Are you sure?"));
        if (answerButton != QMessageBox::Yes) {
            return;
        }
        // reset invoice
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoiceResultPtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoicePtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (pInvoicePtr->m_pInvoice) {
            Singletons::m_pDAO->deleteInvoice(pInvoicePtr->m_pInvoice->m_id);
        }
        // nothing to fill
        fillInvoiceData(InvoicePtr());
    }
    //
    void MemberDashboardWindow::on_exitButton_clicked()
    {
        // call login window on exit
        m_switchCentralWidgetCallback(WindowKey::kLoginWindowKey);
    }
    void MemberDashboardWindow::on_depositsButton_clicked()
    {
        // call deposits window
        m_switchCentralWidgetCallback(WindowKey::kDepositsWindowKey);
    }
    //
    void MemberDashboardWindow::on_invoiceTableWidget_cellClicked(int row, int column)
    {
        UNUSEDPARAMETER(column);
        auto rowMap = m_rowProductIdMap.find(row);
        if (rowMap == m_rowProductIdMap.end()) {
            //this should never happen
            return;
        }
        Int32 productId = rowMap->second;
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            return;
        }

        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        Uint32 count = numItemDialog.getKey();
        if (!count) {
            // count was 0 -> remove item from invoice
            bool ok = Singletons::m_pServices->removeInvoiceProductId(pInvoiceResultPtr->m_pInvoice->m_id, productId);
            if (!ok) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            // Check invoice was removed
            InvoiceResultPtr pNewInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
            fillInvoiceData(pNewInvoicePtr->m_pInvoice);
        } else {
            // count was not 0 -> update item from invoice
            bool ok = Singletons::m_pServices->updateInvoiceInfo(pInvoiceResultPtr->m_pInvoice->m_id, productId, count);
            if (!ok) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
            fillInvoiceData(pInvoiceResultPtr->m_pInvoice);
        }
    }
    //
    void MemberDashboardWindow::on_accountButton_clicked()
    {
        // call account window
        m_switchCentralWidgetCallback(WindowKey::kAccountViewWindowKey);
    }
    //
    void MemberDashboardWindow::on_tableReservationButton_clicked()
    {
        // call table reservation window
        m_switchCentralWidgetCallback(WindowKey::kTableReservationViewWindowKey);
    }
    //
    void MemberDashboardWindow::on_invoicesPushButton_clicked()
    {
        // call invoices window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }
    //
    void MemberDashboardWindow::on_productListWidget_itemClicked(QListWidgetItem *item)
    {
        Int32 productId = item->data(Constants::kIdRole).toInt();
        NumItemDialog numItemDialog(this);
        numItemDialog.exec();
        Uint32 count = numItemDialog.getKey();
        if (!count) {
            // nothing to add or create
            return;
        }
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            // there is no active invoice, create it!
            pInvoiceResultPtr = Singletons::m_pDAO->createInvoice(pCurrMemberPtr->m_id);
            if (pInvoiceResultPtr->m_error) {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
                return;
            }
        }
        // increase product count
        bool ok = Singletons::m_pServices->increaseProductInvoice(pInvoiceResultPtr->m_pInvoice->m_id, productId, count);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);
    }
    //
    void MemberDashboardWindow::on_productRemoveButton_clicked(int productId, QString productName, Float totalPrice)
    {
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice)
        {
            QLOG_WARN() << QString("[User %1] Unable to find current active invoice").arg(Singletons::m_pCurrMember->m_id);
            QMessageBox::warning(this, tr("Error happened"), tr("Invoice not found"));
            return;
        }
        // ask for confirmation
        QMessageBox::StandardButton answerButton = QMessageBox::question(this, tr("Delete product"),
            tr("Delete %1 for %2 €?").arg(productName).arg(QString::number(totalPrice, 'f', 2)));
        if (answerButton != QMessageBox::Yes) {
            return;
        }
        bool ok = Singletons::m_pServices->removeInvoiceProductId(pInvoiceResultPtr->m_pInvoice->m_id, productId);
        if (!ok) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        // Check invoice was removed
        InvoiceResultPtr pNewInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pNewInvoiceResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }
        fillInvoiceData(pNewInvoiceResultPtr->m_pInvoice);
    }
}


void PenyaManager::MemberDashboardWindow::on_newinvoiceButton_clicked()
{
    // Go to dashboard window
    m_switchCentralWidgetCallback(WindowKey::kMemberDashboardWindowKey);
}
