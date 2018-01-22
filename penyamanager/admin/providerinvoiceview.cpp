//

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
        ProviderInvoiceResultPtr providerInvoiceResultPtr = Singletons::m_pDAO->getProviderInvoiceById(providerInvoiceId);
        if (providerInvoiceResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        if (!providerInvoiceResultPtr->m_pProviderInvoice) {
            Singletons::m_pLogger->Warn(Constants::kSystemUserId, PenyaManager::LogAction::kDashboard,
                    QString("provider invoice id %1 not found in ddbb").arg(providerInvoiceId));
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Operation not performed. Contact administrator"), [](){});
            return;
        }
        this->ui->invoiceIdValueLabel->setText(providerInvoiceId);
        this->ui->invoiceTotalValueLabel->setText(QString("%1 €").arg(providerInvoiceResultPtr->m_pProviderInvoice->m_total, 0, 'f', 2));
        QString dateLocalized = Singletons::m_pTranslationManager->getLocale().toString(providerInvoiceResultPtr->m_pProviderInvoice->m_regDate, QLocale::NarrowFormat);
        this->ui->providerInvoiceDateValueLabel->setText(dateLocalized);
        this->ui->providerNameLabel->setText(providerInvoiceResultPtr->m_pProviderInvoice->m_providerName);
        // provider image
        QString imagePath = QDir(Singletons::m_pSettings->value(Constants::kResourcePathKey).toString()).filePath(providerInvoiceResultPtr->m_pProviderInvoice->m_providerImagePath);
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
        ProviderInvoiceProductItemListResultPtr pListResultPtr = Singletons::m_pDAO->getProviderInvoiceProductsByInvoiceId(providerInvoiceId);
        if (pListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }
        // num rows
        this->ui->providerInvoiceTableWidget->setRowCount(pListResultPtr->m_list->size());
        // table reset
        this->ui->providerInvoiceTableWidget->clearContents();

        Uint32 rowCount = 0;
        for (ProviderInvoiceProductItemList::iterator iter = pListResultPtr->m_list->begin(); iter != pListResultPtr->m_list->end(); ++iter)
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
            this->ui->providerInvoiceTableWidget->setItem(rowCount, column++, new QTableWidgetItem(Singletons::m_pTranslationManager->getStringTranslation(pProductPtr->m_productNameEus, pProductPtr->m_productNameEs)));
            // count
            this->ui->providerInvoiceTableWidget->setItem(rowCount, column++, new QTableWidgetItem(QString::number(pProductPtr->m_count)));
            rowCount++;
        }
    }
}

