#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <commons/DataTypes.h>

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
            virtual ~Deposit(){}

        public:
            //
            Int32               m_id;
            //
            Int32               m_memberId;
            //
            Int32               m_memberUsername;
            //
            DepositState        m_state;
            //
            QDateTime           m_date;
            //
            Float               m_total;
    };

    //
    typedef QSharedPointer<Deposit> DepositPtr;
    //
    class DepositResult
    {
        public:
            //
            DepositResult();
            //
            virtual ~DepositResult(){}

        public:
            //
            Int32                   m_error;
            //
            DepositPtr              m_deposit;
    };
    //
    typedef QSharedPointer<DepositResult> DepositResultPtr;
    //
    typedef std::vector<DepositPtr> DepositList;
    //
    typedef QSharedPointer<DepositList> DepositListPtr;
    //
    class DepositListResult
    {
        public:
            //
            DepositListResult();
            //
            virtual ~DepositListResult(){}

        public:
            //
            Int32                   m_error;
            //
            DepositListPtr          m_list;
    };
    //
    typedef QSharedPointer<DepositListResult> DepositListResultPtr;
}

#endif // DEPOSIT_H
