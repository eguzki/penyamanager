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
            case TransactionType::AccountPayment: return "Account Payment";
            case TransactionType::DepositFix: return "Desposit Fix";
            default: return "Bad TransactionType";
        }
    }
    //
    Transaction::Transaction()
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
