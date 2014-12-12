#include "loginwindow.h"
#include "ui_loginwindow.h"

namespace PenyaManager {

LoginWindow::LoginWindow(QWidget *parent) :
    IPartner(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

//
LoginWindow::~LoginWindow()
{
    delete ui;
}

//
void LoginWindow::start()
{
    init();
}

void LoginWindow::init()
{
    showFullScreen();
}

void LoginWindow::setParner(IPartner *partner) {
    if(partner == 0)
        return;

    connect(this->ui->loginButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(this->ui->loginButton, SIGNAL(clicked()), partner, SLOT(init()));

}
}
