//

#include "Invoice.h"

namespace PenyaManager
{
    //
    Invoice::Invoice()
    {
    }

    //
    Invoice::Invoice(Int32 id, Int32 memberId, InvoiceState state, const QDateTime &date, Float total)
        :
            m_id(id),
            m_memberId(memberId),
            m_state(state),
            m_date(date),
            m_total(total)
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
    {
    }
}
