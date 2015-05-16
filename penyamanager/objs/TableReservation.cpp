//

#include "TableReservation.h"

namespace PenyaManager
{
    //
    TableReservation::TableReservation()
    {
    }

    //
    TableReservation::TableReservation(Int32 reservationId, Int32 idTable, const QString &memberName, const QString &memberSurname, Uint32 idMember, Uint16 guestNum)
        :
            m_reservationId(reservationId),
            m_idTable(idTable),
            m_memberName(memberName),
            m_memberSurname(memberSurname),
            m_idMember(idMember),
            m_guestNum(guestNum)
    {
    }
}
