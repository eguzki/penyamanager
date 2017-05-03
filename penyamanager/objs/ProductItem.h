#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>

#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    class ProductItem
    {
        public:
            //
            ProductItem();
            //
            ProductItem(const QString &name, const QString &imagePath, bool active, const QDateTime &regDate, Int32 familyId, Float price, Int32 providerId, Int32 stock);
            //
            virtual ~ProductItem(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_name;
            //
            QString             m_imagePath;
            //
            bool                m_active;
            //
            QDateTime           m_regDate;
            //
            Int32               m_familyId;
            //
            Float               m_price;
            //
            Int32               m_providerId;
            //
            Int32               m_stock;
    };

    //
    typedef QSharedPointer<ProductItem> ProductItemPtr;
    //
    typedef std::vector<ProductItemPtr> ProductItemList;
    //
    typedef QSharedPointer<ProductItemList> ProductItemListPtr;
    //
    class ProductItemResult
    {
        public:
            //
            ProductItemResult();
            //
            virtual ~ProductItemResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProductItemListPtr      m_list;
    };
    //
    typedef QSharedPointer<ProductItemResult> ProductItemResultPtr;

    //
    class ProductListStats
    {
        public:
            //
            ProductListStats();
            //
            ProductListStats(Uint32 totalNumProducts);
            //
            virtual ~ProductListStats(){}

        public:
            //
            Uint32              m_totalNumProducts;
    };

    //
    typedef QSharedPointer<ProductListStats> ProductListStatsPtr;
}

#endif // PRODUCTITEM_H
