#include "providermanagerview.h"
#include "ui_providermanagerview.h"

ProviderManagerView::ProviderManagerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProviderManagerView)
{
    ui->setupUi(this);
}

ProviderManagerView::~ProviderManagerView()
{
    delete ui;
}
