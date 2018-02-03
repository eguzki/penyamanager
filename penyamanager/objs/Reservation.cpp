//

#include <QObject>

#include "Reservation.h"

namespace PenyaManager
{
    //
    Reservation::Reservation()
    {
    }
    //
    ReservationListResult::ReservationListResult()
        :
            m_error(0)
    {}
    //
    QString GetStringFromReservationTypeEnum(ReservationType e, bool translate)
    {
        switch (e)
        {
            case ReservationType::Lunch: return translate?(QObject::tr("lunch")):("lunch");
            case ReservationType::Dinner: return translate?(QObject::tr("dinner")):("dinner");
        }
        return "Bad ReservationType";
    }
}
