#ifndef TABLERESERVATION_H
#define TABLERESERVATION_H

#include <QString>
#include <QDateTime>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    enum class ReservationType
    {
        Lunch,
        Dinner
    };
    //
    class TableReservation
    {
        public:
            //
            TableReservation();
            //
            TableReservation(Int32 reservationId, Int32 idTable, const QString &memberName, const QString &memberSurname, Uint32 idMember, Uint16 guestNum);
            //
            virtual ~TableReservation(){}

        public:
            //
            Int32               m_reservationId;
            //
            Int32               m_idTable;
            //
            QString             m_memberName;
            //
            QString             m_memberSurname;
            //
            Int32               m_idMember;
            //
            Uint16              m_guestNum;
    };

    //
    typedef std::shared_ptr<TableReservation> TableReservationPtr;
    //
    typedef std::vector<TableReservationPtr> TableReservationList;
    //
    typedef std::shared_ptr<TableReservationList> TableReservationListPtr;
}

#endif // TABLERESERVATION_H
