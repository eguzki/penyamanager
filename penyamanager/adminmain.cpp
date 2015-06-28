#include <QApplication>

#include "admon_screen.h"
#include "adminmainwindow.h"
#include "adminloginwindow.h"
#include "slowpayersview.h"
#include "admininvoicelistview.h"
#include "invoicedetailswidget.h"
#include "providermanagerview.h"
#include "adminnewprovider.h"
#include "stockmanagementwindow.h"
#include "familyitemmanagementwindow.h"
#include "adminproductitem.h"
#include "adminfamilyview.h"
#include "constants.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    PenyaManager::Singletons::Create();
    PenyaManager::AdminMainWindow adminMainWindow;

    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminLoginWindowKey, new PenyaManager::AdminLoginWindow(&adminMainWindow));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminMemberInfoWindowKey, new PenyaManager::admon_screen);
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

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kAdminLoginWindowKey);
    pAdminLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
