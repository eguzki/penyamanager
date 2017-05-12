#ifndef DAO_H
#define DAO_H

#include <QtSql>

#include <objs/Transaction.h>
#include <objs/Reservation.h>
#include <objs/Member.h>
#include <objs/Invoice.h>
#include <objs/Deposit.h>
#include <objs/Provider.h>
#include <objs/ProductFamily.h>
#include <objs/ProductItem.h>
#include <objs/InvoiceProductItem.h>
#include <objs/ReservationItem.h>
#include <objs/ProviderInvoice.h>
#include <objs/ProviderInvoiceProductItem.h>
#include "DataTypes.h"

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
            bool exec(QSqlQuery&);
            //
            QSqlError lastError() const;
            //
            ProductFamilyListResultPtr getProductFamilies(bool onlyActive);
            //
            ProductItemListResultPtr getProductsFromFamily(Int32 familyId, bool onlyActive);
            //
            MemberResultPtr fetchMemberById(Int32 memberId);
            //
            MemberResultPtr fetchMemberByUsername(Int32 username);
            //
            FloatBoolPairResultPtr getAccountBalance(Int32 memberId);
            //
            InvoiceResultPtr getMemberActiveInvoice(Int32 memberId);
            //
            InvoiceListResultPtr getActiveInvoiceList();
            //
            InvoiceResultPtr getInvoice(Int32 invoiceId);
            //
            InvoiceResultPtr createInvoice(Int32 memberId);
            //
            bool removeProductInvoice(Int32 invoiceId, Int32 productId);
            //
            bool updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count);
            //
            Int32 increaseProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count);
            //
            Int32 countInvoiceProductItems(Int32 invoiceId);
            //
            InvoiceProductItemListResultPtr getInvoiceProductItems(Int32 invoiceId);
            //
            bool updateInvoice(const InvoicePtr &pInvoicePtr);
            //
            TransactionResultPtr getLastAccountInfo(Int32 memberId);
            //
            bool insertTransaction(const TransactionPtr &pTransactionPtr);
            //
            DepositResultPtr createDeposit(const DepositPtr &pDepositPtr);
            //
            TransactionListResultPtr getAccountList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            Int32 getAccountListCount(const QDate &fromDate, const QDate &toDate);
            //
            Float getAccountListInvoicesSum(const QDate &fromDate, const QDate &toDate);
            //
            Float getAccountListDepositsSum(const QDate &fromDate, const QDate &toDate);
            //
            Float getAccountListBankChargesSum(const QDate &fromDate, const QDate &toDate);
            //
            TransactionListResultPtr getAccountListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            Int32 getAccountListByMemberIdCount(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            Float getAccountListByMemberIdInvoicesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            Float getAccountListByMemberIdDepositsSum(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            Float getAccountListByMemberIdBankChargesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            ReservationListResultPtr getTableReservation(ReservationType reservationType, const QDate &now);
            //
            ReservationListResultPtr getOvenReservation(ReservationType reservationType, const QDate &now);
            //
            ReservationListResultPtr getFireplaceReservation(ReservationType reservationType, const QDate &now);
            //
            ReservationItemListResultPtr getLunchTableList();
            //
            ReservationItemListResultPtr getOvenList();
            //
            ReservationItemListResultPtr getFireplaceList();
            //
            bool makeTableReservation(const QDate &date, ReservationType reservationType, Uint16 guestNum, Int32 memberId, Int32 idtable, bool isAdmin);
            //
            bool updateTableReservation(Int32 reservationId, bool isAdmin);
            //
            bool cancelTableReservation(Int32 reservationId);
            //
            bool makeOvenReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idOven, bool isAdmin);
            //
            bool updateOvenReservation(Int32 reservationId, bool isAdmin);
            //
            bool cancelOvenReservation(Int32 reservationId);
            //
            bool makeFireplaceReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idFireplace, bool isAdmin);
            //
            bool updateFireplaceReservation(Int32 reservationId, bool isAdmin);
            //
            bool cancelFireplaceReservation(Int32 reservationId);
            //
            MemberListResultPtr getSlowPayersList();
            //
            InvoiceListResultPtr getInvoiceListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceListStatsResultPtr getInvoiceListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            InvoiceListResultPtr getInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceListStatsResultPtr getInvoiceListStats(const QDate &fromDate, const QDate &toDate);
            //
            ProviderListResultPtr getProviderList();
            //
            ProductItemListResultPtr getProductsFromProvider(Int32 providerId);
            //
            bool createProvider(const QString &name, const QString &imageFileName, const QString &phone);
            //
            ProductItemListResultPtr getProductsList(Uint32 page, Uint32 count);
            //
            ProductListStatsResultPtr getProductsListStats();
            //
            bool updateStock(Int32 productItemId, Int32 count);
            //
            ProductItemResultPtr getProductItem(Int32 productItemId);
            //
            bool updateProductItem(const ProductItemPtr &pProductItemPtr);
            //
            Int32 createProductItem(const ProductItemPtr &pProductItemPtr);
            //
            ProductFamilyResultPtr getProductFamily(Int32 familyId);
            //
            bool updateProductFamilyItem(const ProductFamilyPtr &pFamilyPtr);
            //
            Int32 createProductFamilyItem(const ProductFamilyPtr &pFamilyPtr);
            //
            InvoiceProductItemListResultPtr getProductExpensesList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceProductItemStatsResultPtr getProductExpensesListStats(const QDate &fromDate, const QDate &toDate);
            //
            InvoiceProductItemListResultPtr getProductExpensesListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceProductItemStatsResultPtr getProductExpensesListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            bool createProviderInvoice(const ProviderInvoicePtr &pProviderInvoicePtr);
            //
            bool createProviderInvoiceProduct(const QString &invoiceId, Int32 productId, Uint32 count);
            //
            ProviderInvoiceListResultPtr getProviderInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            ProviderInvoiceListStatsResultPtr getProviderInvoiceListStats(const QDate &fromDate, const QDate &toDate);
            //
            ProviderInvoiceListResultPtr getProviderInvoiceListByProviderId(Int32 providerId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            ProviderInvoiceListStatsResultPtr getProviderInvoiceListByProviderIdStats(Int32 providerId, const QDate &fromDate, const QDate &toDate);
            //
            DepositListResultPtr getUncheckedDeposits();
            //
            bool closeDeposit(Int32 depositId);
            //
            MemberListResultPtr getMemberList(bool onlyPostalSend, Uint32 page, Uint32 count);
            //
            MemberListStatsResultPtr getMemberListStats(bool onlyPostalSend);
            //
            bool updateMember(const MemberPtr &pMemberPtr);
            //
            Int32 createMember(const MemberPtr &pMemberPtr);
            //
            bool changeMemberPassword(Int32 memberId, const QString &pwdHash, const QDateTime &lastmodified);
            //
            bool changeMemberLastLogin(Int32 memberId, const QDateTime &lastlogin);
            //
            InvoiceResultPtr getLastInvoiceInfo();
            //
            bool updateInvoiceLastModDate(Int32 invoiceId, const QDateTime &lastModDate);
            //
            bool deleteInvoice(Int32 invoiceIde);
            //
            BoolResult checkUsername(Int32 username);
            //
            ProviderInvoiceResultPtr getProviderInvoiceById(const QString &providerInvoiceId);
            //
            ProviderInvoiceProductItemListResultPtr getProviderInvoiceProductsByInvoiceId(const QString &providerInvoiceId);

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
            QSqlQuery               m_memberByUsernameQuery;
            //
            QSqlQuery               m_memberAccountBalanceQuery;
            //
            QSqlQuery               m_invoiceQuery;
            //
            QSqlQuery               m_memberActiveInvoiceQuery;
            //
            QSqlQuery               m_removeProductInvoiceQuery;
            //
            QSqlQuery               m_updateProductInvoiceQuery;
            //
            QSqlQuery               m_increaseProductInvoiceQuery;
            //
            QSqlQuery               m_insertInvoiceQuery;
            //
            QSqlQuery               m_getLastIdQuery;
            //
            QSqlQuery               m_productInvoiceCountQuery;
            //
            QSqlQuery               m_productInvoiceItemsQuery;
            //
            QSqlQuery               m_updateInvoiceQuery;
            //
            QSqlQuery               m_memberLastAccountInfoQuery;
            //
            QSqlQuery               m_insertTransactionQuery;
            //
            QSqlQuery               m_insertDepositQuery;
            //
            QSqlQuery               m_accountListQuery;
            //
            QSqlQuery               m_memberAccountListQuery;
            //
            QSqlQuery               m_accountListCountQuery;
            //
            QSqlQuery               m_accountListInvoicesSumQuery;
            //
            QSqlQuery               m_accountListDepositsSumQuery;
            //
            QSqlQuery               m_accountListBankChargesSumQuery;
            //
            QSqlQuery               m_accountListByMemberIdCountQuery;
            //
            QSqlQuery               m_accountListByMemberIdInvoicesSumQuery;
            //
            QSqlQuery               m_accountListByMemberIdDepositsSumQuery;
            //
            QSqlQuery               m_accountListByMemberIdBankChargesSumQuery;
            //
            QSqlQuery               m_tableReservationListQuery;
            //
            QSqlQuery               m_ovenReservationListQuery;
            //
            QSqlQuery               m_fireplaceReservationListQuery;
            //
            QSqlQuery               m_lunchTablesListQuery;
            //
            QSqlQuery               m_ovenListQuery;
            //
            QSqlQuery               m_fireplaceListQuery;
            //
            QSqlQuery               m_insertTableReservationQuery;
            //
            QSqlQuery               m_updateTableReservationQuery;
            //
            QSqlQuery               m_cancelTableReservationQuery;
            //
            QSqlQuery               m_insertOvenReservationQuery;
            //
            QSqlQuery               m_updateOvenReservationQuery;
            //
            QSqlQuery               m_cancelOvenReservationQuery;
            //
            QSqlQuery               m_insertFireplaceReservationQuery;
            //
            QSqlQuery               m_updateFireplaceReservationQuery;
            //
            QSqlQuery               m_cancelFireplaceReservationQuery;
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
            //
            QSqlQuery               m_uncheckedDepositListQuery;
            //
            QSqlQuery               m_closeDepositQuery;
            //
            QSqlQuery               m_memberListQuery;
            //
            QSqlQuery               m_memberListFilteredQuery;
            //
            QSqlQuery               m_memberListStatsQuery;
            //
            QSqlQuery               m_memberListFilteredStatsQuery;
            //
            QSqlQuery               m_updateMemberQuery;
            //
            QSqlQuery               m_createMemberQuery;
            //
            QSqlQuery               m_updateMemberPasswordQuery;
            //
            QSqlQuery               m_updateMemberLastLoginQuery;
            //
            QSqlQuery               m_lastInvoiceQuery;
            //
            QSqlQuery               m_updateLastModInvoiceQuery;
            //
            QSqlQuery               m_removeInvoiceQuery;
            //
            QSqlQuery               m_getActiveInvoiceListQuery;
            //
            QSqlQuery               m_checkUsernameQuery;
            //
            QSqlQuery               m_providerInvoiceByIdQuery;
            //
            QSqlQuery               m_providerInvoiceProductsByInvoiceIdQuery;
    };
}
#endif // DAO_H
