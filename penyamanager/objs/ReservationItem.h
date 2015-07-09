#ifndef RESERVATIONITEMS_H
#define RESERVATIONITEMS_H

#include <QString>
#include <QDateTime>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    enum class ReservationItemType
    {
        LunchTableType,
        OvenType,
        FireplaceType
    };

    QString getStringFromReservationTypeEnum(ReservationItemType e);

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
    typedef std::shared_ptr<ReservationItem> ReservationItemPtr;
    //
    typedef std::vector<ReservationItemPtr> ReservationItemList;
    //
    typedef std::shared_ptr<ReservationItemList> ReservationItemListPtr;
}

#endif // RESERVATIONITEMS_H
