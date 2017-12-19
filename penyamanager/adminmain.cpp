//

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include <commons/IPartner.h>
#include <commons/constants.h>
#include <commons/singletons.h>
#include <commons/utils.h>
#include <commons/inactivityeventfilter.h>
#include <admin/adminmainwindow.h>
#include <admin/adminloginwindow.h>

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication app(argc, argv);

    // Settings
    QSettings settings(PenyaManager::Constants::kOrganizationName, PenyaManager::Constants::kApplicationName);

    PenyaManager::PenyaManagerLoggerPtr pLogger = PenyaManager::NewLoggerInstance(&settings, "penyamanageradmin");

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
    penyamanagerTranslator.load(PenyaManager::Singletons::m_pTranslationManager->getAdminTranslationFile());
    app.installTranslator(&penyamanagerTranslator);

    QTimer inactivityTimer(NULL);
    inactivityTimer.setInterval(PenyaManager::Constants::kAdminInactivityTimeoutSec * 1000);

    PenyaManager::InactivityEventFilter inactivityEventFilter(&inactivityTimer);
    app.installEventFilter(&inactivityEventFilter);

    PenyaManager::AdminMainWindow adminMainWindow(NULL, &inactivityTimer);

    PenyaManager::AdminLoginWindow *pLoginWindow = new PenyaManager::AdminLoginWindow(NULL, &adminMainWindow, &penyamanagerTranslator);
    PenyaManager::Singletons::m_pParnetFinder->addPartner(PenyaManager::WindowKey::kAdminLoginWindowKey, pLoginWindow);

    // entry point -> adminlogin window
    PenyaManager::IPartner* pAdminLoginPartner = PenyaManager::Singletons::m_pParnetFinder->getPartner(PenyaManager::WindowKey::kAdminLoginWindowKey);
    pAdminLoginPartner->init();
    pAdminLoginPartner->show();

    int returnValue = app.exec();

    PenyaManager::Singletons::Destroy();

    pLogger->Info(PenyaManager::Constants::kSystemUserId, PenyaManager::LogAction::kMain, "Exit");
    return returnValue;
}
