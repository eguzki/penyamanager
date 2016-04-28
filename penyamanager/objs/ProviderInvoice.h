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
    typedef std::vector<ProviderInvoicePtr> ProviderInvoiceList;
    //
    typedef QSharedPointer<ProviderInvoiceList> ProviderInvoiceListPtr;

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
}

#endif // PROVIDERINVOICE_H
