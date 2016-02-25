#ifndef SLOWPAYERSVIEW_H
#define SLOWPAYERSVIEW_H

#include <QWidget>

#include <commons/IPartner.h>

namespace Ui {
class SlowPayersView;
}

namespace PenyaManager {
    //
    class SlowPayersView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit SlowPayersView(QWidget *parent = 0);
            //
            ~SlowPayersView();
            //
            void init();
            //
            void retranslate();

    private slots:
            //
            void on_csvPushButton_clicked();
            //
            void on_resetAccountsPushButton_clicked();

    private:
            //
            void translateTable();
            //
            void fillSlowPayersData();
            //
            void initializeTable();

        private:
            //
            Ui::SlowPayersView *ui;
    };
}

#endif // SLOWPAYERSVIEW_H
