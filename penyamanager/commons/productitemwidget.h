#ifndef PRODUCTITEMWIDGET_H
#define PRODUCTITEMWIDGET_H

#include <QWidget>
#include <commons/DataTypes.h>

namespace Ui {
class ProductItemWidget;
}

namespace PenyaManager {
    //
    class ProductItemWidget : public QWidget
    {
        Q_OBJECT

        public:
            //
            ProductItemWidget(QWidget *parent, const QPixmap &imageMap, const QString &text, Float price);
            //
            ~ProductItemWidget();

        private:
            //
            Ui::ProductItemWidget *ui;
    };
}

#endif // PRODUCTITEMWIDGET_H
