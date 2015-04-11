//

#include <QLabel>
#include <QDateTime>
#include <QMessageBox>

#include "constants.h"
#include "utils.h"
#include "numitemdialog.h"
#include "singletons.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace PenyaManager {

    //
    MainWindow::MainWindow(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        this->connect(this->ui->quitButton, SIGNAL(clicked()), this, SLOT(quitButtonOnClick()));
        this->connect(this->ui->familyListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(familyItemClicked(QListWidgetItem*)));
        this->connect(this->ui->productListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(productItemClicked(QListWidgetItem*)));
    }

    //
    MainWindow::~MainWindow()
    {
        delete ui;
    }

    //
    void MainWindow::setParner(IPartner *partner)
    {
        if(partner == 0)
            return;

        connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(hide()));
        connect(this->ui->exitButton, SIGNAL(clicked()), partner, SLOT(init()));

    }

    void MainWindow::init()
    {
        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(0);
            return;
        }

        //
        // Loading User profile
        //

        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        fillMemberProfile(pCurrMember);

        //
        // Loading families
        //

        ProductFamilyListPtr pfListPtr = Singletons::m_pDAO->getProductFamilies();

        this->ui->productListWidget->clear();

        fillFamilyProducts(pfListPtr);

        //
        // Loading Current Invoice (if it exists)
        //

        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        if (!pInvoicePtr) {
            // there is no active invoice, create it!
            pInvoicePtr = Singletons::m_pDAO->createInvoice(pCurrMember->m_id);
        }

        fillInvoiceData(pInvoicePtr);

        //
        // Show
        //

        show();
    }

    //
    void MainWindow::createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pProductItem = new QListWidgetItem(pList);
        pProductItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pProductItem);

        // main product widget
        QWidget *pProduceItemWidget = new QWidget;

        // load product image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pfPtr->m_imagePath);
        QPixmap productItemPixmap = Utils::getImage(imagePath);
        pImageLabel->setPixmap(productItemPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        // product info: name and price
        QWidget *pProductItemInfoWidget = new QWidget;
        QVBoxLayout *pInfoLayout = new QVBoxLayout;
        QLabel *pTextLabel = new QLabel(pfPtr->m_name);
        pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        //pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        QLabel *pProductPriceLabel = new QLabel(QString("%1 €").arg(pfPtr->m_price));
        pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        //pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pInfoLayout->addWidget(pTextLabel);
        pInfoLayout->addWidget(pProductPriceLabel);
        pProductItemInfoWidget->setLayout(pInfoLayout);

        QHBoxLayout *pLayout = new QHBoxLayout;
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pProductItemInfoWidget);
        pProduceItemWidget->setLayout(pLayout);
        pProductItem->setSizeHint(pLayout->minimumSize());
        pProductItem->setFlags(Qt::ItemIsSelectable);
        pProductItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        pList->setItemWidget(pProductItem, pProduceItemWidget);
    }

    //
    void MainWindow::createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList)
    {
        QListWidgetItem *pFamilyItem = new QListWidgetItem(pList);
        pFamilyItem->setData(Constants::kIdRole, pfPtr->m_id);
        pList->addItem(pFamilyItem);

        QWidget *pFamilyWidget = new QWidget;
        // load family image
        QLabel *pImageLabel = new QLabel;
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pfPtr->m_imagePath);
        QPixmap familyPixmap = Utils::getImage(imagePath);
        pImageLabel->setPixmap(familyPixmap);
        pImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        pImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        pImageLabel->setScaledContents(true);

        QLabel *pTextLabel = new QLabel(pfPtr->m_name);
        pTextLabel->setFixedWidth(Constants::kFamilyWidgetWidth -  Constants::kFamilyImageWidth - 5);
        pTextLabel->setFixedHeight(Constants::kFamilyImageHeigth);

        QHBoxLayout *pLayout = new QHBoxLayout;
        pLayout->addWidget(pImageLabel);
        pLayout->addWidget(pTextLabel);
        pFamilyWidget->setLayout(pLayout);
        pFamilyItem->setSizeHint(pLayout->minimumSize());
        pFamilyItem->setFlags(Qt::ItemIsSelectable);
        pFamilyItem->setBackgroundColor(pList->count() % 2 == 0 ? (Qt::lightGray) : (Qt::darkGray));
        pList->setItemWidget(pFamilyItem, pFamilyWidget);
    }
    //
    void MainWindow::fillFamilyProducts(const ProductFamilyListPtr &pflPtr)
    {
        this->ui->familyListWidget->clear();

        for (ProductFamilyList::iterator iter = pflPtr->begin(); iter != pflPtr->end(); ++iter)
        {
            createFamilyWidget(*iter, this->ui->familyListWidget);
        }
    }

    //
    void MainWindow::fillProductItems(Int32 familyId)
    {
        this->ui->productListWidget->clear();

        ProductItemListPtr pfListPtr = Singletons::m_pDAO->getProductsFromFamily(familyId);

        for (ProductItemList::iterator iter = pfListPtr->begin(); iter != pfListPtr->end(); ++iter)
        {
            createProductItemWidget(*iter, this->ui->productListWidget);
        }
    }

    //
    void MainWindow::quitButtonOnClick()
    {
        // qApp is a macro defined as: (QApplication*)QCoreApplication::instance()
        qApp->exit(0);
        //close();
    }

    //
    void MainWindow::familyItemClicked(QListWidgetItem* item)
    {
        Int32 familyId = item->data(Constants::kIdRole).toInt();
        fillProductItems(familyId);
    }

    //
    void MainWindow::fillMemberProfile(const MemberPtr &pMemberPtr)
    {
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
        QPixmap memberPixmap = Utils::getImage(imagePath);
        this->ui->memberImage->setPixmap(memberPixmap);
        this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->memberImage->setScaledContents(true);
        this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
        this->ui->memberIdInfo->setText(QString::number(pMemberPtr->m_id));
        this->ui->memberBalanceInfo->setText(QString::number(pMemberPtr->m_balance, 'f', 2));
    }

    //
    void MainWindow::fillInvoiceData(const InvoicePtr &pInvoicePtr)
    {
        if (!pInvoicePtr) {
            return;
        }

        // Invoice header
        this->ui->invoiceGroupBox->setTitle(tr("Invoice (Ref #%1) on (%2)").arg(pInvoicePtr->m_id).arg(pInvoicePtr->m_date.toString()));

        // get invoice products
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);

        // table
        this->ui->invoiceTableWidget->setColumnCount(4);
        this->ui->invoiceTableWidget->setRowCount(pInvoiceProductItemListPtr->size());

        // invoice table Header
        QStringList headers;
        headers.append("article");
        headers.append("price/u");
        headers.append("count");
        headers.append("total");
        this->ui->invoiceTableWidget->setHorizontalHeaderLabels(headers);
        // invoice table reset
        this->ui->invoiceTableWidget->clearContents();

        Uint32 rowCount = 0;
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            this->ui->invoiceTableWidget->setItem(rowCount, 0, new QTableWidgetItem(pInvoiceProductItemPtr->m_productname));
            this->ui->invoiceTableWidget->setItem(rowCount, 1, new QTableWidgetItem(tr("%1 €").arg(pInvoiceProductItemPtr->m_priceperunit)));
            this->ui->invoiceTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1").arg(pInvoiceProductItemPtr->m_count)));
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            this->ui->invoiceTableWidget->setItem(rowCount, 3, new QTableWidgetItem(tr("%1 €").arg(totalPrice)));
            totalInvoice += totalPrice;
            rowCount++;
        }
        this->ui->totalDisplayLabel->setText(QString("%1 €").arg(totalInvoice));
    }
    //
    void MainWindow::productItemClicked(QListWidgetItem* item)
    {
        Int32 productId = item->data(Constants::kIdRole).toInt();
        //QMessageBox::critical(this, "some text", QString("product_id: %1").arg(productId));
        NumItemDialog numItemDialog(this);
        Uint32 count = numItemDialog.exec();
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);

        if (!count) {
            // count was 0 -> remove item from invoice
            Singletons::m_pDAO->removeProductInvoice(pInvoicePtr->m_id, productId);
        } else {
            // count was not 0 -> update item from invoice
            Singletons::m_pDAO->updateProductInvoice(pInvoicePtr->m_id, productId, count);
        }

        // always fresh invoice
        pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        fillInvoiceData(pInvoicePtr);
    }
    //
    void MainWindow::on_invoiceCloseButton_clicked()
    {
        /*
        Int32 ret = QMessageBox::information(this, tr("Invoice will be closed"), tr("Do you want to continue?"), QMessageBox::Yes | QMessageBox::No);
        switch (ret) {
            case QMessageBox::Yes:
                // close invoice
                qDebug() << "close";
                break;
            default:
                // nop
                qDebug() << "do not close";
                break;
        }
        */
    }
    //
    void MainWindow::on_invoiceResetButton_clicked()
    {
        MemberPtr pCurrMember = Singletons::m_pCurrMember;
        // always fresh invoice
        InvoicePtr pInvoicePtr = Singletons::m_pDAO->getMemberActiveInvoice(pCurrMember->m_id);
        Singletons::m_pDAO->resetInvoiceProductItems(pInvoicePtr->m_id);
        fillInvoiceData(pInvoicePtr);
    }
    //
    void MainWindow::closeCurrentInvoice()
    {
    }
}


