//
#include <qwidget.h>
#include "Transaction.h"

namespace PenyaManager {
    //
    QString getStringFromTransactionTypeEnum(TransactionType e)
    {
        switch (e)
        {
            case TransactionType::Invoice: return QWidget::tr("Invoice");
            case TransactionType::Deposit: return QWidget::tr("Deposit");
            case TransactionType::AccountPayment: return QWidget::tr("Account Payment");
            case TransactionType::DepositFix: return QWidget::tr("Deposit Fix");
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
    //
    TransactionResult::TransactionResult()
        :
            m_error(0)
    {}
    //
    TransactionListResult::TransactionListResult()
        :
            m_error(0)
    {}
    //
    TransactionListStatsResult::TransactionListStatsResult()
        :
            m_error(0)
    {}
}

