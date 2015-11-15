//

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include <QsLogDest.h>
#include <QsLog.h>

#include "adminmainwindow.h"
#include "adminloginwindow.h"
#include "slowpayersview.h"
#include "admininvoicelistview.h"
#include "invoicedetailswidget.h"
#include "providermanagerview.h"
#include "adminnewprovider.h"
#include "stockmanagementwindow.h"
#include "familyitemmanagementwindow.h"
#include "adminproductitem.h"
#include "adminfamilyview.h"
#include "productexpensesview.h"
#include "providerinvoiceview.h"
#include "providerinvoicelistview.h"
#include "depositlistview.h"
#include "accountbalanceview.h"
#include "memberlistview.h"
#include "memberview.h"
#include "constants.h"
#include "IPartner.h"
#include "singletons.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
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
    const QString sLogPath(QDir(app.applicationDirPath()).filePath("penyamanageradmin.log"));

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
    penyamanagerTranslator.load(PenyaManager::Singletons::m_translationManager.getAdminTranslationFile());
    app.installTranslator(&penyamanagerTranslator);

    PenyaManager::AdminMainWindow adminMainWindow;

    PenyaManager::AdminLoginWindow *pLoginWindow = new PenyaManager::AdminLoginWindow(NULL, &adminMainWindow, &penyamanagerTranslator);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminLoginWindowKey, pLoginWindow);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminSlowPayersWindowKey, new PenyaManager::SlowPayersView);

    // central widgets need adminmainwindow callback to call each other
    PenyaManager::CentralWidgetCallback adminMainWindowSwitchCallback = std::bind(&PenyaManager::AdminMainWindow::switchCentralWidget, &adminMainWindow, _1);
    // instantiate adminmain widgets
    PenyaManager::AdminInvoiceListView *pAdminInvoiceListView = new PenyaManager::AdminInvoiceListView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminInvoiceListWindowKey, pAdminInvoiceListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kInvoiceDetailsWindowKey, new PenyaManager::InvoiceDetailsWidget);
    PenyaManager::ProviderManagerView *pProviderManagerView = new PenyaManager::ProviderManagerView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminProviderWindowKey, pProviderManagerView);
    PenyaManager::AdminNewProvider *pAdminNewProvider = new PenyaManager::AdminNewProvider(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminNewProviderKey, pAdminNewProvider);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kStockManagementWindowKey, new PenyaManager::StockManagementWindow);
    PenyaManager::FamilyItemManagementWindow *pFamilyItemManagementWindow = new PenyaManager::FamilyItemManagementWindow(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kFamilyItemManagementWindowKey, pFamilyItemManagementWindow);
    PenyaManager::AdminProductItem *pAdminProductItem = new PenyaManager::AdminProductItem(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminProductItemKey, pAdminProductItem);
    PenyaManager::AdminFamilyView *pAdminFamilyView = new PenyaManager::AdminFamilyView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminFamilyViewKey, pAdminFamilyView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kProductExpensesViewKey, new PenyaManager::ProductExpensesView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kProviderInvoiceViewKey, new PenyaManager::ProviderInvoiceView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kProviderInvoiceListViewKey, new PenyaManager::ProviderInvoiceListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminDepositListViewKey, new PenyaManager::DepositListView);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminAccountBalanceViewKey, new PenyaManager::AccountBalanceView);
    PenyaManager::MemberListView *pMemberListView = new PenyaManager::MemberListView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMemberListViewWindowKey, pMemberListView);
    PenyaManager::MemberView *pMemberView = new PenyaManager::MemberView(NULL, adminMainWindowSwitchCallback);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kMemberViewKey, pMemberView);

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kAdminLoginWindowKey);
    pAdminLoginPartner->init();

    int returnValue = app.exec();

    PenyaManager::Singletons::Destroy();

    QLOG_INFO() << "Program exited";
    return returnValue;
}
