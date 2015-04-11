#include <QApplication>

#include "singletons.h"
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle("windows");
    QApplication a(argc, argv);

    PenyaManager::Singletons::Create();

    PenyaManager::MainWindow mainWindow;
    PenyaManager::LoginWindow loginWindow;

    mainWindow.setParner(&loginWindow);
    loginWindow.setParner(&mainWindow);

    loginWindow.start();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
