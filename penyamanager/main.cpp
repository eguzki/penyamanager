#include <QApplication>

#include "singletons.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "admon_screen.h"

int main(int argc, char *argv[])
{
    PenyaManager::Singletons::Create();

    QApplication::setStyle("windows");
    QApplication a(argc, argv);
    PenyaManager::MainWindow mainWindow;
    PenyaManager::LoginWindow loginWindow;
    PenyaManager::admon_screen adminWindow;

    mainWindow.setParner(&loginWindow);
    loginWindow.setParner(&mainWindow);
    mainWindow.setAdminParner(&adminWindow);
    adminWindow.setParner(&mainWindow);

    loginWindow.start();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
