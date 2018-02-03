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
            m_totalProducts(0)
    {}
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
    InvoiceProductItemCounterStatsResult::InvoiceProductItemCounterStatsResult()
        :
            m_error(0)
    {}
}
