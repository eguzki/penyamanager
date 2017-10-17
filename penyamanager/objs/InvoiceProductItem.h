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
            InvoiceProductItem(Int32 productId, QString productName, QString imagePath, Float priceperunit, Uint32 count);
            //
            virtual ~InvoiceProductItem(){}

        public:
            //
            Int32               m_productId;
            //
            QString             m_productname;
            //
            QString             m_imagePath;
            //
            Float               m_priceperunit;
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
            InvoiceProductItemStats(Uint32 totalProducts);
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
}

#endif // INVOICEPRODUCTITEM_H
