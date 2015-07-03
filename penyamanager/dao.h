#ifndef DAO_H
#define DAO_H

#include <QtSql>

#include "DataTypes.h"
#include "objs/Transaction.h"
#include "objs/TableReservation.h"
#include "objs/Member.h"
#include "objs/Invoice.h"
#include "objs/Deposit.h"
#include "objs/Provider.h"
#include "objs/ProductFamily.h"
#include "objs/ProductItem.h"
#include "objs/InvoiceProductItem.h"
#include "objs/LunchTable.h"
#include "objs/ProviderInvoice.h"

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
            ProductFamilyListPtr getProductFamilies(bool onlyActive);
            //
            ProductItemListPtr getProductsFromFamily(Int32 familyId, bool onlyActive);
            //
            MemberPtr getActiveMemberById(Int32 memberLoginId);
            //
            InvoicePtr getMemberActiveInvoice(Int32 memberId);
            //
            InvoicePtr getInvoice(Int32 invoiceId);
            //
            MemberByAdminPtr getActiveMemberByAdmin(Int32 memberLoginId);
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
            DepositPtr createDeposit(const DepositPtr &pDepositPtr);
            //
            TransactionListPtr getAccountList(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            TableReservationListPtr getTableReservation(ReservationType reservationType, const QDate &now);
            //
            LunchTableListPtr getLunchTableList();
            //
            void makeTableReservation(const QDate &date, ReservationType reservationType, Uint16 guestNum, Int32 memberId, Int32 idtable);
            //
            void cancelTableReservation(Int32 reservationId);
            //
            MemberListPtr getSlowPayersList();
            //
            InvoiceListPtr getInvoiceListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceListStatsPtr getInvoiceListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            InvoiceListPtr getInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceListStatsPtr getInvoiceListStats(const QDate &fromDate, const QDate &toDate);
            //
            ProviderListPtr getProviderList();
            //
            ProductItemListPtr getProductsFromProvider(Int32 providerId);
            //
            void createProvider(const QString &name, const QString &imageFileName, const QString &phone);
            //
            ProductItemListPtr getProductsList(Uint32 page, Uint32 count);
            //
            ProductListStatsPtr getProductsListStats();
            //
            void updateStock(Int32 productItemId, Int32 count);
            //
            ProductItemPtr getProductItem(Int32 productItemId);
            //
            void updateProductItem(const ProductItemPtr &pProductItemPtr);
            //
            void createProductItem(const ProductItemPtr &pProductItemPtr);
            //
            ProductFamilyPtr getProductFamily(Int32 familyId);
            //
            void updateProductFamilyItem(const ProductFamilyPtr &pFamilyPtr);
            //
            void createProductFamilyItem(const ProductFamilyPtr &pFamilyPtr);
            //
            InvoiceProductItemListPtr getProductExpensesList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceProductItemStatsPtr getProductExpensesListStats(const QDate &fromDate, const QDate &toDate);
            //
            InvoiceProductItemListPtr getProductExpensesListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceProductItemStatsPtr getProductExpensesListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            void createProviderInvoice(const ProviderInvoicePtr &pProviderInvoicePtr);
            //
            void createProviderInvoiceProduct(const QString &invoiceId, Int32 productId, Uint32 count);
            //
            ProviderInvoiceListPtr getProviderInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            ProviderInvoiceListStatsPtr getProviderInvoiceListStats(const QDate &fromDate, const QDate &toDate);
            //
            ProviderInvoiceListPtr getProviderInvoiceListByProviderId(Int32 providerId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            ProviderInvoiceListStatsPtr getProviderInvoiceListByProviderIdStats(Int32 providerId, const QDate &fromDate, const QDate &toDate);

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
            QSqlQuery               m_invoiceQuery;
            //
            QSqlQuery               m_memberActiveInvoiceQuery;
            //
            QSqlQuery               m_memberByAdmin;
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
            QSqlQuery               m_insertDepositQuery;
            //
            QSqlQuery               m_memberAccountListQuery;
            //
            QSqlQuery               m_tableReservationListQuery;
            //
            QSqlQuery               m_lunchTablesListQuery;
            //
            QSqlQuery               m_insertTableReservationQuery;
            //
            QSqlQuery               m_cancelTableReservationQuery;
            //
            QSqlQuery               m_slowPayersQuery;
            //
            QSqlQuery               m_invoiceListByMemberIdQuery;
            //
            QSqlQuery               m_invoiceListByMemberIdStatsQuery;
            //
            QSqlQuery               m_invoiceListQuery;
            //
            QSqlQuery               m_invoiceListStatsQuery;
            //
            QSqlQuery               m_providerListQuery;
            //
            QSqlQuery               m_productItemsByProviderQuery;
            //
            QSqlQuery               m_createProviderQuery;
            //
            QSqlQuery               m_productItemListQuery;
            //
            QSqlQuery               m_productItemsStatsQuery;
            //
            QSqlQuery               m_updateStockQuery;
            //
            QSqlQuery               m_productItemQuery;
            //
            QSqlQuery               m_updateProductItemQuery;
            //
            QSqlQuery               m_createProductItemQuery;
            //
            QSqlQuery               m_productFamilyItemQuery;
            //
            QSqlQuery               m_updateProductFamilyItemQuery;
            //
            QSqlQuery               m_createProductFamilyItemQuery;
            //
            QSqlQuery               m_productExpensesListByMemberIdQuery;
            //
            QSqlQuery               m_productExpensesListByMemberIdStatsQuery;
            //
            QSqlQuery               m_productExpensesListQuery;
            //
            QSqlQuery               m_productExpensesListStatsQuery;
            //
            QSqlQuery               m_createProviderInvoiceQuery;
            //
            QSqlQuery               m_createProviderInvoiceProductQuery;
            //
            QSqlQuery               m_providerInvoiceListByProviderIdQuery;
            //
            QSqlQuery               m_providerInvoiceListByProviderIdStatsQuery;
            //
            QSqlQuery               m_providerInvoiceListQuery;
            //
            QSqlQuery               m_providerInvoiceListStatsQuery;
    };
}
#endif // DAO_H
