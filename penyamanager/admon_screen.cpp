#include "admon_screen.h"
#include "ui_admon_screen.h"

admon_screen::admon_screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admon_screen)
{
    ui->setupUi(this);
}

admon_screen::~admon_screen()
{
    delete ui;
}
