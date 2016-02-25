//

#include <QMessageBox>
#include <QsLog.h>

#include <commons/singletons.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace PenyaManager {

    //
    MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
    }
    //
    MainWindow::~MainWindow()
    {
        delete ui;
    }
    //
    void MainWindow::init()
    {
        switchCentralWidget(WindowKey::kLoginWindowKey);
        showFullScreen();
    }
    //
    void MainWindow::switchCentralWidget(WindowKey key)
    {
        if (this->ui->verticalLayout->count() > 0) {
            QWidget *pCurrentWidget = this->ui->verticalLayout->takeAt(0)->widget();
            pCurrentWidget->hide();
        }
        // call invoice list window
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(key);
        pPartner->init();
        // place widget
        this->ui->verticalLayout->addWidget(pPartner);
        pPartner->show();
    }
}

