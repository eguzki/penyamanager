//

#include <QDebug>

#include "utils.h"
#include "singletons.h"
#include "providerinvoiceview.h"
#include "ui_providerinvoiceview.h"

namespace PenyaManager {
    //
    ProviderInvoiceView::ProviderInvoiceView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::ProviderInvoiceView),
        m_currentProviderIndex(-1),
        m_rowProviderIdMap()
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
    void ProviderInvoiceView::on_savePushButton_clicked()
    {

    }
    //
    void ProviderInvoiceView::initialize()
    {
        m_currentProviderIndex = -1;
        this->ui->invoiceLineEdit->clear();
        this->ui->totalLineEdit->clear();
        this->ui->providerComboBox->clear();
        this->ui->productsTableWidget->clear();

        ProviderListPtr pProviderListPtr = Singletons::m_pDAO->getProviderList();

        // internal data structure reset
        this->m_rowProviderIdMap.clear();
        Int32 idx = 0;
        for (auto iter = pProviderListPtr->begin(); iter != pProviderListPtr->end(); ++iter)
        {
            ProviderPtr pProviderPtr = *iter;
            QString providerImagePath = QDir(Constants::kImageRootPath).filePath(pProviderPtr->m_image);
            QPixmap productPixmap = Utils::getImage(providerImagePath);
            this->ui->providerComboBox->insertItem(idx, QIcon(productPixmap), pProviderPtr->m_name, pProviderPtr->m_id);
            this->m_rowProviderIdMap[idx] = pProviderPtr->m_id;
            idx++;
        }
        // do not show any provider by default (-1)
        this->ui->providerComboBox->setCurrentIndex(m_currentProviderIndex);
    }
    //
    void ProviderInvoiceView::initializeTable()
    {
        // table
        this->ui->productsTableWidget->setColumnCount(3);
        // invoice table Header
        QStringList headers;
        headers.append("Image");
        headers.append("name");
        headers.append("# units");

        this->ui->productsTableWidget->setHorizontalHeaderLabels(headers);
        this->ui->productsTableWidget->setColumnWidth(0, Constants::kFamilyImageWidth);
        this->ui->productsTableWidget->setColumnWidth(1, 300);
        this->ui->productsTableWidget->setColumnWidth(2, 100);
    }
    //
    void ProviderInvoiceView::init()
    {
        initialize();
        //
        // Show
        //

        show();
    }
    //
    void ProviderInvoiceView::on_providerComboBox_activated(int index)
    {
        if (index < 0 || index == m_currentProviderIndex){
            return;
        }
        m_currentProviderIndex = index;

        auto rowMap = m_rowProviderIdMap.find(m_currentProviderIndex);
        if (rowMap == m_rowProviderIdMap.end()) {
            //this should never happen
            qDebug() << "[ERROR] providerId not found and should be in the map";
            return;
        }

        // get provider ID
        Int32 providerId = rowMap->second;

        qDebug() << "provider: " << providerId;
    }
}

