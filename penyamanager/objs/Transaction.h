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
        NewAccount,
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
    class TransactionResult
    {
        public:
            //
            TransactionResult();
            //
            virtual ~TransactionResult(){}

        public:
            //
            Int32                   m_error;
            //
            TransactionPtr          m_transaction;
    };
    //
    typedef QSharedPointer<TransactionResult> TransactionResultPtr;
    //
    typedef std::vector<TransactionPtr> TransactionList;
    //
    typedef QSharedPointer<TransactionList> TransactionListPtr;
    //
    class TransactionListResult
    {
        public:
            //
            TransactionListResult();
            //
            virtual ~TransactionListResult(){}

        public:
            //
            Int32                   m_error;
            //
            TransactionListPtr      m_list;
    };
    //
    typedef QSharedPointer<TransactionListResult> TransactionListResultPtr;

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
    //
    class TransactionListStatsResult
    {
        public:
            //
            TransactionListStatsResult();
            //
            virtual ~TransactionListStatsResult(){}

        public:
            //
            Int32                   m_error;
            //
            TransactionListStatsPtr m_listStats;
    };
    //
    typedef QSharedPointer<TransactionListStatsResult> TransactionListStatsResultPtr;
}

#endif // TRANSACTION_H
