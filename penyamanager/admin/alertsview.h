#ifndef ALERTSVIEW_H
#define ALERTSVIEW_H

#include <QWidget>
#include <QMessageBox>

#include <commons/IPartner.h>

namespace Ui {
    //
    class AlertsView;
}

namespace PenyaManager {
    //
    class AlertsView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AlertsView(QWidget *parent = 0);
            //
            ~AlertsView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            Ui::AlertsView *ui;
    };
}

#endif // ALERTSVIEW_H
