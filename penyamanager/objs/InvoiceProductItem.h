#ifndef INVOICEPRODUCTITEM_H
#define INVOICEPRODUCTITEM_H

#include <QSharedPointer>
#include <QString>

#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    class InvoiceProductItem
    {
        public:
            //
            InvoiceProductItem();
            //
            virtual ~InvoiceProductItem(){}

        public:
            //
            Int32               m_productId;
            //
            QString             m_productnameEus;
            //
            QString             m_productnameEs;
            //
            QString             m_imagePath;
            // price per unit on closing invoice
            Float               m_pricePerUnit;
            // current price per unit
            Float               m_currentPricePerUnit;
            //
            Uint32              m_count;
    };

    //
    typedef QSharedPointer<InvoiceProductItem> InvoiceProductItemPtr;
    //
    typedef std::vector<InvoiceProductItemPtr> InvoiceProductItemList;
    //
    typedef QSharedPointer<InvoiceProductItemList> InvoiceProductItemListPtr;
    //
    class InvoiceProductItemListResult
    {
        public:
            //
            InvoiceProductItemListResult();
            //
            virtual ~InvoiceProductItemListResult(){}

        public:
            //
            Int32                       m_error;
            //
            InvoiceProductItemListPtr   m_list;
    };
    //
    typedef QSharedPointer<InvoiceProductItemListResult> InvoiceProductItemListResultPtr;

    //
    class InvoiceProductItemStats
    {
        public:
            //
            InvoiceProductItemStats();
            //
            InvoiceProductItemStats(Uint32 totalProducts, Float totalAmount);
            //
            virtual ~InvoiceProductItemStats(){}

        public:
            //
            Uint32              m_totalProducts;
    };

    //
    typedef QSharedPointer<InvoiceProductItemStats> InvoiceProductItemStatsPtr;
    //
    class InvoiceProductItemStatsResult
    {
        public:
            //
            InvoiceProductItemStatsResult();
            //
            virtual ~InvoiceProductItemStatsResult(){}

        public:
            //
            Int32                       m_error;
            //
            InvoiceProductItemStatsPtr  m_stats;
    };
    //
    typedef QSharedPointer<InvoiceProductItemStatsResult> InvoiceProductItemStatsResultPtr;

    //
    class InvoiceProductItemCounterStats
    {
        public:
            //
            InvoiceProductItemCounterStats();
            //
            virtual ~InvoiceProductItemCounterStats(){}

        public:
            //
            Uint32              m_totalProducts;
    };

    //
    typedef QSharedPointer<InvoiceProductItemCounterStats> InvoiceProductItemCounterStatsPtr;
    //
    class InvoiceProductItemCounterStatsResult
    {
        public:
            //
            InvoiceProductItemCounterStatsResult();
            //
            virtual ~InvoiceProductItemCounterStatsResult(){}

        public:
            //
            Int32                               m_error;
            //
            InvoiceProductItemCounterStatsPtr   m_stats;
    };
    //
    typedef QSharedPointer<InvoiceProductItemCounterStatsResult> InvoiceProductItemCounterStatsResultPtr;
}

#endif // INVOICEPRODUCTITEM_H
