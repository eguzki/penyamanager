//

#include "Transaction.h"

namespace PenyaManager {
    //
    Transaction::Transaction()
    {
    }
    //
    Transaction::Transaction(TransactionType type, Int32 memberId, Float amount, const QDateTime& date, Float balance, const QString &descr)
        :
            m_type(type),
            m_memberId(memberId),
            m_amount(amount),
            m_date(date),
            m_balance(balance),
            m_descr(descr)
    {
    }

}
