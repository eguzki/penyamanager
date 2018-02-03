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
    //
    ProviderInvoiceListResult::ProviderInvoiceListResult()
        :
            m_error(0)
    {}
    //
    ProviderInvoiceListStatsResult::ProviderInvoiceListStatsResult()
        :
            m_error(0)
    {}
    //
    ProviderInvoiceResult::ProviderInvoiceResult()
        :
            m_error(0)
    {}
}
