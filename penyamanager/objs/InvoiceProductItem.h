#ifndef INVOICEPRODUCTITEM_H
#define INVOICEPRODUCTITEM_H

#include <QString>

#include <DataTypes.h>

namespace PenyaManager
{
    //
    class InvoiceProductItem
    {
        public:
            //
            InvoiceProductItem();
            //
            InvoiceProductItem(Int32 productId, QString productName, Float priceperunit, Uint32 count);
            //
            virtual ~InvoiceProductItem(){}

        public:
            //
            Int32               m_productId;
            //
            QString             m_productname;
            //
            Float               m_priceperunit;
            //
            Uint32              m_count;
    };

    //
    typedef std::shared_ptr<InvoiceProductItem> InvoiceProductItemPtr;
    //
    typedef std::vector<InvoiceProductItemPtr> InvoiceProductItemList;
    //
    typedef std::shared_ptr<InvoiceProductItemList> InvoiceProductItemListPtr;
}

#endif // INVOICEPRODUCTITEM_H