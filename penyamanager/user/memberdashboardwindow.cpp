//

#include <QLabel>
#include <QDateTime>
#include <QMessageBox>
#include <QsLog.h>

#include <commons/constants.h>
#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "numitemdialog.h"
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
        translateTable();
        Uint32 column = 0;
        this->ui->invoiceTableWidget->setColumnWidth(column++, 150);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 70);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 30);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 70);
        this->ui->invoiceTableWidget->setColumnWidth(column++, 50);
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
            QLOG_ERROR() << QString("[FATAL] Unable to initialize Database: %1").arg(err.text());
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(1);
            return;
        }

        //
        // Loading User profile
        //
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        pCurrMemberPtr = Singletons::m_pDAO->getMemberById(pCurrMemberPtr->m_id);
        Singletons::m_pCurrMember = pCurrMemberPtr;
        this->m_pMemberProfileGroupBox->init(pCurrMemberPtr);

        //
        // Loading families
        //

        ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies(true);

        this->ui->productListWidget->clear();

        fillFamilyProducts(pfListPtr);

        //
        // Loading Current Invoice (if it exists)
        //

        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        // pInvoicePtr could be null
        fillInvoiceData(pInvoicePtr);
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
        QWidget *pProduceItemWidget = new QWidget;

        // load product image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap productItemPixmap = GuiUtils::getImage(imagePath);
        pImageLabel->setPixmap(productItemPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        // product info: name and price
        QWidget *pProductItemInfoWidget = new QWidget;
        QVBoxLayout *pInfoLayout = new QVBoxLayout;
        pInfoLayout->setContentsMargins(2,2,2,2);
        QLabel *pTextLabel = new QLabel(pfPtr->m_name);
        //pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        //pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        QLabel *pProductPriceLabel = new QLabel(QString("%1 €").arg(pfPtr->m_price, 0, 'f', 2));
        //pProductPriceLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth);
        //pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pInfoLayout->addWidget(pTextLabel);
        pInfoLayout->addWidget(pProductPriceLabel);
        pProductItemInfoWidget->setLayout(pInfoLayout);
        pProductItemInfoWidget->setFixedWidth(Constants::kFamilyWidgetWidth);

        QHBoxLayout *pLayout = new QHBoxLayout;
        pLayout->setContentsMargins(2,2,2,2);
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pProductItemInfoWidget);
        pProduceItemWidget->setLayout(pLayout);
        pProductItem->setSizeHint(pLayout->minimumSize());
        pProductItem->setFlags(Qt::ItemIsSelectable);
        pProductItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        pList->setItemWidget(pProductItem, pProduceItemWidget);
    }

    //
    void MemberDashboardWindow::createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pFamilyItem = new QListWidgetItem(pList);
        pFamilyItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pFamilyItem);

        QWidget *pFamilyWidget = new QWidget;
        // load family image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pfPtr->m_imagePath);
        QPixmap familyPixmap = GuiUtils::getImage(imagePath);
        pImageLabel->setPixmap(familyPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        QLabel *pTextLabel = new QLabel(pfPtr->m_name);
        //pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);

        QHBoxLayout *pLayout = new QHBoxLayout;
        pLayout->setContentsMargins(2,2,2,2);
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pTextLabel);
        pFamilyWidget->setLayout(pLayout);
        pFamilyItem->setSizeHint(pLayout->minimumSize());
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

        ProductItemListPtr pfListPtr = Singletons::m_pDAO->getProductsFromFamily(familyId, true);

        for (ProductItemList::iterator iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
        {
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
            this->ui->invoiceInfoLabel->setText("");
            // invoice table reset
            this->ui->invoiceTableWidget->clearContents();
            this->ui->invoiceTableWidget->setRowCount(0);
            this->ui->totalDisplayLabel->setText("0 €");
            return;
        }

        // Invoice header
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(pInvoicePtr->m_date, QLocale::NarrowFormat);
        this->ui->invoiceInfoLabel->setText(tr("Created on %1").arg(dateLocalized));

        // get invoice products
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);

        // table
        this->ui->invoiceTableWidget->setRowCount(pInvoiceProductItemListPtr->size());

        // invoice table reset
        this->ui->invoiceTableWidget->clearContents();
        // internal data structure reset
        this->m_rowProductIdMap.clear();

        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->invoiceTableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit, 0, 'f', 2)));
            this->ui->invoiceTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceTableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString("%1 €").arg(totalPrice, 0, 'f', 2)));
            totalInvoice += totalPrice;
            this->m_rowProductIdMap[rowCount] = pInvoiceProductItemPtr->m_productId;
            // show remove action
            QPushButton *pRemoveButton = new QPushButton(tr("Remove"), this->ui->invoiceTableWidget);
            this->connect(pRemoveButton, &QPushButton::clicked, std::bind(&MemberDashboardWindow::on_productRemoveButton_clicked, this, pInvoiceProductItemPtr->m_productId));
            this->ui->invoiceTableWidget->setCellWidget(rowCount, 4, pRemoveButton);
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
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (pInvoicePtr) {
            Singletons::m_pDAO->deleteInvoice(pInvoicePtr->m_id);
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
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);

        NumItemDialog numItemDialog(this, tr("Enter number of items"));
        numItemDialog.exec();
        Uint32 count = numItemDialog.getKey();
        if (!count) {
            // count was 0 -> remove item from invoice
            Singletons::m_pServices->removeInvoiceProductId(pInvoicePtr->m_id, productId);
            // Check invoice was removed
            InvoicePtr pNewInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
            fillInvoiceData(pNewInvoicePtr);
        } else {
            // count was not 0 -> update item from invoice
            Singletons::m_pServices->updateInvoiceInfo(pInvoicePtr->m_id, productId, count);
            fillInvoiceData(pInvoicePtr);
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
        // call table reservation window
        m_switchCentralWidgetCallback(WindowKey::kInvoiceListWindoKey);
    }
    //
    void MemberDashboardWindow::on_productListWidget_itemClicked(QListWidgetItem *item)
    {
        Int32 productId = item->data(Constants::kIdRole).toInt();
        NumItemDialog numItemDialog(this, tr("Enter number of items"));
        numItemDialog.exec();
        Uint32 count = numItemDialog.getKey();
        if (!count) {
            // nothing to add or create
            return;
        }
        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMemberPtr->m_id);
        if (!pInvoicePtr) {
            // there is no active invoice, create it!
            pInvoicePtr = Singletons::m_pDAO->createInvoice(pCurrMemberPtr->m_id);
        }
        // increase product count
        Singletons::m_pServices->increaseProductInvoice(pInvoicePtr->m_id, productId, count);
        fillInvoiceData(pInvoicePtr);
    }
    //
    void MemberDashboardWindow::on_productRemoveButton_clicked(int productId)
    {
        // ask for confirmation
        QMessageBox::StandardButton answerButton = QMessageBox::question(this, tr("delete product item"), tr("Are you sure?"));
        if (answerButton != QMessageBox::Yes) {
            return;
        }
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        Singletons::m_pServices->removeInvoiceProductId(pInvoicePtr->m_id, productId);
        // Check invoice was removed
        InvoicePtr pNewInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        fillInvoiceData(pNewInvoicePtr);
    }
}

