//


#include "InvoiceProductItem.h"

namespace PenyaManager
{
    //
    InvoiceProductItem::InvoiceProductItem()
    {
    }

    //
    InvoiceProductItemStats::InvoiceProductItemStats()
        :
            m_totalProducts(0),
            m_totalAmount(0.0)
    {
    }

    //
    InvoiceProductItemStats::InvoiceProductItemStats(Uint32 totalProducts, Float totalAmount)
        :
            m_totalProducts(totalProducts),
            m_totalAmount(totalAmount)
    {
    }
    //
    InvoiceProductItemListResult::InvoiceProductItemListResult()
        :
            m_error(0)
    {}
    //
    InvoiceProductItemStatsResult::InvoiceProductItemStatsResult()
        :
            m_error(0)
    {}
    //
    InvoiceProductItemCounterStats::InvoiceProductItemCounterStats()
        :
            m_totalProducts(0)
    {}
    //
    InvoiceProductItemCounterStats::InvoiceProductItemCounterStats(Uint32 totalProducts)
        :
            m_totalProducts(totalProducts)
    {}
    //
    InvoiceProductItemCounterStatsResult::InvoiceProductItemCounterStatsResult()
        :
            m_error(0)
    {}
}
