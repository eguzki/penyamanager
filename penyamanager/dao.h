#ifndef DAO_H
#define DAO_H

#include <QtSql>

#include "DataTypes.h"
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
            //
            void resetInvoiceProductItems(Int32 invoiceId);

        private:
            //
            QSqlDatabase            m_db;
            //
            QSqlQuery               m_productFamiliesQuery;
            //
            QSqlQuery               m_productItemsByFamilyQuery;
            //
            QSqlQuery               m_memberByIdQuery;
            //
            QSqlQuery               m_memberActiveInvoiceQuery;
            //
            QSqlQuery               m_removeProductInvoiceQuery;
            //
            QSqlQuery               m_updateProductInvoiceQuery;
            //
            QSqlQuery               m_insertInvoiceQuery;
            //
            QSqlQuery               m_getLastIdQuery;
            //
            QSqlQuery               m_productInvoiceItemsQuery;
            //
            QSqlQuery               m_resetInvoiceProductItemsQuery;
    };
}
#endif // DAO_H
