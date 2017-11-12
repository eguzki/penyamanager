//

#include "ReservationItem.h"

namespace PenyaManager
{
    //
    ReservationItem::ReservationItem()
    {
    }

    //
    QString getStringFromReservationTypeEnum(ReservationItemType e)
    {
        switch (e)
        {
            case ReservationItemType::LunchTableType: return "Table";
            case ReservationItemType::OvenType: return "Oven";
            case ReservationItemType::FireplaceType: return "Fireplace";
            default: return "Bad ReservationItemType";
        }
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

