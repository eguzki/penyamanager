#ifndef SERVICES_H
#define SERVICES_H

#include "objs/Invoice.h"
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
            //
            void resetSlowPayersBalance();
            //
            TransactionListStatsPtr getAccountListStats(const QDate &fromDate, const QDate &toDate);
            //
            TransactionListStatsPtr getAccountListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
    };
}

#endif
