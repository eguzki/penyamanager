//

#include <commons/constants.h>
#include <commons/guiutils.h>
#include <commons/singletons.h>
#include <commons/familyitemwidget.h>
#include <commons/productitemwidget.h>
#include "memberdashboardwindow.h"
#include "ui_memberdashboardwindow.h"

namespace PenyaManager {

    //
    MemberDashboardWindow::MemberDashboardWindow(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::MemberDashboardWindow),
        m_currentPage(0),
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
        this->ui->invoiceTableWidget->setColumnWidth(column++, 56);
    }
    //
    void MemberDashboardWindow::retranslate()
    {
        this->ui->retranslateUi(this);
        this->m_pMemberProfileGroupBox->retranslate();
        translateTable();
    }
    //
    void MemberDashboardWindow::translateTable()
    {
        // table Header
        QStringList headers;
        headers.append(tr("article"));
        headers.append(tr("price/u"));
        headers.append(tr("Count"));
        headers.append(tr("total"));
        headers.append(tr("Remove"));
        this->ui->invoiceTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void MemberDashboardWindow::init()
    {
        //
        // Loading User profile
        //
        MemberResultPtr pMemberResultPtr = Singletons::m_pServices->getMemberById(Singletons::m_pCurrMember->m_id);
        if (pMemberResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pMemberResultPtr->m_member) {
            // member not found, should not happen
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kDashboard,
                    QString("Unable to find owner by id %1").arg(Singletons::m_pCurrMember->m_id));
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
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        this->ui->productListWidget->clear();

        fillFamilyProducts(pfListPtr->m_list);

        //
        // Loading Current Invoice (if it exists)
        //
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        m_currentPage = 0;
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);

        // check negative balance
        if (pMemberResultPtr->m_member->m_balance < 0)
        {
            // User is slow payer
            Singletons::m_pDialogManager->criticalMessageBox(this,
                    tr("Your current balance is negative: %1 €").arg(pMemberResultPtr->m_member->m_balance, 0, 'f', 2),
                    std::bind(&MemberDashboardWindow::checkCreditLimit, this)
                    );
            return;
        }
        checkCreditLimit();
    }
    //
    void MemberDashboardWindow::checkCreditLimit()
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        //
        // check credit limit
        //
        if (pCurrMemberPtr->m_balance < Constants::kCreditLimit)
        {
            // User has gone over credit limit. Do not allow creating invoice
            this->ui->familyListWidget->setDisabled(true);
            this->ui->invoiceCloseButton->setDisabled(true);
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Your current balance is over limit (%1 €): %2 €").arg(Constants::kCreditLimit, 0, 'f', 2).arg(pCurrMemberPtr->m_balance, 0, 'f', 2), [](){});
            return;
        } else {
            this->ui->familyListWidget->setDisabled(false);
            this->ui->invoiceCloseButton->setDisabled(false);
        }
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
        QWidget *pProduceItemWidget = new ProductItemWidget(pList, productItemPixmap, Singletons::m_pTranslationManager->getStringTranslation(pfPtr->m_nameEus, pfPtr->m_nameEs), pfPtr->m_price);

        // load product image
        pProductItem->setSizeHint(pProduceItemWidget->minimumSize());
        pProductItem->setFlags(Qt::ItemIsSelectable);
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
        QWidget *pFamilyWidget = new FamilyItemWidget(pList, familyPixmap, Singletons::m_pTranslationManager->getStringTranslation(pfPtr->m_nameEus, pfPtr->m_nameEs));

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
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
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
            this->ui->pagingWidget->setHidden(true);
            this->ui->totalDisplayLabel->setText("0.00 €");
            return;
        }

        // get invoice products
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id, m_currentPage, Constants::kDashboardProductListPageCount);
        if (pInvoiceProductItemListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(pInvoicePtr->m_id);
        if (invoiceProductItemStatsResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // enable-disable pagination buttons
        // total num pages
        Uint32 numPages = (Uint32)ceil((Float)invoiceProductItemStatsResultPtr->m_stats->m_totalProducts/Constants::kDashboardProductListPageCount);
        // when just single page, hide pagingWidget
        this->ui->pagingWidget->setHidden(numPages <= 1);
        if (numPages > 1) {
            this->ui->prevPagePushButton->setEnabled(m_currentPage > 0);
            this->ui->nextPagePushButton->setEnabled(m_currentPage < numPages-1);
            this->ui->pageInfoLabel->setText(QString("%1 / %2").arg(m_currentPage+1).arg(numPages));
        }
        // invoice table reset
        this->ui->invoiceTableWidget->clearContents();

        // table
        this->ui->invoiceTableWidget->setRowCount(pInvoiceProductItemListResultPtr->m_list->size());

        // internal data structure reset
        this->m_rowProductIdMap.clear();

        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceTableWidget->setItem(rowCount, 0, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pInvoiceProductItemPtr->m_productnameEus, pInvoiceProductItemPtr->m_productnameEs)));
            this->ui->invoiceTableWidget->item(rowCount, 0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            this->ui->invoiceTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_currentPricePerUnit, 0, 'f', 2)));
            this->ui->invoiceTableWidget->item(rowCount, 1)->setTextAlignment(Qt::AlignCenter);
            this->ui->invoiceTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            this->ui->invoiceTableWidget->item(rowCount, 2)->setTextAlignment(Qt::AlignCenter);
            Float totalPrice = pInvoiceProductItemPtr->m_currentPricePerUnit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            this->ui->invoiceTableWidget->item(rowCount, 3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            this->m_rowProductIdMap[rowCount] = pInvoiceProductItemPtr->m_productId;
            // show remove action
            QPushButton *pRemoveButton = new QPushButton("", this->ui->invoiceTableWidget);
            QPixmap pixmap(":images/trash.png");
            QIcon buttonIcon(pixmap);
            pRemoveButton->setIcon(buttonIcon);
            this->connect(pRemoveButton, &QPushButton::clicked, std::bind(&MemberDashboardWindow::on_productRemoveButton_clicked, this,
                  pInvoiceProductItemPtr->m_productId,
                  pInvoiceProductItemPtr->m_productnameEus,
                  pInvoiceProductItemPtr->m_productnameEs,
                  totalPrice));
            this->ui->invoiceTableWidget->setCellWidget(rowCount, 4, pRemoveButton);

            // ROW HEIGHT
            this->ui->invoiceTableWidget->setRowHeight(rowCount, 35);
            totalInvoice += totalPrice;
            rowCount++;
        }
        this->ui->totalDisplayLabel->setText(QString("%1 €").arg(totalInvoice, 0, 'f', 2));
    }
    //
    void MemberDashboardWindow::on_invoiceCloseButton_clicked()
    {
        // check invoice is not empty
        if (!this->ui->invoiceTableWidget->rowCount()) {
            Singletons::m_pDialogManager->infoMessageBox(this, tr("Current invoice is empty"), [](){});
            return;
        }
        m_switchCentralWidgetCallback(WindowKey::kInvoiceWindowKey);
    }
    //
    void MemberDashboardWindow::on_invoiceResetButton_clicked()
    {
        // ask for confirmation
        Singletons::m_pDialogManager->questionMessageBox(this,
                tr("Are you sure to reset invoice?"),
                std::bind(&MemberDashboardWindow::onInvoiceReset, this, _1)
                );
    }
    //
    void MemberDashboardWindow::onInvoiceReset(QMessageBox::StandardButton answerButton)
    {
        if (answerButton != QMessageBox::Yes) {
            return;
        }
        // reset invoice
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoiceResultPtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoicePtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (pInvoicePtr->m_pInvoice) {
            Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("reset invoice. Invoice id %1").arg(pInvoicePtr->m_pInvoice->m_id));
            Singletons::m_pDAO->deleteInvoice(pInvoicePtr->m_pInvoice->m_id);
        }
        // nothing to fill
        m_currentPage = 0;
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
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("On invoice table cell clicked, product id not found."));
            return;
        }
        Int32 productId = rowMap->second;

        Singletons::m_pDialogManager->numItemDialog(this, tr("Number of items?"),
                std::bind(&MemberDashboardWindow::onNumItemSelectedFromInvoice, this, productId, _1)
                );
    }
    //
    void MemberDashboardWindow::onNumItemSelectedFromInvoice(Int32 productId, QString resultStr)
    {
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            Singletons::m_pLogger->Warn(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("Unable to find current active invoice"));
            return;
        }

        Uint32 count = resultStr.toUInt();
        if (!count) {
            // nothing to add or create
            return;
        }

        // count was not 0 -> update item from invoice
        BoolResult boolResult = Singletons::m_pServices->increaseProductInvoice(pInvoiceResultPtr->m_pInvoice->m_id, productId, count);
        if (boolResult.error) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("Could not increase invoice product. Invoice id %1, product id %2, count %3").arg(pInvoiceResultPtr->m_pInvoice->m_id).arg(productId).arg(count));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // no need to reset m_currentPage
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);
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
        Singletons::m_pDialogManager->numItemDialog(this, tr("Number of items?"),
                std::bind(&MemberDashboardWindow::onNumItemSelectedFromProductList, this, productId, _1)
                );
    }
    //
    void MemberDashboardWindow::onNumItemSelectedFromProductList(Int32 productId, QString resultStr)
    {
        Uint32 count = resultStr.toUInt();
        if (!count) {
            // nothing to add or create
            return;
        }
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice) {
            // there is no active invoice, create it!
            pInvoiceResultPtr = Singletons::m_pDAO->createInvoice(pCurrMemberPtr->m_id);
            if (pInvoiceResultPtr->m_error) {
                Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
                return;
            }
        }
        // increase product count
        BoolResult boolResult = Singletons::m_pServices->increaseProductInvoice(pInvoiceResultPtr->m_pInvoice->m_id, productId, count);
        if (boolResult.error) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("Could not increase invoice product. Invoice id %1, product id %2, count %3").arg(pInvoiceResultPtr->m_pInvoice->m_id).arg(productId).arg(count));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // when no rowsAffected (new invoice), reset m_currentPage
        if (!boolResult.result) {
            m_currentPage = 0;
        }
        // no need to reset m_currentPage
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);
    }
    //
    void MemberDashboardWindow::on_productRemoveButton_clicked(int productId, QString productNameEus, QString productNameEs, Float totalPrice)
    {
        // ask for confirmation
        Singletons::m_pDialogManager->questionMessageBox(this,
                tr("Delete %1 for %2 €?").arg(Singletons::m_pTranslationManager->getStringTranslation(productNameEus, productNameEs)).arg(QString::number(totalPrice, 'f', 2)),
                std::bind(&MemberDashboardWindow::on_productRemove_result, this, productId, _1)
                );
        // no code should be added here
    }
    //
    void MemberDashboardWindow::on_prevPagePushButton_clicked()
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        m_currentPage--;
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);
    }
    //
    void MemberDashboardWindow::on_nextPagePushButton_clicked()
    {
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        m_currentPage++;
        fillInvoiceData(pInvoiceResultPtr->m_pInvoice);
    }
    //
    void MemberDashboardWindow::on_productRemove_result(int productId, QMessageBox::StandardButton answerButton)
    {
        if (answerButton != QMessageBox::Yes) {
            return;
        }

        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoiceResultPtr pInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!pInvoiceResultPtr->m_pInvoice)
        {
            Singletons::m_pLogger->Warn(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("Unable to find current active invoice, userid %1").arg(pCurrMember->m_id));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        bool ok = Singletons::m_pServices->removeInvoiceProductId(pInvoiceResultPtr->m_pInvoice->m_id, productId);
        if (!ok) {
            Singletons::m_pLogger->Error(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kDashboard,
                    QString("removeInvoiceProductId. invoiceid %1, productid %2").arg(pInvoiceResultPtr->m_pInvoice->m_id).arg(productId));
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // Check invoice was removed
        InvoiceResultPtr pNewInvoiceResultPtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pNewInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBox(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        m_currentPage = 0;
        fillInvoiceData(pNewInvoiceResultPtr->m_pInvoice);
    }
}

