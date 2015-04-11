#include <QApplication>

#include "constants.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    PenyaManager::Singletons::Create();

    // entry point -> login window
    PenyaManager::IPartner* pLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::Constants::kLoginWindowKey);
    pLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
