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
}

#endif // PROVIDERINVOICE_H
