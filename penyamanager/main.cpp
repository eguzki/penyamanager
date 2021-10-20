//

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

#include <commons/constants.h>
#include <commons/logging.h>
#include <commons/singletons.h>
#include <commons/guiutils.h>
#include <commons/inactivityeventfilter.h>
#include <user/mainwindow.h>

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
        pLogger->Error(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kMain, "Settings file not found. Call the stupid administrator and complain for incompetence");
        QMessageBox qMsgBox(QMessageBox::Critical, QString(), QObject::tr("Settings file not found. Call the stupid administrator and complain for incompetence"), QMessageBox::Ok, NULL, Qt::FramelessWindowHint);
        qMsgBox.exec();
        return 1;
    }

    pLogger->Info(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kMain, "Init");

    QTimer *pInactivityTimer = new QTimer(NULL);
    pInactivityTimer->setInterval(PenyaManager::Constants::kInactivityTimeoutSec * 1000);

    // Singletons initialization
    // Includes ddbb connection
    PenyaManager::Singletons::Create(&settings, pLogger, pInactivityTimer);

    if (!PenyaManager::Singletons::m_pDAO->isOpen()) {
        PenyaManager::Singletons::m_pLogger->Error(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kMain, "Database connection failed");
        QMessageBox qMsgBox(QMessageBox::Critical, QString(), QObject::tr("Database connection failed. Call the stupid administrator and complain for incompetence"), QMessageBox::Ok, NULL, Qt::FramelessWindowHint);
        qMsgBox.exec();
        return 1;
    }

    // Translators
    QTranslator penyamanagerTranslator;
    // Initial dictionary
    penyamanagerTranslator.load(PenyaManager::Singletons::m_pTranslationManager->getTranslationFile());
    app.installTranslator(&penyamanagerTranslator);

    PenyaManager::InactivityEventFilter inactivityEventFilter(PenyaManager::Singletons::m_pInactivityTimer);
    app.installEventFilter(&inactivityEventFilter);

    PenyaManager::MainWindow mainWindow(NULL, &penyamanagerTranslator);

    mainWindow.init();
    // To disable Full Screen, comment the line below.
    mainWindow.showFullScreen();
    // To disable windowed mode, comment the line below.
    //mainWindow.show();

    // run qt event loop
    int returnValue = app.exec();

    // destroy singletons
    PenyaManager::Singletons::Destroy();

    pLogger->Info(PenyaManager::Constants::kNoUserId, PenyaManager::LogAction::kMain, "Exit");
    return returnValue;
}
