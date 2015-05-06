#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

#include <DataTypes.h>
#include <constants.h>

namespace PenyaManager
{
    //
    enum class TransactionType
    {
        Invoice,
        Deposit, 
        AccountPayment 
    };
    
    QString getStringFromTransactionTypeEnum(TransactionType e);

    //
    class Transaction
    {
        public:
            //
            Transaction();
            //
            Transaction(TransactionType type, Int32 memberId, Float amount, const QDateTime& date, Float balance, const QString &descr);
            //
            virtual ~Transaction(){}

        public:
            //
            TransactionType     m_type;
            //
            Int32               m_memberId;
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
    typedef std::shared_ptr<Transaction> TransactionPtr;
    //
    typedef std::vector<TransactionPtr> TransactionList;
    //
    typedef std::shared_ptr<TransactionList> TransactionListPtr;
}

#endif // TRANSACTION_H
