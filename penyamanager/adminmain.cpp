#include <QApplication>

#include "admon_screen.h"
#include "adminmainwindow.h"
#include "adminloginwindow.h"
#include "slowpayersview.h"
#include "constants.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    PenyaManager::Singletons::Create();
    PenyaManager::AdminMainWindow adminMainWindow;

    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kAdminLoginWindowKey, new PenyaManager::AdminLoginWindow(&adminMainWindow));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kAdminMemberInfoWindow, new PenyaManager::admon_screen);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kAdminSlowPayersWindowKey, new PenyaManager::SlowPayersView);

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::Constants::kAdminLoginWindowKey);
    pAdminLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
