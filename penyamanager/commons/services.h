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
            bool cleanOutdatedInvoices();
            //
            bool closeInvoice(const InvoicePtr &pInvoicePtr);
            //
            bool createAccountTransaction(Int32 memberId, Float amount, const QString &description, TransactionType type);
            //
            DepositResultPtr createDeposit(const MemberPtr &pMemberPtr, Float amount);
            //
            bool resetSlowPayersBalance();
            //
            TransactionListStatsResultPtr getAccountListStats(const QDate &fromDate, const QDate &toDate);
            //
            TransactionListStatsResultPtr getAccountListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            bool updateInvoiceInfo(Int32 invoiceId, Int32 productId, Uint32 count);
            //
            bool removeInvoiceProductId(Int32 invoiceId, Int32 productId);
            //
            BoolResult increaseProductInvoice(Int32 invoiceId, Int32 productId, Int32 count);
            //
            MemberResultPtr getMemberById(Int32 memberId);
            //
            MemberResultPtr getMemberByUsername(Int32 username);
    };
}

#endif
