#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QString>
#include <QDateTime>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    enum class DepositState
    {
        Unchecked,
        Closed
    };
    //
    class Deposit
    {
        public:
            //
            Deposit();
            //
            Deposit(Int32 id, Int32 memberId, DepositState state, const QDateTime &date, Float total, const QString &descr);
            //
            virtual ~Deposit(){}

        public:
            //
            Int32               m_id;
            //
            Int32               m_memberId;
            //
            DepositState        m_state;
            //
            QDateTime           m_date;
            //
            Float               m_total;
            //
            QString             m_descr;
    };

    //
    typedef std::shared_ptr<Deposit> DepositPtr;
    //
    typedef std::vector<DepositPtr> DepositList;
    //
    typedef std::shared_ptr<DepositList> DepositListPtr;
}

#endif // DEPOSIT_H
