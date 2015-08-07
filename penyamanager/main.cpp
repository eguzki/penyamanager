//

#include <QApplication>
#include <QMessageBox>

#include "constants.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "invoicewindow.h"
#include "depositwindow.h"
#include "accountview.h"
#include "tablereservationview.h"
#include "invoicelistwindow.h"
#include "invoicedetailswindow.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    QSettings settings(PenyaManager::Constants::kOrganizationName, PenyaManager::Constants::kApplicationName);
    if (!settings.contains(PenyaManager::Constants::kResourcePathKey))
    {
        QMessageBox::critical(NULL, "Error", "Settings file not found. Call the stupid administrator and complain for incompetence");
        return 1;
    }

    PenyaManager::Singletons::Create(&settings);

    // Fill views
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kLoginWindowKey, new PenyaManager::LoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMainWindowKey, new PenyaManager::MainWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceWindowKey, new PenyaManager::InvoiceWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kDepositsWindowKey, new PenyaManager::DepositWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAccountViewWindowKey, new PenyaManager::AccountView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kTableReservationViewWindowKey, new PenyaManager::TableReservationView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceListWindoKey, new PenyaManager::InvoiceListWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceDetailsWindowKey, new PenyaManager::InvoiceDetailsWindow);

    // entry point -> login window
    PenyaManager::IPartner* pLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kLoginWindowKey);
    pLoginPartner->init();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
