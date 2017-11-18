//

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include <commons/IPartner.h>
#include <commons/invoicedetailswidget.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include <commons/utils.h>
#include <admin/adminmainwindow.h>
#include <admin/adminloginwindow.h>
#include <admin/slowpayersview.h>
#include <admin/admininvoicelistview.h>
#include <admin/providermanagerview.h>
#include <admin/adminnewprovider.h>
#include <admin/stockmanagementwindow.h>
#include <admin/familyitemmanagementwindow.h>
#include <admin/adminproductitem.h>
#include <admin/adminfamilyview.h>
#include <admin/productexpensesview.h>
#include <admin/providerinvoiceview.h>
#include <admin/newproviderinvoiceview.h>
#include <admin/providerinvoicelistview.h>
#include <admin/depositlistview.h>
#include <admin/accountbalanceview.h>
#include <admin/memberlistview.h>
#include <admin/memberview.h>
#include <admin/adminreservationswindow.h>

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication app(argc, argv);

    // Settings
    QSettings settings(PenyaManager::Constants::kOrganizationName, PenyaManager::Constants::kApplicationName);
    if (!settings.contains(PenyaManager::Constants::kResourcePathKey))
    {
        QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Settings file not found. Call the stupid administrator and complain for incompetence"));
        return 1;
    }

    PenyaManager::PenyaManagerLoggerPtr pLogger = PenyaManager::NewLoggerInstance(&settings, "penyamanageradmin");

    pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kMain, "Init");

    // Singletons initialization
    // Includes ddbb connection
    PenyaManager::Singletons::Create(&settings, pLogger);

    if (!PenyaManager::Singletons::m_pDAO->isOpen()) {
        QLOG_ERROR() << QString("Database connection failed");
        QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Database connection failed. Call the stupid administrator and complain for incompetence"));
        return 1;
    }

    // Translators
    QTranslator penyamanagerTranslator;
    // Initial dictionary
    penyamanagerTranslator.load(PenyaManager::Singletons::m_translationManager.getAdminTranslationFile());
    app.installTranslator(&penyamanagerTranslator);

    PenyaManager::AdminMainWindow adminMainWindow;

    PenyaManager::AdminLoginWindow *pLoginWindow = new PenyaManager::AdminLoginWindow(NULL, &adminMainWindow, &penyamanagerTranslator);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminLoginWindowKey, pLoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminSlowPayersWindowKey, new PenyaManager::SlowPayersView);

    // central widgets need adminmainwindow callback to call each other
    PenyaManager::CentralWidgetCallback adminMainWindowSwitchCallback = std::bind(&PenyaManager::AdminMainWindow::switchCentralWidget, &adminMainWindow, _1);
    // instantiate adminmain widgets
    PenyaManager::AdminInvoiceListView *pAdminInvoiceListView = new PenyaManager::AdminInvoiceListView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminInvoiceListWindowKey, pAdminInvoiceListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceDetailsWindowKey, new PenyaManager::InvoiceDetailsWidget);
    PenyaManager::ProviderManagerView *pProviderManagerView = new PenyaManager::ProviderManagerView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminProviderWindowKey, pProviderManagerView);
    PenyaManager::AdminNewProvider *pAdminNewProvider = new PenyaManager::AdminNewProvider(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminNewProviderKey, pAdminNewProvider);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kStockManagementWindowKey, new PenyaManager::StockManagementWindow);
    PenyaManager::FamilyItemManagementWindow *pFamilyItemManagementWindow = new PenyaManager::FamilyItemManagementWindow(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kFamilyItemManagementWindowKey, pFamilyItemManagementWindow);
    PenyaManager::AdminProductItem *pAdminProductItem = new PenyaManager::AdminProductItem(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminProductItemKey, pAdminProductItem);
    PenyaManager::AdminFamilyView *pAdminFamilyView = new PenyaManager::AdminFamilyView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminFamilyViewKey, pAdminFamilyView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kProductExpensesViewKey, new PenyaManager::ProductExpensesView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kProviderInvoiceViewKey, new PenyaManager::ProviderInvoiceView);
    PenyaManager::NewProviderInvoiceView *pNewProviderInvoiceView = new PenyaManager::NewProviderInvoiceView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kNewProviderInvoiceViewKey, pNewProviderInvoiceView);
    PenyaManager::ProviderInvoiceListView *pProviderInvoiceListView = new PenyaManager::ProviderInvoiceListView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kProviderInvoiceListViewKey, pProviderInvoiceListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminDepositListViewKey, new PenyaManager::DepositListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminAccountBalanceViewKey, new PenyaManager::AccountBalanceView);
    PenyaManager::MemberListView *pMemberListView = new PenyaManager::MemberListView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMemberListViewWindowKey, pMemberListView);
    PenyaManager::MemberView *pMemberView = new PenyaManager::MemberView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMemberViewKey, pMemberView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminReservationViewKey, new PenyaManager::AdminReservationsWindow);

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kAdminLoginWindowKey);
    pAdminLoginPartner->init();
    pAdminLoginPartner->show();

    int returnValue = app.exec();

    PenyaManager::Singletons::Destroy();

    QLOG_INFO() << QString("[Exit]");
    return returnValue;
}
