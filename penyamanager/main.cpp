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
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::kLoginWindowKey, new PenyaManager::LoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::kMainWindowKey, new PenyaManager::MainWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::kInvoiceWindowKey, new PenyaManager::InvoiceWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::kDepositsWindowKey, new PenyaManager::DepositWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::kAccountViewWindowKey, new PenyaManager::AccountView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::kTableReservationViewWindowKey, new PenyaManager::TableReservationView);

    // entry point -> login window
    PenyaManager::IPartner* pLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::kLoginWindowKey);
    pLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
