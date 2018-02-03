//

#include <QPainter>

#include <commons/singletons.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memberdashboardwindow.h"
#include "loginwindow.h"
#include "invoicewindow.h"
#include "depositwindow.h"
#include "accountview.h"
#include "tablereservationview.h"
#include "invoicelistwindow.h"
#include "invoicedetailswindow.h"

namespace PenyaManager {

    //
    MainWindow::MainWindow(QWidget *parent, QTranslator *pTranslator, QTimer *pInactivityTimer) :
        QWidget(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        // central widgets need mainwindow callback to call each other
        CentralWidgetCallback mainWindowSwitchCallback = std::bind(&MainWindow::switchCentralWidget, this, _1);
        // Fill views
        LoginWindow *pLoginWindow = new LoginWindow(this, pTranslator, pInactivityTimer, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kLoginWindowKey, pLoginWindow);
        this->ui->stackedWidget->addWidget(pLoginWindow);
        MemberDashboardWindow *pMemberDashboardWindow = new MemberDashboardWindow(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kMemberDashboardWindowKey, pMemberDashboardWindow);
        this->ui->stackedWidget->addWidget(pMemberDashboardWindow);
        InvoiceWindow *pInvoiceWindow = new InvoiceWindow(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kInvoiceWindowKey, pInvoiceWindow);
        this->ui->stackedWidget->addWidget(pInvoiceWindow);
        DepositWindow *pDepositWindow = new DepositWindow(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kDepositsWindowKey, pDepositWindow);
        this->ui->stackedWidget->addWidget(pDepositWindow);
        AccountView *pAccountView = new AccountView(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kAccountViewWindowKey, pAccountView);
        this->ui->stackedWidget->addWidget(pAccountView);
        TableReservationView *pTableReservationView = new TableReservationView(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kTableReservationViewWindowKey, pTableReservationView);
        this->ui->stackedWidget->addWidget(pTableReservationView);
        InvoiceListWindow *pInvoiceListWindow = new InvoiceListWindow(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kInvoiceListWindoKey, pInvoiceListWindow);
        this->ui->stackedWidget->addWidget(pInvoiceListWindow);
        InvoiceDetailsWindow *pInvoiceDetailsWindow = new InvoiceDetailsWindow(this, mainWindowSwitchCallback);
        Singletons::m_pParnetFinder->addPartner(WindowKey::kInvoiceDetailsWindowKey, pInvoiceDetailsWindow);
        this->ui->stackedWidget->addWidget(pInvoiceDetailsWindow);
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
    }
    //
    void MainWindow::switchCentralWidget(WindowKey key)
    {
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(key);
        pPartner->init();
        this->ui->stackedWidget->setCurrentWidget(pPartner);
    }
}

