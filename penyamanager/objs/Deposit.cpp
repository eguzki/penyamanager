//

#include "Deposit.h"

namespace PenyaManager
{
    //
    Deposit::Deposit()
    {
    }

    //
    Deposit::Deposit(Int32 id, Int32 memberId, DepositState state, const QDateTime &date, Float total, const QString &descr)
        :
            m_id(id),
            m_memberId(memberId),
            m_state(state),
            m_date(date),
            m_total(total),
            m_descr(descr)
    {
    }
}
