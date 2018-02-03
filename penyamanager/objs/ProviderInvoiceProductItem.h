#ifndef PROVIDERINVOICEPRODUCTITEM_H
#define PROVIDERINVOICEPRODUCTITEM_H

#include <QSharedPointer>
#include <QString>
#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    class ProviderInvoiceProductItem
    {
        public:
            //
            ProviderInvoiceProductItem();
            //
            virtual ~ProviderInvoiceProductItem(){}

        public:
            //
            Int32               m_productId;
            //
            Int32               m_count;
            //
            QString             m_productNameEus;
            //
            QString             m_productNameEs;
            //
            QString             m_productImagePath;
            //
            Float               m_productPrice;
    };

    //
    typedef QSharedPointer<ProviderInvoiceProductItem> ProviderInvoiceProductItemPtr;
    //
    typedef std::vector<ProviderInvoiceProductItemPtr> ProviderInvoiceProductItemList;
    //
    typedef QSharedPointer<ProviderInvoiceProductItemList> ProviderInvoiceProductItemListPtr;
    //
    class ProviderInvoiceProductItemListResult
    {
        public:
            //
            ProviderInvoiceProductItemListResult();
            //
            virtual ~ProviderInvoiceProductItemListResult(){}

        public:
            //
            Int32                               m_error;
            //
            ProviderInvoiceProductItemListPtr   m_list;
    };
    //
    typedef QSharedPointer<ProviderInvoiceProductItemListResult> ProviderInvoiceProductItemListResultPtr;
}

#endif // PROVIDERINVOICEPRODUCTITEM_H
