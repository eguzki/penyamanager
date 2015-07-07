//

#include "Transaction.h"

namespace PenyaManager {
    //
    QString getStringFromTransactionTypeEnum(TransactionType e)
    {
        switch (e)
        {
            case TransactionType::Invoice: return "Invoice";
            case TransactionType::Deposit: return "Deposit";
            case TransactionType::AccountPayment: return "AccountPayment";
            default: return "Bad TransactionType";
        }
    }
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
    //
    TransactionListStats::TransactionListStats()
        :
            m_totalNumTransactions(0),
            m_totalInvoices(0.0),
            m_totalDeposits(0.0),
            m_totalBankCharges(0.0)
    {
    }

}
