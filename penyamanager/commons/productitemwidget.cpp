#include "productitemwidget.h"
#include "ui_productitemwidget.h"

ProductItemWidget::ProductItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductItemWidget)
{
    ui->setupUi(this);
}

ProductItemWidget::~ProductItemWidget()
{
    delete ui;
}
