#include <QApplication>

#include "singletons.h"
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    Singletons::Create();

    QApplication::setStyle("windows");
    QApplication a(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;

    mainWindow.setParner(&loginWindow);
    loginWindow.setParner(&mainWindow);

    loginWindow.start();

    int returnValue = a.exec();

    Singletons::Destroy();

    return returnValue;
}
