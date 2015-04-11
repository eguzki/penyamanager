//


#include "InvoiceProductItem.h"

namespace PenyaManager
{
    //
    InvoiceProductItem::InvoiceProductItem()
    {
    }

    //
    InvoiceProductItem::InvoiceProductItem(QString productName, Float priceperunit, Uint32 count)
        :
            m_productname(productName),
            m_priceperunit(priceperunit),
            m_count(count)
    {
    }
}
