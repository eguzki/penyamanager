#ifndef INVOICE_H
#define INVOICE_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
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
    class Invoice
    {
        public:
            //
            Invoice();
            //
            Invoice(Int32 id, Int32 memberId, InvoiceState state, const QDateTime &date, Float total);
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
            QDateTime           m_date;
            //
            Float               m_total;
    };

    //
    typedef QSharedPointer<Invoice> InvoicePtr;
    //
    typedef std::vector<InvoicePtr> InvoiceList;
    //
    typedef QSharedPointer<InvoiceList> InvoiceListPtr;

    //
    class InvoiceListStats
    {
        public:
            //
            InvoiceListStats();
            //
            InvoiceListStats(Uint32 totalNumInvoices, Float totalAmount);
            //
            virtual ~InvoiceListStats(){}

        public:
            //
            Uint32              m_totalNumInvoices;
            //
            Float               m_totalAmount;
    };

    //
    typedef QSharedPointer<InvoiceListStats> InvoiceListStatsPtr;
}

#endif // INVOICE_H
