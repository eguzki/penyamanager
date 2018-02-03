//

#include "Invoice.h"

namespace PenyaManager
{
    //
    Invoice::Invoice()
    {
    }
    //
    InvoiceListStats::InvoiceListStats()
    {
    }
    //
    InvoiceListStats::InvoiceListStats(Uint32 totalNumInvoices, Float totalAmount)
        :
            m_totalNumInvoices(totalNumInvoices),
            m_totalAmount(totalAmount)
    {}
    //
    InvoiceResult::InvoiceResult()
        :
            m_error(0)
    {}
    //
    InvoiceListResult::InvoiceListResult()
        :
            m_error(0)
    {}
    //
    InvoiceListStatsResult::InvoiceListStatsResult()
        :
            m_error(0)
    {}
}
