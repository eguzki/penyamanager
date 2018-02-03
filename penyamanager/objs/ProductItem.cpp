//

#include "ProductItem.h"

namespace PenyaManager
{
    //
    ProductItem::ProductItem()
    {
    }
    //
    ProductListStats::ProductListStats()
    {
    }
    //
    ProductListStats::ProductListStats(Uint32 totalNumProducts)
        :
            m_totalNumProducts(totalNumProducts)
    {
    }
    //
    ProductItemResult::ProductItemResult()
        :
            m_error(0)
    {
    }
    //
    ProductItemListResult::ProductItemListResult()
        :
            m_error(0)
    {
    }
    //
    ProductListStatsResult::ProductListStatsResult()
        :
            m_error(0)
    {}
    //
    StockProductItem::StockProductItem()
    {}
    //
    StockProductItemListResult::StockProductItemListResult()
        :
            m_error(0)
    {}
}
