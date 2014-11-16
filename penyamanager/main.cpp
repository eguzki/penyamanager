#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;

    mainWindow.setParner(&loginWindow);
    loginWindow.setParner(&mainWindow);

    loginWindow.show();

    return a.exec();
}
