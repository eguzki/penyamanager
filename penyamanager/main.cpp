#include <QApplication>

#include "singletons.h"
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    PenyaManager::Singletons::Create();

    QApplication::setStyle("windows");
    QApplication a(argc, argv);
    PenyaManager::MainWindow mainWindow;
    PenyaManager::LoginWindow loginWindow;

    mainWindow.setParner(&loginWindow);
    loginWindow.setParner(&mainWindow);

    loginWindow.start();

    int returnValue = a.exec();

    PenyaManager::Singletons::Destroy();

    return returnValue;
}
