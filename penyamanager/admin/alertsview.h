#ifndef ALERTSVIEW_H
#define ALERTSVIEW_H

#include <QWidget>
#include <QMessageBox>
#include <QListWidgetItem>

#include <objs/Member.h>
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
            explicit AlertsView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~AlertsView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            Int32 processData();
            //
            Int32 processOldYoungMembers();
            //
            Int32 fillAlertList();
            //
            Int32 fillOldInactiveMembers();
            //
            Int32 fillExpiredYoungMembers();
            //
            Int32 processDroppedMembers();

        private slots:
            void on_alertListWidget_itemClicked(QListWidgetItem *item);

        private:
            //
            Ui::AlertsView *ui;
            //
            CentralWidgetCallback m_switchCentralWidgetCallback;
    };
}

#endif // ALERTSVIEW_H
