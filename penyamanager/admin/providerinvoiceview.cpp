//

#include <QDebug>
#include <QSpinBox>
#include <QSpacerItem>
#include <QMessageBox>
#include <QsLog.h>

#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "providerinvoiceview.h"
#include "ui_providerinvoiceview.h"

namespace PenyaManager {
    //
    ProviderInvoiceView::ProviderInvoiceView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::ProviderInvoiceView)
    {
        ui->setupUi(this);
        initializeTable();
    }
    //
    ProviderInvoiceView::~ProviderInvoiceView()
    {
        delete ui;
    }
    //
    void ProviderInvoiceView::initializeTable()
    {
        // table
        this->ui->providerInvoiceTableWidget->setColumnCount(3);
        translateTable();
        Uint32 column = 0;
        this->ui->providerInvoiceTableWidget->setColumnWidth(column++, Constants::kFamilyImageWidth);
        this->ui->providerInvoiceTableWidget->setColumnWidth(column++, 300);
        this->ui->providerInvoiceTableWidget->setColumnWidth(column++, 150);
    }
    //
    void ProviderInvoiceView::translateTable()
    {
        // invoice table Header
        QStringList headers;
        headers.append(tr("Icon"));
        headers.append(tr("Product"));
        headers.append(tr("Count"));
        this->ui->providerInvoiceTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void ProviderInvoiceView::initialize()
    {
        QString providerInvoiceId(Singletons::m_currentProviderInvoiceId);
        ProviderInvoicePtr providerInvoicePtr = Singletons::m_pDAO->getProviderInvoiceById(providerInvoiceId);
        if (!providerInvoicePtr) {
            QLOG_ERROR() << QString("[ERROR] provider invoice id {%1} not found in ddbb").arg(providerInvoiceId);
            QMessageBox::warning(this, tr("Error"), tr("Unexpected error"));
            return;
        }
        this->ui->invoiceIdValueLabel->setText(providerInvoiceId);
        this->ui->invoiceTotalValueLabel->setText(QString("%1 €").arg(providerInvoicePtr->m_total, 0, 'f', 2));
        QString dateLocalized = Singletons::m_translationManager.getLocale().toString(providerInvoicePtr->m_regDate, QLocale::NarrowFormat);
        this->ui->providerInvoiceDateValueLabel->setText(dateLocalized);
        this->ui->providerNameLabel->setText(providerInvoicePtr->m_providerName);
        // provider image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(providerInvoicePtr->m_providerImagePath);
        QPixmap providerPixmap = GuiUtils::getImage(imagePath);
        this->ui->providerImageLabel->setPixmap(providerPixmap);
        this->ui->providerImageLabel->setFixedWidth(Constants::kFamilyImageWidth);
        this->ui->providerImageLabel->setFixedHeight(Constants::kFamilyImageHeigth);
        this->ui->providerImageLabel->setScaledContents(true);
        fillProviderInvoiceProducts(providerInvoiceId);
    }
    //
    void ProviderInvoiceView::init()
    {
        initialize();
    }
    //
    void ProviderInvoiceView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void ProviderInvoiceView::fillProviderInvoiceProducts(const QString &providerInvoiceId)
    {
        ProviderInvoiceProductItemListPtr pListPtr = Singletons::m_pDAO->getProviderInvoiceProductsByInvoiceId(providerInvoiceId);
        // num rows
        this->ui->providerInvoiceTableWidget->setRowCount(pListPtr->size());
        // table reset
        this->ui->providerInvoiceTableWidget->clearContents();

        Uint32 rowCount = 0;
        for (ProviderInvoiceProductItemList::iterator iter = pListPtr->begin(); iter != pListPtr->end(); ++iter)
        {
            ProviderInvoiceProductItemPtr pProductPtr = *iter;
            Uint32 column = 0;
            // icon image
            QTableWidgetItem *productImageWidget = new QTableWidgetItem;
            QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(pProductPtr->m_productImagePath);
            QPixmap productItemPixmap = GuiUtils::getImage(imagePath).scaled(Constants::kFamilyImageWidth, Constants::kFamilyImageHeigth);
            productImageWidget->setData(Qt::DecorationRole, productItemPixmap);
            this->ui->providerInvoiceTableWidget->setRowHeight(rowCount, Constants::kFamilyImageHeigth);
            this->ui->providerInvoiceTableWidget->setItem(rowCount, column++, productImageWidget);
            // product name
            this->ui->providerInvoiceTableWidget->setItem(rowCount, column++, new QTableWidgetItem(pProductPtr->m_productName));
            // count
            this->ui->providerInvoiceTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pProductPtr->m_count)));
            rowCount++;
        }
    }
}

