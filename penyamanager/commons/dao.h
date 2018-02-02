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
    typedef QSharedPointer<QSqlQuery>           QueryPtr;
    //
    typedef std::function<QueryPtr(void)>       QueryFactory;
    //
    struct QueryResponse {
        //
        bool        error;
        //
        QueryPtr    query;
    };

    //
    class DAO
    {
        public:
            // Last query ID
            static const QString    kLastQueryId;
            //
            DAO(const QString& hostame, const QString& databaseName,
                    const QString& username, const QString& pass);
            //
            virtual ~DAO();
            //
            bool isOpen();
            //
            QueryResponse exec(QueryFactory);
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
            bool updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count, Float price);
            //
            Int32 increaseProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count);
            //
            InvoiceProductItemListResultPtr getInvoiceProductItems(Int32 invoiceId, Uint32 page, Uint32 count);
            //
            InvoiceProductItemStatsResultPtr getInvoiceProductItemsStats(Int32 invoiceId);
            //
            InvoiceProductItemListResultPtr getAllInvoiceProductItems(Int32 invoiceId);
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
            FloatResult getAccountListInvoicesSum(const QDate &fromDate, const QDate &toDate);
            //
            FloatResult getAccountListDepositsSum(const QDate &fromDate, const QDate &toDate);
            //
            FloatResult getAccountListBankChargesSum(const QDate &fromDate, const QDate &toDate);
            //
            TransactionListResultPtr getAccountListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            Int32 getAccountListByMemberIdCount(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            FloatResult getAccountListByMemberIdInvoicesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            FloatResult getAccountListByMemberIdDepositsSum(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            FloatResult getAccountListByMemberIdBankChargesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            ReservationListResultPtr getTableReservation(ReservationType reservationType, const QDate &now);
            //
            ReservationListResultPtr getOvenReservation(ReservationType reservationType, const QDate &now);
            //
            ReservationListResultPtr getFireplaceReservation(ReservationType reservationType, const QDate &now);
            //
            ReservationItemListResultPtr getLunchTableList(Uint32 page, Uint32 count);
            //
            ReservationItemListResultPtr getAllLunchTableList();
            //
            ReservationItemListResultPtr getOvenList(Uint32 page, Uint32 count);
            //
            ReservationItemListResultPtr getAllOvenList();
            //
            ReservationItemListResultPtr getFireplaceList(Uint32 page, Uint32 count);
            //
            ReservationItemListResultPtr getAllFireplaceList();
            //
            ReservationItemListStatsPtr getLunchTableListStats();
            //
            ReservationItemListStatsPtr getOvenListStats();
            //
            ReservationItemListStatsPtr getFireplaceListStats();
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
            ProviderResultPtr getProviderById(Int32 providerId);
            //
            bool updateProvider(const ProviderPtr &pProviderPtr);
            //
            ProductItemListResultPtr getProductsFromProvider(Int32 providerId);
            //
            Int32 createProvider(const ProviderPtr &pProviderPtr);
            //
            StockProductItemListResultPtr getAllStockProductsList();
            //
            StockProductItemListResultPtr getStockProductsList(Uint32 page, Uint32 count);
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
            InvoiceProductItemCounterStatsResultPtr getProductExpensesListStats(const QDate &fromDate, const QDate &toDate);
            //
            InvoiceProductItemListResultPtr getProductExpensesListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count);
            //
            InvoiceProductItemCounterStatsResultPtr getProductExpensesListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate);
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
            //
            Int32 getLastUsername();

        private:
            //
            QString getLastExecutedQuery(const QueryPtr& queryPtr);

        private:
            //
            QSqlDatabase            m_db;
    };
}
#endif // DAO_H
