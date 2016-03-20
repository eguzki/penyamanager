//

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include <QLocale>
#include <QsLogDest.h>
#include <QsLog.h>

#include <commons/constants.h>
#include <commons/IPartner.h>
#include <commons/singletons.h>
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
    if (!settings.contains(PenyaManager::Constants::kResourcePathKey))
    {
        QMessageBox::critical(NULL, "Error", "Settings file not found. Call the stupid administrator and complain for incompetence");
        return 1;
    }

    // LOGGING
    // init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    // set minimum log level and file name
    logger.setLoggingLevel(QsLogging::InfoLevel);
    const QString sLogPath(QDir(app.applicationDirPath()).filePath("penyamanager.log"));

    // Create log destinations
    QsLogging::DestinationPtr fileDestination( QsLogging::DestinationFactory::MakeFileDestination(
                sLogPath,
                QsLogging::LogRotationOption::EnableLogRotation,
                QsLogging::MaxSizeBytes(PenyaManager::Constants::kLogMaxSizeBytes)
                ));
    // set log destinations on the logger
    logger.addDestination(fileDestination);

    QLOG_INFO() << "Program started";

    // Singletons initialization
    // Includes ddbb connection
    PenyaManager::Singletons::Create(&settings);

    if (!PenyaManager::Singletons::m_pDAO->isOpen()) {
        QLOG_ERROR() << QString("[FATAL] Database connection failed");
        QMessageBox::critical(NULL, "Error", "Database connection failed. Call the stupid administrator and complain for incompetence");
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

    QLOG_INFO() << "Program exited";
    return returnValue;
}
