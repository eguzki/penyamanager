//

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include <commons/constants.h>
#include <commons/logging.h>
#include <commons/IPartner.h>
#include <commons/singletons.h>
#include <commons/utils.h>
#include <user/mainwindow.h>
#include <user/memberdashboardwindow.h>
#include <user/loginwindow.h>
#include <user/invoicewindow.h>
#include <user/depositwindow.h>
#include <user/accountview.h>
#include <user/tablereservationview.h>
#include <user/invoicelistwindow.h>
#include <user/invoicedetailswindow.h>

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    // Main QApplication object
    QApplication app(argc, argv);

    // Settings
    QSettings settings(PenyaManager::Constants::kOrganizationName, PenyaManager::Constants::kApplicationName);
    
    PenyaManager::PenyaManagerLoggerPtr pLogger = PenyaManager::NewLoggerInstance(&settings,"penyamanager");

    if (!settings.contains(PenyaManager::Constants::kResourcePathKey))
    {
        pLogger->Error(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kMain, "Settings file not found. Call the stupid administrator and complain for incompetence");
        QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Settings file not found. Call the stupid administrator and complain for incompetence"));
        return 1;
    }

    pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kMain, "Init");

    // Singletons initialization
    // Includes ddbb connection
    PenyaManager::Singletons::Create(&settings, pLogger);

    if (!PenyaManager::Singletons::m_pDAO->isOpen()) {
        PenyaManager::Singletons::m_pLogger->Error(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kMain, "Database connection failed");
        QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Database connection failed. Call the stupid administrator and complain for incompetence"));
        return 1;
    }

    // Translators
    QTranslator penyamanagerTranslator;
    // Initial dictionary
    penyamanagerTranslator.load(PenyaManager::Singletons::m_translationManager.getTranslationFile());
    app.installTranslator(&penyamanagerTranslator);

    PenyaManager::MainWindow mainWindow;
    // central widgets need mainwindow callback to call each other
    PenyaManager::CentralWidgetCallback mainWindowSwitchCallback = std::bind(&PenyaManager::MainWindow::switchCentralWidget, &mainWindow, _1);
    // Fill views
    PenyaManager::LoginWindow *pLoginWindow = new PenyaManager::LoginWindow(&mainWindow, &penyamanagerTranslator, mainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kLoginWindowKey, pLoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMemberDashboardWindowKey, new PenyaManager::MemberDashboardWindow(&mainWindow, mainWindowSwitchCallback));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceWindowKey, new PenyaManager::InvoiceWindow(&mainWindow, mainWindowSwitchCallback));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kDepositsWindowKey, new PenyaManager::DepositWindow(&mainWindow, mainWindowSwitchCallback));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAccountViewWindowKey, new PenyaManager::AccountView(&mainWindow, mainWindowSwitchCallback));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kTableReservationViewWindowKey, new PenyaManager::TableReservationView(&mainWindow, mainWindowSwitchCallback));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceListWindoKey, new PenyaManager::InvoiceListWindow(&mainWindow, mainWindowSwitchCallback));
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceDetailsWindowKey, new PenyaManager::InvoiceDetailsWindow(&mainWindow, mainWindowSwitchCallback));

    mainWindow.init();

    // run qt event loop
    int returnValue = app.exec();

    // destroy singletons
    PenyaManager::Singletons::Destroy();

    pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kMain, "Exit");
    return returnValue;
}
