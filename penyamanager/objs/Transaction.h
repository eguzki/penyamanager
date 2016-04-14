#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>

#include <commons/DataTypes.h>
#include <commons/constants.h>

namespace PenyaManager
{
    //
    enum class TransactionType
    {
        Invoice,
        Deposit,
        AccountPayment,
        DepositFix
    };

    QString getStringFromTransactionTypeEnum(TransactionType e);

    //
    class Transaction
    {
        public:
            //
            Transaction();
            //
            virtual ~Transaction(){}

        public:
            //
            TransactionType     m_type;
            //
            Int32               m_memberId;
            //
            Int32               m_memberUsername;
            //
            Float               m_amount;
            //
            QDateTime           m_date;
            //
            Float               m_balance;
            //
            QString             m_descr;
    };

    //
    typedef QSharedPointer<Transaction> TransactionPtr;
    //
    typedef std::vector<TransactionPtr> TransactionList;
    //
    typedef QSharedPointer<TransactionList> TransactionListPtr;

    //
    class TransactionListStats
    {
        public:
            //
            TransactionListStats();
            //
            virtual ~TransactionListStats(){}

        public:
            //
            Uint32              m_totalNumTransactions;
            //
            Float               m_totalInvoices;
            //
            Float               m_totalDeposits;
            //
            Float               m_totalBankCharges;
    };

    //
    typedef QSharedPointer<TransactionListStats> TransactionListStatsPtr;
}

#endif // TRANSACTION_H
