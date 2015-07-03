#ifndef PROVIDERINVOICE_H
#define PROVIDERINVOICE_H

#include <QString>
#include <QDateTime>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    class ProviderInvoice
    {
        public:
            //
            ProviderInvoice();
            //
            ProviderInvoice(QString id, Float total, const QDate &regDate, Int32 providerid);
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
    };

    //
    typedef std::shared_ptr<ProviderInvoice> ProviderInvoicePtr;
    //
    typedef std::vector<ProviderInvoicePtr> ProviderInvoiceList;
    //
    typedef std::shared_ptr<ProviderInvoiceList> ProviderInvoiceListPtr;

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
    typedef std::shared_ptr<ProviderInvoiceListStats> ProviderInvoiceListStatsPtr;
}

#endif // PROVIDERINVOICE_H