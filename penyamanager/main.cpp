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
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kLoginWindowKey, new PenyaManager::LoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kMainWindowKey, new PenyaManager::MainWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kInvoiceWindowKey, new PenyaManager::InvoiceWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kDepositsWindowKey, new PenyaManager::DepositWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kAccountViewWindowKey, new PenyaManager::AccountView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::Constants::kTableReservationViewWindowKey, new PenyaManager::TableReservationView);

    // entry point -> login window
    PenyaManager::IPartner* pLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::Constants::kLoginWindowKey);
    pLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
