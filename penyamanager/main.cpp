//

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include <QLocale>

#include <QsLogDest.h>
#include <QsLog.h>

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

    // Fill views
    PenyaManager::LoginWindow *pLoginWindow = new PenyaManager::LoginWindow(NULL, &penyamanagerTranslator);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kLoginWindowKey, pLoginWindow);
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

    // run qt event loop
    int returnValue = app.exec();

    // destroy singletons
    PenyaManager::Singletons::Destroy();

    QLOG_INFO() << "Program exited";
    return returnValue;
}
