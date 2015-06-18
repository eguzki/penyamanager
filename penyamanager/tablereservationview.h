#ifndef TABLERESERVATIONVIEW_H
#define TABLERESERVATIONVIEW_H

#include <QWidget>
#include <QDate>
#include <QAbstractButton>

#include "memberprofilegroupbox.h"
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
            void initializeTableReservations(const MemberPtr &);
            //
            void fillTableReservations(const MemberPtr &, const QDate &, ReservationType);
            //
            void prepareTableReservationMap(TableReservationMap &, const TableReservationListPtr &, const MemberPtr &, bool &);

        private slots:
            //
            void on_backButton_clicked();
            //
            void on_calendarWidget_clicked(const QDate &date);
            //
            void on_reservedButton_clicked(int tableId);
            //
            void on_cancelButton_clicked(int reservationId);
            //
            void on_lunchButton_clicked(bool checked);
            //
            void on_dinnerButton_clicked(bool checked);

    private:
            //
            Ui::TableReservationView *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
    };
}

#endif // TABLERESERVATIONVIEW_H
