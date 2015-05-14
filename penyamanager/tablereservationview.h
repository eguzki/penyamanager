#ifndef TABLERESERVATIONVIEW_H
#define TABLERESERVATIONVIEW_H

#include <QWidget>
#include <QDate>
#include <QAbstractButton>

#include "objs/TableReservation.h"
#include "objs/Member.h"
#include "IPartner.h"

namespace Ui {
class TableReservationView;
}

namespace PenyaManager {
    //
    typedef std::map<Uint32, TableReservationPtr> TableReservationMap;
    //
    class TableReservationView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit TableReservationView(QWidget *parent = 0);
            //
            ~TableReservationView();
            //
            void init();

        private:
            //
            void fillMemberProfile(const MemberPtr &);
            //
            void initializeTableReservations(const MemberPtr &);
            //
            void fillTableReservations(const MemberPtr &, const QDate &, ReservationType);
            //
            void prepareTableReservationMap(TableReservationMap &, const TableReservationListPtr &, const MemberPtr &, bool &);

        private slots:
            //
            void on_backButton_clicked();
            //
            void on_reservationType_toggled(int, bool);
            //
            void on_calendarWidget_clicked(const QDate &date);
            //
            void on_reservedButton_clicked(int tableId);
            //
            void on_cancelButton_clicked(int reservationId);

    private:
            //
            Ui::TableReservationView *ui;
    };
}

#endif // TABLERESERVATIONVIEW_H
