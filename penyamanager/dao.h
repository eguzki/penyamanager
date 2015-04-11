#ifndef DAO_H
#define DAO_H

#include <QtSql>

#include "objs/Member.h"
#include "objs/Invoice.h"
#include "objs/ProductFamily.h"
#include "objs/ProductItem.h"
#include "objs/InvoiceProductItem.h"

namespace PenyaManager {
    //
    class DAO
    {
        public:
            //
            DAO(const QString& hostame, const QString& databaseName,
                    const QString& username, const QString& pass);
            //
            virtual ~DAO();
            //
            bool isOpen();
            //
            QSqlError lastError() const;
            //
            ProductFamilyListPtr getProductFamilies();
            //
            ProductItemListPtr getProductsFromFamily(Int32 familyId);
            //
            MemberPtr getActiveMemberById(Int32 memberLoginId);
            //
            InvoicePtr getMemberActiveInvoice(Int32 memberId);
            //
            InvoicePtr createInvoice(Int32 memberId);
            //
            void removeProductInvoice(Int32 invoiceId, Int32 productId);
            //
            void updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count);
            //
            InvoiceProductItemListPtr getInvoiceProductItems(Int32 invoiceId);

        private:
            //
            QSqlDatabase            m_db;
            //
            QSqlQuery               m_productFamiliesQuery;
            //
            QSqlQuery               m_productItemsByFamilyQuery;
            //
            QSqlQuery               m_memberById;
            //
            QSqlQuery               m_memberActiveInvoice;
            //
            QSqlQuery               m_removeProductInvoice;
            //
            QSqlQuery               m_updateProductInvoice;
            //
            QSqlQuery               m_insertInvoice;
            //
            QSqlQuery               m_getLastId;
            //
            QSqlQuery               m_productInvoiceItemsQuery;
    };
}
#endif // DAO_H
