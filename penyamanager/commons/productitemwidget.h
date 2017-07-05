#ifndef PRODUCTITEMWIDGET_H
#define PRODUCTITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ProductItemWidget;
}

class ProductItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductItemWidget(QWidget *parent = 0);
    ~ProductItemWidget();

private:
    Ui::ProductItemWidget *ui;
};

#endif // PRODUCTITEMWIDGET_H
