#include <QApplication>
#include <QMessageBox>

#include "singletons.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "ddbbhelper.h"

int main(int argc, char *argv[])
{
    Singletons::Create();

    QApplication::setStyle("windows");
    QApplication a(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;

    mainWindow.setParner(&loginWindow);
    loginWindow.setParner(&mainWindow);

    // initialize the database
    
    if (!Singletons::m_db.isOpen()) {
        QSqlError err = Singletons::m_db.lastError();
        QMessageBox::critical(&mainWindow, "Unable to initialize Database",
                "Error initializing database: " + err.text());
        Singletons::Destroy();
        return 1;
    }

    loginWindow.showFullScreen();

    int returnValue = a.exec();

    Singletons::Destroy();
     
    return returnValue;
}
