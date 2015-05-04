//


#include "InvoiceProductItem.h"

namespace PenyaManager
{
    //
    InvoiceProductItem::InvoiceProductItem()
    {
    }

    //
    InvoiceProductItem::InvoiceProductItem(Int32 productId, QString productName, Float priceperunit, Uint32 count)
        :
            m_productId(productId),
            m_productname(productName),
            m_priceperunit(priceperunit),
            m_count(count)
    {
    }
}
