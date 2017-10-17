//

#include "productitemwidget.h"
#include "ui_productitemwidget.h"

namespace PenyaManager {
    //
    ProductItemWidget::ProductItemWidget(QWidget *parent, const QPixmap &imageMap, const QString &text, Float price) :
        QWidget(parent),
        ui(new Ui::ProductItemWidget)
    {
        ui->setupUi(this);
        ui->imageQLabel->setPixmap(imageMap);
        ui->nameQLabel->setText(text);
        ui->priceQLabel->setText(QString("%1 €").arg(price, 0, 'f', 2));
    }
    //
    ProductItemWidget::~ProductItemWidget()
    {
        delete ui;
    }
}
