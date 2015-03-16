#include "families.h"
#include "ui_families.h"

families::families(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::families)
{
    ui->setupUi(this);
}

families::~families()
{
    delete ui;
}
