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
    class InvoiceResult
    {
        public:
            //
            InvoiceResult();
            //
            virtual ~InvoiceResult(){}

        public:
            //
            Int32                   m_error;
            //
            InvoicePtr              m_pInvoice;
    };
    //
    typedef QSharedPointer<InvoiceResult> InvoiceResultPtr;
    //
    typedef std::vector<InvoicePtr> InvoiceList;
    //
    typedef QSharedPointer<InvoiceList> InvoiceListPtr;
    //
    class InvoiceListResult
    {
        public:
            //
            InvoiceListResult();
            //
            virtual ~InvoiceListResult(){}

        public:
            //
            Int32                   m_error;
            //
            InvoiceListPtr          m_list;
    };
    //
    typedef QSharedPointer<InvoiceListResult> InvoiceListResultPtr;
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
    //
    class InvoiceListStatsResult
    {
        public:
            //
            InvoiceListStatsResult();
            //
            virtual ~InvoiceListStatsResult(){}

        public:
            //
            Int32                   m_error;
            //
            InvoiceListStatsPtr     m_stats;
    };
    //
    typedef QSharedPointer<InvoiceListStatsResult> InvoiceListStatsResultPtr;
}

#endif // INVOICE_H
