#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

#include <DataTypes.h>
#include <constants.h>

namespace PenyaManager
{
    //
    class Transaction
    {
        public:
            //
            Transaction();
            //
            Transaction(Int32 id, Float amount, Uint64 date, Float balance, const QString &descr);
            //
            virtual ~Transaction(){}

        public:
            //
            Int32               m_id;
            //
            Float               m_amount;
            //
            Uint64              m_date;
            //
            Float               m_balance;
            //
            QString             m_descr;
    };

    //
    typedef std::shared_ptr<Transaction> TransactionPtr;
}

#endif // TRANSACTION_H
