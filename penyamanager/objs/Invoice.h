#ifndef INVOICE_H
#define INVOICE_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <commons/DataTypes.h>

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
            virtual ~Invoice(){}

        public:
            //
            Int32               m_id;
            //
            Int32               m_memberId;
            //
            Int32               m_memberUsername;
            //
            InvoiceState        m_state;
            //
            QDateTime           m_date;
            //
            Float               m_total;
            //
            QDateTime           m_lastModified;
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
