//

#include "Invoice.h"

namespace PenyaManager
{
    //
    Invoice::Invoice()
    {
    }

    //
    Invoice::Invoice(Int32 id, Int32 memberId, InvoiceState state, Uint64 date, Float total, PaymentType payment)
        :
            m_id(id),
            m_memberId(memberId),
            m_state(state),
            m_date(date),
            m_total(total),
            m_payment(payment)
    {
    }
}
