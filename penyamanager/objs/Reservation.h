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
            Int32               m_memberUsername;
            //
            QString             m_memberName;
            //
            QString             m_memberSurname;
            //
            Int32               m_idMember;
            //
            Uint16              m_guestNum;
            //
            bool                m_isAdmin;
    };

    //
    typedef QSharedPointer<Reservation> ReservationPtr;
    //
    typedef std::vector<ReservationPtr> ReservationList;
    //
    typedef QSharedPointer<ReservationList> ReservationListPtr;
    //
    typedef std::map<Uint32, ReservationPtr> ReservationMap;
}

#endif // RESERVATIONS_H
