#ifndef FAMILYITEMWIDGET_H
#define FAMILYITEMWIDGET_H

#include <QWidget>

namespace Ui {
class FamilyItemWidget;
}

namespace PenyaManager {
    //
    class FamilyItemWidget : public QWidget
    {
        Q_OBJECT

        public:
            //
            FamilyItemWidget(QWidget *parent, const QPixmap &imageMap, const QString &text);
            //
            ~FamilyItemWidget();

        private:
            //
            Ui::FamilyItemWidget *ui;
    };
}

#endif // FAMILYITEMWIDGET_H
