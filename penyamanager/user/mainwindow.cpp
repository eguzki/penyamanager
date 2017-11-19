//

#include <QMessageBox>
#include <QPainter>

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
    // Required to apply background-image stylesheet to QWidget
    void MainWindow::paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
    //
    void MainWindow::init()
    {
        switchCentralWidget(WindowKey::kLoginWindowKey);

        // To disable Full Screen, comment the line below. Que no la above.
        showFullScreen();
        // To disable windowed mode, comment the line below. Que sí, que la de abajo.
        // show();
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

