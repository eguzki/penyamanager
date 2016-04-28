//

#include "ProviderInvoice.h"

namespace PenyaManager
{
    //
    ProviderInvoice::ProviderInvoice()
    {
    }

    //
    ProviderInvoiceListStats::ProviderInvoiceListStats()
    {
    }
    //
    ProviderInvoiceListStats::ProviderInvoiceListStats(Uint32 totalNumInvoices, Float totalAmount)
        :
            m_totalNumInvoices(totalNumInvoices),
            m_totalAmount(totalAmount)
    {
    }
}
