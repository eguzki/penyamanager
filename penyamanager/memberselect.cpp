#include "memberselect.h"
#include "ui_memberselect.h"
#include "admon_screen.h"
#include "dao.h"
#include "singletons.h"

memberselect::memberselect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberselect)
{
    ui->setupUi(this);
}

memberselect::~memberselect()
{
    delete ui;
}



void memberselect::on_buttonBox_accepted()
{
    this->userid=this->ui->memberSelect->toPlainText().toInt();
}
