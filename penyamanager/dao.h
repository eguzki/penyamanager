#ifndef DAO_H
#define DAO_H

#include <QtSql>

#include "DataTypes.h"
#include "objs/Transaction.h"
#include "objs/TableReservation.h"
#include "objs/Member.h"
#include "objs/Invoice.h"
#include "objs/Deposit.h"
#include "objs/ProductFamily.h"
#include "objs/ProductItem.h"
#include "objs/InvoiceProductItem.h"
#include "objs/LunchTable.h"

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
            //
            void updateInvoice(const InvoicePtr &pInvoicePtr);
            //
            TransactionPtr getLastAccountInfo(Int32 memberId);
            //
            void insertTransaction(const TransactionPtr &pTransactionPtr);
            //
            void updateMember(const MemberPtr &pMemberPtr);
            //
            DepositPtr createDeposit(const DepositPtr &pDepositPtr);
            //
            TransactionListPtr getAccountList(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            TableReservationListPtr getTableReservation(ReservationType reservationType, const QDate &now);
            //
            LunchTableListPtr getLunchTableList();

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
            //
            QSqlQuery               m_updateInvoiceQuery;
            //
            QSqlQuery               m_memberLastAccountInfoQuery;
            //
            QSqlQuery               m_insertTransactionQuery;
            //
            QSqlQuery               m_updateMemberQuery;
            //
            QSqlQuery               m_insertDepositQuery;
            //
            QSqlQuery               m_memberAccountListQuery;
            //
            QSqlQuery               m_tableReservationListQuery;
            //
            QSqlQuery               m_lunchTablesListQuery;
    };
}
#endif // DAO_H
