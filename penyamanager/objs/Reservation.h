#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    enum class ReservationType
    {
        Lunch,
        Dinner
    };
    //
    class Reservation
    {
        public:
            //
            Reservation();
            //
            virtual ~Reservation(){}

        public:
            //
            Int32               m_reservationId;
            //
            Int32               m_idItem;
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
    typedef QSharedPointer<Reservation> ReservationPtr;
    //
    typedef std::vector<ReservationPtr> ReservationList;
    //
    typedef QSharedPointer<ReservationList> ReservationListPtr;
}

#endif // RESERVATIONS_H
