//

#include <QDebug>
#include <QMessageBox>

#include "singletons.h"
#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

namespace PenyaManager {
    //
    AdminMainWindow::AdminMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AdminMainWindow)
    {
        ui->setupUi(this);

        this->connect(this->ui->actionExit, &QAction::triggered, std::bind(&AdminMainWindow::on_exit_button_triggered, this));
    }
    //
    AdminMainWindow::~AdminMainWindow()
    {
        delete ui;
    }
    //
    void AdminMainWindow::init()
    {
        if (!Singletons::m_pDAO->isOpen()) {
            QSqlError err = Singletons::m_pDAO->lastError();
            QMessageBox::critical(this, "Unable to initialize Database",
                    "Error initializing database: " + err.text());
            qApp->exit(0);
            return;
        }

        show();
    }
    //
    void AdminMainWindow::on_exit_button_triggered()
    {
        this->hide();
        // call admin main window
        IPartner* pAdminLoginPartner = Singletons::m_pParnetFinder->getPartner(Constants::kAdminLoginWindowKey);
        pAdminLoginPartner->init();
    }
}
