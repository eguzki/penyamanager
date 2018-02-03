//

#include "productitemwidget.h"
#include "ui_productitemwidget.h"

namespace PenyaManager {
    //
    ProductItemWidget::ProductItemWidget(QWidget *parent, const QPixmap &imageMap, const QString &text, Float price) :
        QWidget(parent),
        ui(new Ui::ProductItemWidget)
    {
        UNUSEDPARAMETER(price);
        ui->setupUi(this);
        ui->imageQLabel->setPixmap(imageMap);
        ui->nameQLabel->setText(text);
    }
    //
    ProductItemWidget::~ProductItemWidget()
    {
        delete ui;
    }
}
