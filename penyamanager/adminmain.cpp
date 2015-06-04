#include <QApplication>

#include "admon_screen.h"
#include "adminmainwindow.h"
#include "adminloginwindow.h"
#include "slowpayersview.h"
#include "admininvoicelistview.h"
#include "admininvoicedetails.h"
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
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminInvoiceListWindowKey, new PenyaManager::AdminInvoiceListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminInvoiceDetailsWindowKey, new PenyaManager::AdminInvoiceDetails);

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kAdminLoginWindowKey);
    pAdminLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
