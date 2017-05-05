//


#include "InvoiceProductItem.h"

namespace PenyaManager
{
    //
    InvoiceProductItem::InvoiceProductItem()
    {
    }

    //
    InvoiceProductItem::InvoiceProductItem(Int32 productId, QString productName, QString imagePath, Float priceperunit, Uint32 count)
        :
            m_productId(productId),
            m_productname(productName),
            m_imagePath(imagePath),
            m_priceperunit(priceperunit),
            m_count(count)
    {
    }
    //
    InvoiceProductItemStats::InvoiceProductItemStats()
    {
    }

    //
    InvoiceProductItemStats::InvoiceProductItemStats(Uint32 totalProducts)
        :
            m_totalProducts(totalProducts)
    {
    }
    //
    InvoiceProductItemListResult::InvoiceProductItemListResult()
        :
            m_error(0)
    {}
}
