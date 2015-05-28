#ifndef SERVICES_H
#define SERVICES_H

#include "objs/Member.h"
#include "objs/Transaction.h"
#include "objs/Deposit.h"

namespace PenyaManager {

    //
    class Services
    {
        public:
            //
            Services();
            //
            virtual ~Services();
            //
            void closeInvoice(const MemberPtr &pMemberPtr, Int32 invoiceId);
            //
            void createAccountTransaction(Int32 memberId, Float amount, const QString &description, TransactionType type);
            //
            DepositPtr createDeposit(const MemberPtr &pMemberPtr, Float amount);
    };
}

#endif
