#ifndef ADMINRESERVATIONSWINDOW_H
#define ADMINRESERVATIONSWINDOW_H

#include <QWidget>
#include <objs/Reservation.h>
#include <objs/ReservationItem.h>
#include <commons/IPartner.h>
#include <commons/utils.h>

namespace Ui {
    //
    class AdminReservationsWindow;
}

namespace PenyaManager {
    //
    class AdminReservationsWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminReservationsWindow(QWidget *parent = 0);
            //
            ~AdminReservationsWindow();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void initializeTable();
            //
            void initializeCalendar();
            //
            void fillReservations(const QDate &date, ReservationType reservationType);
            //
            void fillReservationsItems(const ReservationListPtr &pReservationListPtr, const ReservationItemListPtr &pReservationItemListPtr, Uint32 &rowCount);

        private slots:
            //
            void on_calendarWidget_clicked(const QDate &date);
            //
            void on_reservedButton_clicked(int itemId, ReservationItemType itemType);
            //
            void on_cancelButton_clicked(int reservationId, ReservationItemType itemType);
            //
            void on_lunchButton_clicked(bool checked);
            //
            void on_dinnerButton_clicked(bool checked);

        private:
            //
            Ui::AdminReservationsWindow *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // ADMINRESERVATIONSWINDOW_H
