#ifndef PROVIDERINVOICE_H
#define PROVIDERINVOICE_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    class ProviderInvoice
    {
        public:
            //
            ProviderInvoice();
            //
            virtual ~ProviderInvoice(){}

        public:
            //
            QString             m_id;
            //
            Float               m_total;
            //
            QDate               m_regDate;
            //
            Int32               m_providerid;
            //
            QString             m_providerName;
            //
            QString             m_providerImagePath;
    };

    //
    typedef QSharedPointer<ProviderInvoice> ProviderInvoicePtr;
    //
    class ProviderInvoiceResult
    {
        public:
            //
            ProviderInvoiceResult();
            //
            virtual ~ProviderInvoiceResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProviderInvoicePtr      m_pProviderInvoice;
    };
    //
    typedef QSharedPointer<ProviderInvoiceResult> ProviderInvoiceResultPtr;
    //
    typedef std::vector<ProviderInvoicePtr> ProviderInvoiceList;
    //
    typedef QSharedPointer<ProviderInvoiceList> ProviderInvoiceListPtr;
    //
    class ProviderInvoiceListResult
    {
        public:
            //
            ProviderInvoiceListResult();
            //
            virtual ~ProviderInvoiceListResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProviderInvoiceListPtr  m_list;
    };
    //
    typedef QSharedPointer<ProviderInvoiceListResult> ProviderInvoiceListResultPtr;

    //
    class ProviderInvoiceListStats
    {
        public:
            //
            ProviderInvoiceListStats();
            //
            ProviderInvoiceListStats(Uint32 totalNumInvoices, Float totalAmount);
            //
            virtual ~ProviderInvoiceListStats(){}

        public:
            //
            Uint32              m_totalNumInvoices;
            //
            Float               m_totalAmount;
    };

    //
    typedef QSharedPointer<ProviderInvoiceListStats> ProviderInvoiceListStatsPtr;
    //
    class ProviderInvoiceListStatsResult
    {
        public:
            //
            ProviderInvoiceListStatsResult();
            //
            virtual ~ProviderInvoiceListStatsResult(){}

        public:
            //
            Int32                           m_error;
            //
            ProviderInvoiceListStatsPtr     m_stats;
    };
    //
    typedef QSharedPointer<ProviderInvoiceListStatsResult> ProviderInvoiceListStatsResultPtr;
}

#endif // PROVIDERINVOICE_H
