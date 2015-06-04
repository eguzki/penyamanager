#include <QApplication>

#include "constants.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "invoicewindow.h"
#include "depositwindow.h"
#include "accountview.h"
#include "tablereservationview.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    PenyaManager::Singletons::Create();

    // Fill views
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kLoginWindowKey, new PenyaManager::LoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMainWindowKey, new PenyaManager::MainWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceWindowKey, new PenyaManager::InvoiceWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kDepositsWindowKey, new PenyaManager::DepositWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAccountViewWindowKey, new PenyaManager::AccountView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kTableReservationViewWindowKey, new PenyaManager::TableReservationView);

    // entry point -> login window
    PenyaManager::IPartner* pLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kLoginWindowKey);
    pLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
