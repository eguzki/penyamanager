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
            typedef std::function<void(Int32)>  ReservationCallback;
            //
            void translateTable();
            //
            void initializeTable();
            //
            void initializeCalendar();
            //
            void fillReservations(const QDate &date, ReservationType reservationType);
            //
            void fillReservationsItems(
                    const ReservationListPtr &pReservationListPtr,
                    const ReservationItemListPtr &pReservationItemListPtr,
                    Uint32 &rowCount,
                    const ReservationCallback newReservationCallback,
                    const ReservationCallback updateRervationCallback);

        private slots:
            //
            void on_calendarWidget_clicked(const QDate &date);
            //
            void on_new_table_reservation_button_clicked(int itemId);
            //
            void on_update_table_reservation_button_clicked(int itemId);
            //
            void on_new_oven_reservation_button_clicked(int itemId);
            //
            void on_update_oven_reservation_button_clicked(int itemId);
            //
            void on_new_fireplace_reservation_button_clicked(int itemId);
            //
            void on_update_fireplace_reservation_button_clicked(int itemId);
            //
            void on_cancelButton_clicked(int reservationId, ReservationItemType itemType);
            //
            void on_midMorningButton_clicked(bool checked);
            //
            void on_lunchButton_clicked(bool checked);
            //
            void on_supperButton_clicked(bool checked);
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
