#ifndef TABLERESERVATIONVIEW_H
#define TABLERESERVATIONVIEW_H

#include <QWidget>
#include <QDate>
#include <QAbstractButton>

#include "memberprofilegroupbox.h"
#include "objs/Reservation.h"
#include "objs/ReservationItem.h"
#include "objs/Member.h"
#include "IPartner.h"

namespace Ui {
class TableReservationView;
}

namespace PenyaManager {
    //
    typedef std::map<Uint32, ReservationPtr> ReservationMap;
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
            //
            void retranslate();

        private:
            //
            void initializeTable();
            //
            void initializeTableReservations(const MemberPtr &);
            //
            void fillTableReservations(const MemberPtr &, const QDate &, ReservationType);
            //
            void fillReservationsItems(const MemberPtr &pMemberPtr, const ReservationListPtr &pReservationListPtr, const ReservationItemListPtr &pReservationItemListPtr, Uint32 &rowCount);
            //
            void prepareTableReservationMap(ReservationMap &, const ReservationListPtr &, const MemberPtr &, bool &);

        private slots:
            //
            void on_backButton_clicked();
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
            Ui::TableReservationView *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
    };
}

#endif // TABLERESERVATIONVIEW_H
