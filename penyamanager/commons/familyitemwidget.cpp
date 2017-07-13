//

#include "familyitemwidget.h"
#include "ui_familyitemwidget.h"

namespace PenyaManager {
    //
    FamilyItemWidget::FamilyItemWidget(QWidget *parent, const QPixmap &imageMap, const QString &text) :
        QWidget(parent),
        ui(new Ui::FamilyItemWidget)
    {
        ui->setupUi(this);
        ui->imageQLabel->setPixmap(imageMap);
        ui->textQLabel->setText(text);
    }
    //
    FamilyItemWidget::~FamilyItemWidget()
    {
        delete ui;
    }
}
