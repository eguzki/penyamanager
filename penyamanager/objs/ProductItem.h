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
            virtual ~ProductItem(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_nameEus;
            //
            QString             m_nameEs;
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
            ProductItemPtr          m_item;
    };
    //
    typedef QSharedPointer<ProductItemResult> ProductItemResultPtr;
    //
    class ProductItemListResult
    {
        public:
            //
            ProductItemListResult();
            //
            virtual ~ProductItemListResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProductItemListPtr          m_list;
    };
    //
    typedef QSharedPointer<ProductItemListResult> ProductItemListResultPtr;

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
    //
    class ProductListStatsResult
    {
        public:
            //
            ProductListStatsResult();
            //
            virtual ~ProductListStatsResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProductListStatsPtr     m_stats;
    };
    //
    typedef QSharedPointer<ProductListStatsResult> ProductListStatsResultPtr;

    //
    class StockProductItem
    {
        public:
            //
            StockProductItem();
            //
            virtual ~StockProductItem(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_nameEus;
            //
            QString             m_nameEs;
            //
            QString             m_imagePath;
            //
            bool                m_active;
            //
            QDateTime           m_regDate;
            //
            QString             m_familyNameEus;
            //
            QString             m_familyNameEs;
            //
            Float               m_price;
            //
            QString             m_providerName;
            //
            Int32               m_stock;
    };
    //
    typedef QSharedPointer<StockProductItem> StockProductItemPtr;
    //
    typedef std::vector<StockProductItemPtr> StockProductItemList;
    //
    typedef QSharedPointer<StockProductItemList> StockProductItemListPtr;
    //
    class StockProductItemListResult
    {
        public:
            //
            StockProductItemListResult();
            //
            virtual ~StockProductItemListResult(){}

        public:
            //
            Int32                       m_error;
            //
            StockProductItemListPtr     m_list;
    };
    //
    typedef QSharedPointer<StockProductItemListResult> StockProductItemListResultPtr;
}

#endif // PRODUCTITEM_H
