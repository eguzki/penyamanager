#include <QApplication>

#include "adminloginwindow.h"
#include "constants.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    PenyaManager::Singletons::Create();
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kAdminLoginWindowKey, new PenyaManager::AdminLoginWindow);

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::Constants::kAdminLoginWindowKey);
    pAdminLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
