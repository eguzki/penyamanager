//

#include <QObject>

#include "ReservationItem.h"

namespace PenyaManager
{
    //
    ReservationItem::ReservationItem()
    {
    }

    //
    QString GetStringFromReservationItemTypeEnum(ReservationItemType e, bool translate)
    {
        switch (e)
        {
            case ReservationItemType::LunchTableType: return translate?(QObject::tr("table")):("table");
            case ReservationItemType::OvenType: return translate?(QObject::tr("oven")):("oven");
            case ReservationItemType::FireplaceType: return translate?(QObject::tr("fireplace")):("fireplace");
        }
        return "Bad ReservationItemType";
    }
    //
    ReservationItemListResult::ReservationItemListResult()
        :
            m_error(0)
    {}
    //
    ReservationItemListStats::ReservationItemListStats()
        :
            m_error(0)
    {}
    //
    ReservationListStats::ReservationListStats()
        :
            m_totalNum(0)
    {}
    //
    ReservationListStats::ReservationListStats(Int32 totalNum)
        :
            m_totalNum(totalNum)
    {}
}

