#ifndef RESERVATIONITEMS_H
#define RESERVATIONITEMS_H

#include <QSharedPointer>
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
    typedef QSharedPointer<ReservationItem> ReservationItemPtr;
    //
    typedef std::vector<ReservationItemPtr> ReservationItemList;
    //
    typedef QSharedPointer<ReservationItemList> ReservationItemListPtr;
}

#endif // RESERVATIONITEMS_H
