//

#include <commons/singletons.h>
#include "slowpayersview.h"
#include "admininvoicelistview.h"
#include "invoicedetailsview.h"
#include "providermanagerview.h"
#include "adminnewprovider.h"
#include "stockmanagementwindow.h"
#include "familyitemmanagementwindow.h"
#include "adminproductitem.h"
#include "adminfamilyview.h"
#include "productexpensesview.h"
#include "providerinvoiceview.h"
#include "newproviderinvoiceview.h"
#include "providerinvoicelistview.h"
#include "depositlistview.h"
#include "accountbalanceview.h"
#include "memberlistview.h"
#include "memberview.h"
#include "adminreservationswindow.h"

#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

namespace PenyaManager {
    //
    AdminMainWindow::AdminMainWindow(QWidget *parent, QTimer *pInactivityTimer) :
        QMainWindow(parent),
        ui(new Ui::AdminMainWindow),
        m_pEmptyWidget(new QWidget(this)),
        m_pInactivityTimer(pInactivityTimer)
    {
        ui->setupUi(this);

        this->ui->stackedWidget->addWidget(m_pEmptyWidget);
        // central widgets need adminmainwindow callback to call each other
        CentralWidgetCallback adminMainWindowSwitchCallback = std::bind(&AdminMainWindow::switchCentralWidget, this, _1);

        // instantiate adminmain widgets
        AdminInvoiceListView *pAdminInvoiceListView = new AdminInvoiceListView(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminInvoiceListWindowKey, pAdminInvoiceListView);
        this->ui->stackedWidget->addWidget(pAdminInvoiceListView);
        SlowPayersView *pSlowPayersView = new SlowPayersView(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminSlowPayersWindowKey, pSlowPayersView);
        this->ui->stackedWidget->addWidget(pSlowPayersView);
        InvoiceDetailsView *pInvoiceDetailsView = new InvoiceDetailsView(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kInvoiceDetailsWindowKey, pInvoiceDetailsView);
        this->ui->stackedWidget->addWidget(pInvoiceDetailsView);
        ProviderManagerView *pProviderManagerView = new ProviderManagerView(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminProviderWindowKey, pProviderManagerView);
        this->ui->stackedWidget->addWidget(pProviderManagerView);
        AdminNewProvider *pAdminNewProvider = new AdminNewProvider(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminNewProviderKey, pAdminNewProvider);
        this->ui->stackedWidget->addWidget(pAdminNewProvider);
        StockManagementWindow *pStockManagementWindow = new StockManagementWindow(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kStockManagementWindowKey, pStockManagementWindow);
        this->ui->stackedWidget->addWidget(pStockManagementWindow);
        FamilyItemManagementWindow *pFamilyItemManagementWindow = new FamilyItemManagementWindow(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kFamilyItemManagementWindowKey, pFamilyItemManagementWindow);
        this->ui->stackedWidget->addWidget(pFamilyItemManagementWindow);
        AdminProductItem *pAdminProductItem = new AdminProductItem(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminProductItemKey, pAdminProductItem);
        this->ui->stackedWidget->addWidget(pAdminProductItem);
        AdminFamilyView *pAdminFamilyView = new AdminFamilyView(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminFamilyViewKey, pAdminFamilyView);
        this->ui->stackedWidget->addWidget(pAdminFamilyView);
        ProductExpensesView *pProductExpensesView = new ProductExpensesView(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kProductExpensesViewKey, pProductExpensesView);
        this->ui->stackedWidget->addWidget(pProductExpensesView);
        ProviderInvoiceView *pProviderInvoiceView = new ProviderInvoiceView(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kProviderInvoiceViewKey, pProviderInvoiceView);
        this->ui->stackedWidget->addWidget(pProviderInvoiceView);
        NewProviderInvoiceView *pNewProviderInvoiceView = new NewProviderInvoiceView(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kNewProviderInvoiceViewKey, pNewProviderInvoiceView);
        this->ui->stackedWidget->addWidget(pNewProviderInvoiceView);
        ProviderInvoiceListView *pProviderInvoiceListView = new ProviderInvoiceListView(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kProviderInvoiceListViewKey, pProviderInvoiceListView);
        this->ui->stackedWidget->addWidget(pProviderInvoiceListView);
        DepositListView *pDepositListView = new DepositListView(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminDepositListViewKey, pDepositListView);
        this->ui->stackedWidget->addWidget(pDepositListView);
        AccountBalanceView *pAccountBalanceView = new AccountBalanceView(this);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAdminAccountBalanceViewKey, pAccountBalanceView);
        this->ui->stackedWidget->addWidget(pAccountBalanceView);
        MemberListView *pMemberListView = new MemberListView(this, adminMainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kMemberListViewWindowKey, pMemberListView);
        this->ui->stackedWidget->addWidget(pMemberListView);
        MemberView *pMemberView = new MemberView(this, adminMainWindowSwitchCallback);
        PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMemberViewKey, pMemberView);
        this->ui->stackedWidget->addWidget(pMemberView);
        AdminReservationsWindow *pAdminReservationsWindow = new AdminReservationsWindow(this);
        PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminReservationViewKey, pAdminReservationsWindow);
        this->ui->stackedWidget->addWidget(pAdminReservationsWindow);
        // connect QTimer timeout
        this->connect(m_pInactivityTimer, &QTimer::timeout, std::bind(&AdminMainWindow::on_actionExit_triggered, this));
    }
    //
    AdminMainWindow::~AdminMainWindow()
    {
        delete ui;
    }
    //
    void AdminMainWindow::init()
    {
        this->ui->stackedWidget->setCurrentWidget(this->m_pEmptyWidget);
        // start timer
        this->m_pInactivityTimer->start();
    }
    //
    void AdminMainWindow::changeEvent(QEvent* event)
    {
        if (event->type() == QEvent::LanguageChange)
        {
            // retranslate designer form
            this->retranslate();
        }
        QWidget::changeEvent(event);
    }
    //
    void AdminMainWindow::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void AdminMainWindow::on_actionExit_triggered()
    {
        Singletons::m_pDialogManager->onInactivityTimeout();
        // stop timer
        this->m_pInactivityTimer->stop();
        // call admin login window
        hide();
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(WindowKey::kAdminLoginWindowKey);
        pPartner->init();
        pPartner->show();
    }
    //
    void AdminMainWindow::on_actionSlow_payers_triggered()
    {
        // call slow payers window
        switchCentralWidget(WindowKey::kAdminSlowPayersWindowKey);
    }
    //
    void AdminMainWindow::on_actionInvoice_list_triggered()
    {
        // call invoice list window
        switchCentralWidget(WindowKey::kAdminInvoiceListWindowKey);
    }
    //
    void AdminMainWindow::on_actionManage_providers_triggered()
    {
        // call provider manager window
        switchCentralWidget(WindowKey::kAdminProviderWindowKey);
    }
    //
    void AdminMainWindow::on_actionManage_Stock_triggered()
    {
        // call stock list window
        switchCentralWidget(WindowKey::kStockManagementWindowKey);
    }
    //
    void AdminMainWindow::on_actionManage_family_items_triggered()
    {
        // call family item management window
        switchCentralWidget(WindowKey::kFamilyItemManagementWindowKey);
    }
    //
    void AdminMainWindow::on_actionProduct_consumption_triggered()
    {
        // call family item management window
        switchCentralWidget(WindowKey::kProductExpensesViewKey);
    }
    //
    void AdminMainWindow::on_actionProvider_invoice_triggered()
    {
        Singletons::m_currentProductId = -1;
        // call provider invoice window
        switchCentralWidget(WindowKey::kNewProviderInvoiceViewKey);
    }
    //
    void AdminMainWindow::on_actionProvider_invoice_list_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kProviderInvoiceListViewKey);
    }
    //
    void AdminMainWindow::on_actionDeposit_Check_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kAdminDepositListViewKey);
    }
    //
    void AdminMainWindow::on_actionAccount_Balance_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kAdminAccountBalanceViewKey);
    }
    //
    void AdminMainWindow::on_actionMember_management_triggered()
    {
        // call provider invoice window
        switchCentralWidget(WindowKey::kMemberListViewWindowKey);
    }
    //
    void AdminMainWindow::on_actionManager_reservations_triggered()
    {
        // call reservation window
        switchCentralWidget(WindowKey::kAdminReservationViewKey);
    }
    //
    void AdminMainWindow::switchCentralWidget(WindowKey key)
    {
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(key);
        pPartner->init();
        this->ui->stackedWidget->setCurrentWidget(pPartner);
    }
}
