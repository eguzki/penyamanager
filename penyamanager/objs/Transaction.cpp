//

#include "Transaction.h"

namespace PenyaManager {
    //
    Transaction::Transaction()
    {
    }
    //
    Transaction::Transaction(Int32 id, Float amount, Uint64 date, Float balance, const QString &descr)
        :
            m_id(id),
            m_amount(amount),
            m_date(date),
            m_balance(balance),
            m_descr(descr)
    {
    }

}
