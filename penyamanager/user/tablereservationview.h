#ifndef TABLERESERVATIONVIEW_H
#define TABLERESERVATIONVIEW_H

#include <QWidget>
#include <QDate>
#include <QAbstractButton>

#include <commons/IPartner.h>
#include <objs/Reservation.h>
#include <objs/ReservationItem.h>
#include <objs/Member.h>
#include "memberprofilegroupbox.h"

namespace Ui {
class TableReservationView;
}

namespace PenyaManager {
    //
    class TableReservationView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit TableReservationView(QWidget *parent, const CentralWidgetCallback &callback);
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
            void translateTable();
            //
            void initializeTableReservations();
            //
            void fillTableReservations(const MemberPtr &, const QDate &, ReservationType);
            //
            void fillOvenReservations(const MemberPtr &, const QDate &, ReservationType);
            //
            void fillFireplaceReservations(const MemberPtr &, const QDate &, ReservationType);
            //
            void fillReservationsItems(const MemberPtr &pMemberPtr, const ReservationListPtr &pReservationListPtr, const ReservationItemListPtr &pReservationItemListPtr,
                                       const ReservationItemListStatsPtr &pReservationItemListStatsPtr);
            //
            void prepareTableReservationMap(ReservationMap &, const ReservationListPtr &, const MemberPtr &, bool &);
            //
            void onReserved(ReservationItemType reservationItemType, QDate reservationDate, ReservationType reservationType);
            //
            void onCancel(ReservationItemType reservationItemType, QDate reservationDate, ReservationType reservationType);
            //
            void onTableItemGiven(int itemId, QString resultStr);
            //
            void reserveItems(int itemId, Uint32 guestNum);

        private slots:
            //
            void on_calendarWidget_clicked(const QDate &date);
            //
            void onReservedButton_clicked(int itemId);
            //
            void onCancelButton_clicked(int reservationId);
            //
            void on_lunchButton_clicked(bool checked);
            //
            void on_dinnerButton_clicked(bool checked);
            //
            void on_newinvoiceButton_clicked();
            //
            void on_invoicesPushButton_clicked();
            //
            void on_accountButton_clicked();
            //
            void on_depositsButton_clicked();
            //
            void on_exitButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_tablePushButton_clicked();
            //
            void on_ovenPushButton_clicked();
            //
            void on_fireplacePushButton_clicked();
    private:
            //
            Ui::TableReservationView    *ui;
            //
            Uint32                      m_currentPage;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // TABLERESERVATIONVIEW_H
