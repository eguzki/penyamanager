#ifndef INVOICE_H
#define INVOICE_H

#include <DataTypes.h>

namespace PenyaManager
{
    //
    enum class InvoiceState
    {
        Open,
        Closed
    };
    //
    enum class PaymentType
    {
        Cash,
        Account
    };
    //
    class Invoice
    {
        public:
            //
            Invoice();
            //
            Invoice(Int32 id, Int32 memberId, InvoiceState state, Uint64 date, Float total, PaymentType payment);
            //
            virtual ~Invoice(){}

        public:
            //
            Int32               m_id;
            //
            Int32               m_memberId;
            //
            InvoiceState        m_state;
            //
            Uint64              m_date;
            //
            Float               m_total;
            //
            PaymentType         m_payment;
    };

    //
    typedef std::shared_ptr<Invoice> InvoicePtr;
}

#endif // INVOICE_H
