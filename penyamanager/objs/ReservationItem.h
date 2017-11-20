#ifndef RESERVATIONITEMS_H
#define RESERVATIONITEMS_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    enum class ReservationItemType
    {
        LunchTableType,
        OvenType,
        FireplaceType
    };
    //
    QString GetStringFromReservationItemTypeEnum(ReservationItemType e, bool tr = false);

    //
    class ReservationItem
    {
        public:
            //
            ReservationItem();
            //
            virtual ~ReservationItem(){}

        public:
            //
            Int32                   m_idItem;
            //
            QString                 m_itemName;
            //
            Uint16                  m_guestNum;
            //
            ReservationItemType     m_itemType;
    };

    //
    typedef QSharedPointer<ReservationItem> ReservationItemPtr;
    //
    typedef std::vector<ReservationItemPtr> ReservationItemList;
    //
    typedef QSharedPointer<ReservationItemList> ReservationItemListPtr;
    //
    class ReservationItemListResult
    {
        public:
            //
            ReservationItemListResult();
            //
            virtual ~ReservationItemListResult(){}

        public:
            //
            Int32                   m_error;
            //
            ReservationItemListPtr  m_list;
    };
    //
    typedef QSharedPointer<ReservationItemListResult> ReservationItemListResultPtr;
    //
    class ReservationListStats
    {
        public:
            //
            ReservationListStats();
            //
            ReservationListStats(Int32 totalNum);
            //
            virtual ~ReservationListStats(){}

        public:
            //
            Int32                   m_totalNum;
    };
    //
    typedef QSharedPointer<ReservationListStats> ReservationListStatsPtr;
    //
    class ReservationItemListStats
    {
        public:
            //
            ReservationItemListStats();
            //
            virtual ~ReservationItemListStats(){}

        public:
            //
            Int32                   m_error;
            //
            ReservationListStatsPtr  m_listStats;
    };
    //
    typedef QSharedPointer<ReservationItemListStats> ReservationItemListStatsPtr;
}

#endif // RESERVATIONITEMS_H
