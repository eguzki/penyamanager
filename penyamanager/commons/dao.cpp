//

#include <QsLog.h>

#include "dao.h"

namespace PenyaManager {
    //
    DAO::DAO(const QString& hostname, const QString& databaseName,
            const QString& username, const QString& pass)
        :
            // add QT_DEBUG_PLUGINS=1 to check plugin errors
            m_db(QSqlDatabase::addDatabase("QMYSQL")),
            m_productFamiliesQuery(),
            m_productItemsByFamilyQuery(),
            m_memberByIdQuery(),
            m_memberByUsernameQuery(),
            m_memberAccountBalanceQuery(),
            m_invoiceQuery(),
            m_memberActiveInvoiceQuery(),
            m_removeProductInvoiceQuery(),
            m_updateProductInvoiceQuery(),
            m_increaseProductInvoiceQuery(),
            m_insertInvoiceQuery(),
            m_getLastIdQuery("SELECT LAST_INSERT_ID()"),
            m_productInvoiceCountQuery(),
            m_productInvoiceItemsQuery(),
            m_updateInvoiceQuery(),
            m_memberLastAccountInfoQuery(),
            m_insertTransactionQuery(),
            m_insertDepositQuery(),
            m_accountListQuery(),
            m_memberAccountListQuery(),
            m_accountListCountQuery(),
            m_accountListInvoicesSumQuery(),
            m_accountListDepositsSumQuery(),
            m_accountListBankChargesSumQuery(),
            m_accountListByMemberIdCountQuery(),
            m_accountListByMemberIdInvoicesSumQuery(),
            m_accountListByMemberIdDepositsSumQuery(),
            m_accountListByMemberIdBankChargesSumQuery(),
            m_tableReservationListQuery(),
            m_ovenReservationListQuery(),
            m_fireplaceReservationListQuery(),
            m_lunchTablesListQuery(),
            m_ovenListQuery(),
            m_fireplaceListQuery(),
            m_insertTableReservationQuery(),
            m_updateTableReservationQuery(),
            m_cancelTableReservationQuery(),
            m_insertOvenReservationQuery(),
            m_updateOvenReservationQuery(),
            m_cancelOvenReservationQuery(),
            m_insertFireplaceReservationQuery(),
            m_updateFireplaceReservationQuery(),
            m_cancelFireplaceReservationQuery(),
            m_slowPayersQuery(),
            m_invoiceListByMemberIdQuery(),
            m_invoiceListByMemberIdStatsQuery(),
            m_invoiceListQuery(),
            m_invoiceListStatsQuery(),
            m_providerListQuery(),
            m_productItemsByProviderQuery(),
            m_createProviderQuery(),
            m_productItemListQuery(),
            m_productItemsStatsQuery(),
            m_updateStockQuery(),
            m_productItemQuery(),
            m_updateProductItemQuery(),
            m_createProductItemQuery(),
            m_productFamilyItemQuery(),
            m_updateProductFamilyItemQuery(),
            m_createProductFamilyItemQuery(),
            m_productExpensesListByMemberIdQuery(),
            m_productExpensesListByMemberIdStatsQuery(),
            m_productExpensesListQuery(),
            m_productExpensesListStatsQuery(),
            m_createProviderInvoiceQuery(),
            m_createProviderInvoiceProductQuery(),
            m_providerInvoiceListByProviderIdQuery(),
            m_providerInvoiceListByProviderIdStatsQuery(),
            m_providerInvoiceListQuery(),
            m_providerInvoiceListStatsQuery(),
            m_uncheckedDepositListQuery(),
            m_closeDepositQuery(),
            m_memberListQuery(),
            m_memberListFilteredQuery(),
            m_memberListStatsQuery(),
            m_memberListFilteredStatsQuery(),
            m_updateMemberQuery(),
            m_createMemberQuery(),
            m_updateMemberPasswordQuery(),
            m_updateMemberLastLoginQuery(),
            m_lastInvoiceQuery(),
            m_updateLastModInvoiceQuery(),
            m_removeInvoiceQuery(),
            m_getActiveInvoiceListQuery(),
            m_checkUsernameQuery(),
            m_providerInvoiceByIdQuery(),
            m_providerInvoiceProductsByInvoiceIdQuery()
    {
        // configure db connection
        m_db.setHostName(hostname);
        m_db.setDatabaseName(databaseName);
        m_db.setUserName(username);
        m_db.setPassword(pass);

        // open ddbb connection
        bool ok = m_db.open();

        if (!ok) {
            return;
        }

        // ProductFamilies
        // for filterinf only active, fetch all and filter with code
        m_productFamiliesQuery.prepare("SELECT idproduct_family, name, image, active FROM product_family");

        // ProductItems by family
        // for filterinf only active, fetch all and filter with code
        m_productItemsByFamilyQuery.prepare("SELECT idproduct_item, name, image, active, reg_date, price, idprovider FROM product_item WHERE idproduct_family = :familyId");

        // Member by id
        m_memberByIdQuery.prepare(
                "SELECT member.name, member.username, member.surname, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                "member.notes, member.pwd, member.lastlogin "
                "FROM member "
                "WHERE member.idmember=:memberid"
                );

        // Member by id
        m_memberByUsernameQuery.prepare(
                "SELECT member.idmember, member.name, member.surname, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                "member.notes, member.pwd, member.lastlogin "
                "FROM member "
                "WHERE member.username=:username"
                );

        // Member account balance
        m_memberAccountBalanceQuery.prepare(
                "SELECT balance FROM account "
                "WHERE idmember=:memberid "
                "ORDER BY date DESC LIMIT 1 "
                );

        // Invoice by member ID
        m_invoiceQuery.prepare(
                "SELECT state, date, total, idmember, last_modif FROM invoice "
                "WHERE idinvoice = :invoiceid "
                );

        // Invoice by member ID
        m_memberActiveInvoiceQuery.prepare(
                "SELECT idinvoice, state, date, total, last_modif FROM invoice "
                "WHERE idmember = :memberid AND state = :stateid "
                "ORDER BY date DESC LIMIT 1"
                );

        // remove product invoice by ID
        m_removeProductInvoiceQuery.prepare(
                "DELETE FROM inv_prod "
                "WHERE idinvoice = :invoiceid AND idproduct_item = :productid"
                );

        // update product invoice by ID
        m_updateProductInvoiceQuery.prepare(
                "INSERT INTO inv_prod "
                "(idinvoice, idproduct_item, count) "
                "VALUES (:invoiceid, :productid, :count) "
                "ON DUPLICATE KEY UPDATE "
                "count = :count"
                );
        // update product invoice by ID
        m_increaseProductInvoiceQuery.prepare(
                "UPDATE inv_prod SET count = count + :count "
                "WHERE idinvoice = :invoiceid and idproduct_item = :productid"
                );

        // insert new invoice
        m_insertInvoiceQuery.prepare(
                "INSERT INTO invoice"
                "(idinvoice, state, date, total, idmember, last_modif) "
                "VALUES (NULL, :state, :date, :total, :idmember, :lastmodified)"
                );
        // invoice product items by invoiceId
        m_productInvoiceCountQuery.prepare(
                "SELECT COUNT(*)  "
                "FROM inv_prod "
                "WHERE idinvoice=:invoiceid"
                );
        // invoice product items by invoiceId
        m_productInvoiceItemsQuery.prepare(
                "SELECT product_item.idproduct_item, product_item.name, product_item.image, product_item.price, inv_prod.count "
                "FROM inv_prod INNER JOIN product_item ON inv_prod.idproduct_item=product_item.idproduct_item "
                "WHERE idinvoice=:invoiceid"
                );

        // update existing invoice
        m_updateInvoiceQuery.prepare(
                "UPDATE invoice "
                "SET state=:state, date=:date, total=:total, last_modif=:lastmodified "
                "WHERE idinvoice=:invoiceid"
                );

        // member's last account transaction
        m_memberLastAccountInfoQuery.prepare(
                "SELECT member.username, account.amount, account.date, account.balance, account.description, account.type "
                "FROM account "
                "INNER JOIN member ON member.idmember = account.idmember "
                "WHERE account.idmember=:memberid "
                "ORDER BY account.date DESC "
                "LIMIT 1"
                );

        // insert transaction
        m_insertTransactionQuery.prepare(
                "INSERT INTO account "
                "(idmember, amount, date, balance, description, type) "
                "VALUES (:memberid, :amount, :date, :balance, :description, :type)"
                );
        // insert new deposit
        m_insertDepositQuery.prepare(
                "INSERT INTO deposit "
                "(idmember, state, date, total, description) "
                "VALUES (:memberid, :state, :date, :total, :description)"
                );
        // member's account transaction list
        m_memberAccountListQuery.prepare(
                "SELECT member.username, account.amount, account.date, account.description, account.balance, account.type "
                "FROM account "
                "INNER JOIN member ON member.idmember = account.idmember "
                "WHERE account.idmember=:memberid "
                "AND account.date BETWEEN :fromDate AND :toDate "
                "ORDER BY account.date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // member's account transaction list
        m_accountListQuery.prepare(
                "SELECT account.idmember, member.username, account.amount, account.date, account.description, account.balance, account.type "
                "FROM account "
                "INNER JOIN member ON member.idmember = account.idmember "
                "WHERE date BETWEEN :fromDate AND :toDate "
                "ORDER BY date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // num transactions from account
        m_accountListCountQuery.prepare(
                "SELECT COUNT(*) FROM account "
                "WHERE date BETWEEN :fromDate AND :toDate"
                );
        // sum of invoices from account
        m_accountListInvoicesSumQuery.prepare(
                "SELECT SUM(amount) FROM account "
                "WHERE date BETWEEN :fromDate AND :toDate "
                "AND type=0"
                );
        // sum of deposits from account
        m_accountListDepositsSumQuery.prepare(
                "SELECT SUM(amount) FROM account "
                "WHERE date BETWEEN :fromDate AND :toDate "
                "AND type IN (1, 3)"
                );
        // sum of bank charges from account
        m_accountListBankChargesSumQuery.prepare(
                "SELECT SUM(amount) FROM account "
                "WHERE date BETWEEN :fromDate AND :toDate "
                "AND type=2"
                );
        // num transactions by memberid from account
        m_accountListByMemberIdCountQuery.prepare(
                "SELECT COUNT(*) FROM account "
                "WHERE idmember=:memberid "
                "AND date BETWEEN :fromDate AND :toDate"
                );
        // sum of invoices by memberid from account
        m_accountListByMemberIdInvoicesSumQuery.prepare(
                "SELECT SUM(amount) FROM account "
                "WHERE idmember=:memberid "
                "AND date BETWEEN :fromDate AND :toDate "
                "AND type=0"
                );
        // sum of deposits by memberid from account
        m_accountListByMemberIdDepositsSumQuery.prepare(
                "SELECT SUM(amount) FROM account "
                "WHERE idmember=:memberid "
                "AND date BETWEEN :fromDate AND :toDate "
                "AND type IN (1, 3)"
                );
        // sum of bank charger by memberid from account
        m_accountListByMemberIdBankChargesSumQuery.prepare(
                "SELECT SUM(amount) FROM account "
                "WHERE idmember=:memberid "
                "AND date BETWEEN :fromDate AND :toDate "
                "AND type=2"
                );
        // table reservation list for a given moment (date and reservationtype)
        m_tableReservationListQuery.prepare(
                "SELECT tablereservation.idreservation, tablereservation.idtable, member.username, member.name, member.surname, tablereservation.idmember, tablereservation.guestnum, tablereservation.isadmin "
                "FROM tablereservation "
                "INNER JOIN member ON tablereservation.idmember=member.idmember "
                "WHERE date=:dateid "
                "AND reservationtype=:reservationtypeid"
                );
        // oven reservation list for a given moment (date and reservationtype)
        m_ovenReservationListQuery.prepare(
                "SELECT ovenreservation.idreservation, ovenreservation.idoven, member.username, member.name, member.surname, ovenreservation.idmember, ovenreservation.isadmin "
                "FROM ovenreservation "
                "INNER JOIN member ON ovenreservation.idmember=member.idmember "
                "WHERE date=:dateid "
                "AND reservationtype=:reservationtypeid"
                );
        // oven reservation list for a given moment (date and reservationtype)
        m_fireplaceReservationListQuery.prepare(
                "SELECT fireplacereservation.idreservation, fireplacereservation.idfireplace, member.username, member.name, member.surname, fireplacereservation.idmember, fireplacereservation.isadmin "
                "FROM fireplacereservation "
                "INNER JOIN member ON fireplacereservation.idmember=member.idmember "
                "WHERE date=:dateid "
                "AND reservationtype=:reservationtypeid"
                );
        // lunch tables list
        m_lunchTablesListQuery.prepare(
                "SELECT idtable, name, guestnum "
                "FROM lunchtables"
                );
        // oven list
        m_ovenListQuery.prepare(
                "SELECT idoven, name "
                "FROM ovens"
                );
        // fireplace list
        m_fireplaceListQuery.prepare(
                "SELECT idfireplace, name "
                "FROM fireplaces"
                );
        // insert table reservation
        m_insertTableReservationQuery.prepare(
                "INSERT INTO tablereservation "
                "(date, reservationtype, guestnum, idmember, idtable, isadmin) "
                "VALUES (:date, :reservationtype, :guestnum, :idmember, :idtable, :isadmin)"
                );
        // update table reservation
        m_updateTableReservationQuery.prepare(
                "UPDATE tablereservation "
                "SET isadmin = :isadmin "
                "WHERE idreservation = :idreservation"
                );
        // cancel table reservation
        m_cancelTableReservationQuery.prepare(
                "DELETE FROM tablereservation "
                "WHERE idreservation = :idreservation"
                );
        // insert oven reservation
        m_insertOvenReservationQuery.prepare(
                "INSERT INTO ovenreservation "
                "(date, reservationtype, idmember, idoven, isadmin) "
                "VALUES (:date, :reservationtype, :idmember, :idoven, :isadmin)"
                );
        // update oven reservation
        m_updateOvenReservationQuery.prepare(
                "UPDATE ovenreservation "
                "SET isadmin = :isadmin "
                "WHERE idreservation = :idreservation"
                );
        // cancel oven reservation
        m_cancelOvenReservationQuery.prepare(
                "DELETE FROM ovenreservation "
                "WHERE idreservation = :idreservation"
                );
        // insert fireplace reservation
        m_insertFireplaceReservationQuery.prepare(
                "INSERT INTO fireplacereservation "
                "(date, reservationtype, idmember, idfireplace, isadmin) "
                "VALUES (:date, :reservationtype, :idmember, :idfireplace, :isadmin)"
                );
        // update fireplace reservation
        m_updateFireplaceReservationQuery.prepare(
                "UPDATE fireplacereservation "
                "SET isadmin = :isadmin "
                "WHERE idreservation = :idreservation"
                );
        // cancel fireplace reservation
        m_cancelFireplaceReservationQuery.prepare(
                "DELETE FROM fireplacereservation "
                "WHERE idreservation = :idreservation"
                );
        // slow payers
        // SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember
        // returns list of distinct idmembers and their last account date
        // First INNER JOIN on the same table (account) gets balance for the row with last (newest) account date
        // Second INNER JOIN on members table get member information
        m_slowPayersQuery.prepare(
                "SELECT ac.idmember, member.username, member.name, member.surname, member.image, ac.balance, member.lastmodified, member.reg_date "
                "FROM account ac "
                "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                "INNER JOIN member ON member.idmember=ac.idmember "
                "WHERE ac.balance<0 AND member.active=1"
                );
        // active invoice list by memberId
        m_invoiceListByMemberIdQuery.prepare(
                "SELECT member.username, invoice.idinvoice, invoice.date, invoice.total, invoice.last_modif "
                "FROM invoice "
                "INNER JOIN member ON member.idmember = invoice.idmember "
                "WHERE invoice.idmember = :memberid AND invoice.state = :stateid "
                "AND invoice.date BETWEEN :fromDate AND :toDate "
                "ORDER BY date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // active invoice list by memberId stats
        m_invoiceListByMemberIdStatsQuery.prepare(
                "SELECT COUNT(*), SUM(total) FROM invoice "
                "WHERE idmember = :memberid AND state = :stateid "
                "AND date BETWEEN :fromDate AND :toDate"
                );
        // active invoice list
        m_invoiceListQuery.prepare(
                "SELECT member.username, invoice.idinvoice, invoice.idmember, invoice.date, invoice.total, invoice.last_modif "
                "FROM invoice "
                "INNER JOIN member ON invoice.idmember=member.idmember "
                "WHERE invoice.state = :stateid "
                "AND invoice.date BETWEEN :fromDate AND :toDate "
                "ORDER BY invoice.date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // active invoice list stats
        m_invoiceListStatsQuery.prepare(
                "SELECT COUNT(*), SUM(total) FROM invoice "
                "WHERE state = :stateid "
                "AND date BETWEEN :fromDate AND :toDate"
                );
        // provider list
        m_providerListQuery.prepare(
                "SELECT idprovider, name, image, reg_date, phone FROM provider"
                );
        // ProductItems by provider
        m_productItemsByProviderQuery.prepare("SELECT idproduct_item, name, image, reg_date, idproduct_family, price FROM product_item WHERE active=1 AND idprovider=:providerId");
        // create provider
        m_createProviderQuery.prepare(
                "INSERT INTO provider "
                "(name, image, reg_date, phone) "
                "VALUES (:name, :image, :reg_date, :phone)"
                );
        // product items query
        m_productItemListQuery.prepare(
                "SELECT idproduct_item, name, active, image, reg_date, price, idproduct_family, idprovider, stock FROM product_item "
                "ORDER BY reg_date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // product items stats query
        m_productItemsStatsQuery.prepare(
                "SELECT COUNT(*) FROM product_item"
                );
        // update product item stock
        m_updateStockQuery.prepare(
                "UPDATE product_item SET stock = stock + :count WHERE idproduct_item = :productid"
                );
        // product item
        m_productItemQuery.prepare(
                "SELECT name, active, image, reg_date, price, idproduct_family, idprovider, stock FROM product_item "
                "WHERE idproduct_item = :productid"
                );
        // update product item
        m_updateProductItemQuery.prepare(
                "UPDATE product_item "
                "SET name=:name, image=:image, active=:active, idproduct_family=:familyid, price=:price, "
                "idprovider=:providerid, stock=:stock "
                "WHERE idproduct_item = :productid"
                );
        // create product item
        m_createProductItemQuery.prepare(
                "INSERT INTO product_item "
                "(name, image, active, reg_date, idproduct_family, price, idprovider, stock) "
                "VALUES (:name, :image, :active, :reg_date, :familyid, :price, :providerid, :stock)"
                );
        // product family item
        m_productFamilyItemQuery.prepare(
                "SELECT name, active, image, reg_date FROM product_family "
                "WHERE idproduct_family = :familyid"
                );
        // update product family item
        m_updateProductFamilyItemQuery.prepare(
                "UPDATE product_family "
                "SET name=:name, image=:image, active=:active "
                "WHERE idproduct_family = :familyid"
                );
        // create product family item
        m_createProductFamilyItemQuery.prepare(
                "INSERT INTO product_family "
                "(name, image, active, reg_date) "
                "VALUES (:name, :image, :active, :reg_date)"
                );
        // product expenses list by memberId
        m_productExpensesListByMemberIdQuery.prepare(
                "SELECT product_item.idproduct_item, product_item.name, product_item.image, product_item.price, SUM(inv_prod.count) "
                "FROM invoice "
                "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                "INNER JOIN product_item ON product_item.idproduct_item=inv_prod.idproduct_item "
                "WHERE invoice.idmember=:memberid AND invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1 "
                "GROUP BY inv_prod.idproduct_item "
                "LIMIT :limit OFFSET :offset"
                );
        // product expenses list by memberId stats
        m_productExpensesListByMemberIdStatsQuery.prepare(
                "SELECT COUNT(DISTINCT inv_prod.idproduct_item) "
                "FROM invoice "
                "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                "WHERE invoice.idmember=:memberid AND invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1"
                );
        // product expenses list
        // only closed
        m_productExpensesListQuery.prepare(
                "SELECT product_item.idproduct_item, product_item.name, product_item.image, product_item.price, SUM(inv_prod.count) "
                "FROM invoice "
                "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                "INNER JOIN product_item ON product_item.idproduct_item=inv_prod.idproduct_item "
                "WHERE invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1 "
                "GROUP BY inv_prod.idproduct_item "
                "LIMIT :limit OFFSET :offset"
                );
        // product expenses list stats
        // only closed
        m_productExpensesListStatsQuery.prepare(
                "SELECT COUNT(DISTINCT inv_prod.idproduct_item) "
                "FROM invoice "
                "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                "WHERE invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1"
                );
        // create provider invoice
        m_createProviderInvoiceQuery.prepare(
                "INSERT INTO provider_invoices "
                "(idprovider_invoices, date, total, idprovider) "
                "VALUES (:id, :date, :total, :providerid)"
                );
        // create provider invoice product
        m_createProviderInvoiceProductQuery.prepare(
                "INSERT INTO provider_invoices_product "
                "(provider_invoices_idprovider_invoices, product_item_idproduct_item, count) "
                "VALUES (:providerinvoiceid, :productid, :count)"
                );
        // provider invoice list by provider
        m_providerInvoiceListByProviderIdQuery.prepare(
                "SELECT idprovider_invoices, date, total, idprovider FROM provider_invoices "
                "WHERE idprovider = :providerid "
                "AND date BETWEEN :fromDate AND :toDate "
                "ORDER BY date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // provider invoice list Stats by provider
        m_providerInvoiceListByProviderIdStatsQuery.prepare(
                "SELECT COUNT(*), SUM(total) FROM provider_invoices "
                "WHERE idprovider = :providerid "
                "AND date BETWEEN :fromDate AND :toDate"
                );
        // provider invoice list
        m_providerInvoiceListQuery.prepare(
                "SELECT idprovider_invoices, date, total, idprovider FROM provider_invoices "
                "WHERE date BETWEEN :fromDate AND :toDate "
                "ORDER BY date DESC "
                "LIMIT :limit OFFSET :offset"
                );
        // provider invoice list stats
        m_providerInvoiceListStatsQuery.prepare(
                "SELECT COUNT(*), SUM(total) FROM provider_invoices "
                "WHERE date BETWEEN :fromDate AND :toDate"
                );
        // unchecked deposit list
        m_uncheckedDepositListQuery.prepare(
                "SELECT member.username, deposit.iddeposit, deposit.date, deposit.total, deposit.description, deposit.idmember "
                "FROM deposit "
                "INNER JOIN member ON member.idmember = deposit.idmember "
                "WHERE deposit.state = 0"
                );
        // close deposit
        m_closeDepositQuery.prepare(
                "UPDATE deposit "
                "SET state=1 "
                "WHERE iddeposit=:depositid"
                );
        // member list
        m_memberListQuery.prepare(
                "SELECT member.idmember, member.username, member.name, member.surname, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                "member.notes, ac.balance "
                "FROM account ac "
                "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                "INNER JOIN member ON member.idmember=ac.idmember "
                "ORDER BY member.surname ASC "
                "LIMIT :limit OFFSET :offset"
                );
        // member filtered list
        m_memberListFilteredQuery.prepare(
                "SELECT member.idmember, member.username, member.name, member.surname, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                "member.notes, ac.balance "
                "FROM account ac "
                "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                "INNER JOIN member ON member.idmember=ac.idmember "
                "WHERE member.postal_send = 1 "
                "ORDER BY member.surname ASC "
                "LIMIT :limit OFFSET :offset"
                );
        // member list stats
        m_memberListStatsQuery.prepare(
                "SELECT COUNT(*) FROM member"
                );
        // member list filtered stats
        m_memberListFilteredStatsQuery.prepare(
                "SELECT COUNT(*) FROM member "
                "WHERE postal_send = 1"
                );
        // update  member
        m_updateMemberQuery.prepare(
                "UPDATE member "
                "SET username=:username, name=:name, surname=:surname, image=:image, lastmodified=:lastmodified, active=:active, isAdmin=:isadmin, birth=:birth, "
                "address=:address, zip_code=:zip_code, town=:town, state=:state, tel=:tel, tel2=:tel2, email=:email, bank_account=:bank_account, postal_send=:postal_send, "
                "notes=:notes "
                "WHERE idmember = :memberid"
                );
        // create member
        m_createMemberQuery.prepare(
                "INSERT INTO member "
                "(username, name, surname, image, lastmodified, reg_date, active, isAdmin, birth, "
                "address, zip_code, town, state, tel, tel2, email, bank_account, postal_send, "
                "notes, pwd, lastlogin) "
                "VALUES (:username, :name, :surname, :image, :lastmodified, :reg_date, :active, :isadmin, :birth, "
                ":address, :zip_code, :town, :state, :tel, :tel2, :email, :bank_account, :postal_send, "
                ":notes, :pwd, :lastlogin)"
                );
        // update member password
        m_updateMemberPasswordQuery.prepare(
                "UPDATE member "
                "SET pwd=:pwd, lastmodified=:lastmodified "
                "WHERE idmember = :memberid"
                );
        // update member lastlogin date
        m_updateMemberLastLoginQuery.prepare(
                "UPDATE member "
                "SET lastlogin=:lastlogin "
                "WHERE idmember = :memberid"
                );
        // Get last invoice (closed or open)
        m_lastInvoiceQuery.prepare(
                "SELECT idinvoice, state, date, total, idmember, last_modif FROM invoice "
                "ORDER BY last_modif DESC "
                "LIMIT 1"
                );
        // update invoice's last modification date
        m_updateLastModInvoiceQuery.prepare(
                "UPDATE invoice "
                "SET last_modif=:lastmodified "
                "WHERE idinvoice=:invoiceid"
                );
        // remove invoice
        m_removeInvoiceQuery.prepare(
                "DELETE FROM invoice "
                "WHERE idinvoice=:invoiceid"
                );
        // active invoice list
        m_getActiveInvoiceListQuery.prepare(
                "SELECT idinvoice, state, date, total, idmember, last_modif "
                "FROM invoice "
                "WHERE state = :state"
                );
        // check username
        m_checkUsernameQuery.prepare(
                "SELECT COUNT(*) "
                "FROM member "
                "WHERE username = :username"
                );
        // get provider invoice by id
        m_providerInvoiceByIdQuery.prepare(
                "SELECT provider_invoices.date, provider_invoices.total, provider.name, provider.image "
                "FROM provider_invoices "
                "INNER JOIN provider ON provider.idprovider = provider_invoices.idprovider "
                "WHERE provider_invoices.idprovider_invoices = :providerinvoicesid"
                );
        // get provider invoice product by invoice id
        m_providerInvoiceProductsByInvoiceIdQuery.prepare(
                "SELECT provider_invoices_product.product_item_idproduct_item, provider_invoices_product.count, product_item.name, product_item.image, product_item.price "
                "FROM provider_invoices_product "
                "INNER JOIN product_item ON product_item.idproduct_item = provider_invoices_product.product_item_idproduct_item "
                "WHERE provider_invoices_product.provider_invoices_idprovider_invoices = :providerinvoicesid"
                );
    }

    //
    DAO::~DAO()
    {
        if (isOpen())
        {
            m_db.close();
        }
    }

    //
    bool DAO::isOpen()
    {
        return m_db.isOpen();
    }

    //
    QSqlError DAO::lastError() const
    {
        return m_db.lastError();
    }

    //
    ProductFamilyListResultPtr DAO::getProductFamilies(bool onlyActive)
    {
        ProductFamilyListResultPtr pfListPrt(new ProductFamilyListResult);

        // run query
        if (!m_productFamiliesQuery.exec())
        {
            qDebug() << m_productFamiliesQuery.lastError();
            QLOG_ERROR() << m_productFamiliesQuery.lastError();
            pfListPrt->m_error = 1;
        } else {
            pfListPrt->m_list = ProductFamilyListPtr(new ProductFamilyList);
            while (m_productFamiliesQuery.next()) {
                ProductFamilyPtr pfPtr(new ProductFamily);
                pfPtr->m_id = m_productFamiliesQuery.value(0).toUInt();
                pfPtr->m_name = m_productFamiliesQuery.value(1).toString();
                pfPtr->m_imagePath = m_productFamiliesQuery.value(2).toString();
                pfPtr->m_active = m_productFamiliesQuery.value(3).toInt() == 1;
                // discard when onlyActive filter is on and family is not active
                if (!onlyActive || pfPtr->m_active) {
                    pfListPrt->m_list->push_back(pfPtr);
                }
            }
        }
        m_productFamiliesQuery.finish();
        return pfListPrt;
    }

    //
    ProductItemListResultPtr DAO::getProductsFromFamily(Int32 familyId, bool onlyActive)
    {
        ProductItemListResultPtr pIListResultPtr(new ProductItemListResult);
        // bind value
        m_productItemsByFamilyQuery.bindValue(":familyId", familyId);
        // run query
        if (!m_productItemsByFamilyQuery.exec())
        {
            qDebug() << m_productItemsByFamilyQuery.lastError();
            QLOG_ERROR() << m_productItemsByFamilyQuery.lastError();
            pIListResultPtr->m_error = 1;
        } else {
            pIListResultPtr->m_list = ProductItemListPtr(new ProductItemList);
            while (m_productItemsByFamilyQuery.next()) {
                ProductItemPtr pfPtr(new ProductItem);
                pfPtr->m_id = m_productItemsByFamilyQuery.value(0).toUInt();
                pfPtr->m_name = m_productItemsByFamilyQuery.value(1).toString();
                pfPtr->m_imagePath = m_productItemsByFamilyQuery.value(2).toString();
                pfPtr->m_active = m_productItemsByFamilyQuery.value(3).toInt() == 1;
                pfPtr->m_regDate = m_productItemsByFamilyQuery.value(4).toDateTime();
                pfPtr->m_price = m_productItemsByFamilyQuery.value(5).toFloat();
                pfPtr->m_providerId = m_productItemsByFamilyQuery.value(6).toInt();
                // discard when onlyActive filter is on and product is not active
                if (!onlyActive || pfPtr->m_active) {
                    pIListResultPtr->m_list->push_back(pfPtr);
                }
            }
        }
        m_productFamiliesQuery.finish();
        return pIListResultPtr;
    }
    //
    MemberResultPtr DAO::fetchMemberById(Int32 memberId)
    {
        MemberResultPtr pMemberResultPtr(new MemberResult);
        // member and balance
        m_memberByIdQuery.bindValue(":memberid", memberId);
        if (!m_memberByIdQuery.exec())
        {
            qDebug() << m_memberByIdQuery.lastError();
            QLOG_ERROR() << m_memberByIdQuery.lastError();
            pMemberResultPtr->m_error = 1;
        } else if (m_memberByIdQuery.next())
        {
            MemberPtr pMemberPtr(new Member);
            Uint32 column = 0;
            pMemberPtr->m_id = memberId;
            pMemberPtr->m_name = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_username = m_memberByIdQuery.value(column++).toInt();
            pMemberPtr->m_surname = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_imagePath = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_lastModified = m_memberByIdQuery.value(column++).toDateTime();
            pMemberPtr->m_regDate = m_memberByIdQuery.value(column++).toDateTime();
            pMemberPtr->m_active = m_memberByIdQuery.value(column++).toInt() == 1;
            pMemberPtr->m_isAdmin = m_memberByIdQuery.value(column++).toInt() == 1;
            pMemberPtr->m_birthdate = m_memberByIdQuery.value(column++).toDate();
            pMemberPtr->m_address = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_zipCode = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_town = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_state = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_phone = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_phone2 = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_email = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_bank_account = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_postalSend = m_memberByIdQuery.value(column++).toInt() == 1;
            pMemberPtr->m_notes = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_pwd = m_memberByIdQuery.value(column++).toString();
            pMemberPtr->m_lastLogin = m_memberByIdQuery.value(column++).toDateTime();
            pMemberResultPtr->m_member = pMemberPtr;
        }
        m_memberByIdQuery.finish();
        return pMemberResultPtr;
    }
    //
    MemberResultPtr DAO::fetchMemberByUsername(Int32 username)
    {
        MemberResultPtr pMemberResultPtr(new MemberResult);
        // member and balance
        m_memberByUsernameQuery.bindValue(":username", username);
        if (!m_memberByUsernameQuery.exec())
        {
            qDebug() << m_memberByUsernameQuery.lastError();
            QLOG_ERROR() << m_memberByUsernameQuery.lastError();
            pMemberResultPtr->m_error = 1;
        } else if (m_memberByUsernameQuery.next())
        {
            MemberPtr pMemberPtr(new Member);
            Uint32 column = 0;
            pMemberPtr->m_id = m_memberByUsernameQuery.value(column++).toInt();
            pMemberPtr->m_name = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_username = username;
            pMemberPtr->m_surname = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_imagePath = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_lastModified = m_memberByUsernameQuery.value(column++).toDateTime();
            pMemberPtr->m_regDate = m_memberByUsernameQuery.value(column++).toDateTime();
            pMemberPtr->m_active = m_memberByUsernameQuery.value(column++).toInt() == 1;
            pMemberPtr->m_isAdmin = m_memberByUsernameQuery.value(column++).toInt() == 1;
            pMemberPtr->m_birthdate = m_memberByUsernameQuery.value(column++).toDate();
            pMemberPtr->m_address = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_zipCode = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_town = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_state = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_phone = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_phone2 = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_email = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_bank_account = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_postalSend = m_memberByUsernameQuery.value(column++).toInt() == 1;
            pMemberPtr->m_notes = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_pwd = m_memberByUsernameQuery.value(column++).toString();
            pMemberPtr->m_lastLogin = m_memberByUsernameQuery.value(column++).toDateTime();
            pMemberResultPtr->m_member = pMemberPtr;
        }
        m_memberByUsernameQuery.finish();
        return pMemberResultPtr;
    }
    //
    FloatBoolPairResultPtr DAO::getAccountBalance(Int32 memberId)
    {
        FloatBoolPairResultPtr pResult(new FloatBoolPairResult);
        // member and balance
        m_memberAccountBalanceQuery.bindValue(":memberid", memberId);
        if (!m_memberAccountBalanceQuery.exec())
        {
            qDebug() << m_memberAccountBalanceQuery.lastError();
            QLOG_ERROR() << m_memberAccountBalanceQuery.lastError();
            pResult->m_error = 1;
        } else if (m_memberAccountBalanceQuery.next())
        {
            pResult->m_pair.b = true;
            pResult->m_pair.f = m_memberAccountBalanceQuery.value(0).toFloat();
        }
        m_memberAccountBalanceQuery.finish();
        return pResult;
    }
    //
    InvoiceResultPtr DAO::getInvoice(Int32 invoiceId)
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);
        m_invoiceQuery.bindValue(":invoiceid", invoiceId);
        if (!m_invoiceQuery.exec())
        {
            qDebug() << m_invoiceQuery.lastError();
            QLOG_ERROR() << m_invoiceQuery.lastError();
            pInvoiceResultPtr->m_error = 1;
        } else if (m_invoiceQuery.next())
        {
            InvoicePtr pInvoicePtr(new Invoice());
            pInvoicePtr->m_id = invoiceId;
            pInvoicePtr->m_state = static_cast<InvoiceState>(m_invoiceQuery.value(0).toUInt());
            pInvoicePtr->m_date = m_invoiceQuery.value(1).toDateTime();
            pInvoicePtr->m_total = m_invoiceQuery.value(2).toFloat();
            pInvoicePtr->m_memberId = m_invoiceQuery.value(3).toInt();
            pInvoicePtr->m_lastModified = m_invoiceQuery.value(4).toDateTime();
            pInvoiceResultPtr->m_pInvoice = pInvoicePtr;
        }
        m_invoiceQuery.finish();

        return pInvoiceResultPtr;
    }

    InvoiceResultPtr DAO::getMemberActiveInvoice(Int32 memberId)
    {
        InvoiceResultPtr pInvoiceResultPtr;
        m_memberActiveInvoiceQuery.bindValue(":memberid", memberId);
        m_memberActiveInvoiceQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Open));
        if (!m_memberActiveInvoiceQuery.exec())
        {
            qDebug() << m_memberActiveInvoiceQuery.lastError();
            QLOG_ERROR() << m_memberActiveInvoiceQuery.lastError();
            pInvoiceResultPtr->m_error = 1;
        } else if (m_memberActiveInvoiceQuery.next())
        {
            InvoicePtr pInvoicePtr(new Invoice());
            pInvoicePtr->m_id = m_memberActiveInvoiceQuery.value(0).toUInt();
            pInvoicePtr->m_state = static_cast<InvoiceState>(m_memberActiveInvoiceQuery.value(1).toUInt());
            pInvoicePtr->m_date = m_memberActiveInvoiceQuery.value(2).toDateTime();
            pInvoicePtr->m_total = m_memberActiveInvoiceQuery.value(3).toFloat();
            pInvoicePtr->m_lastModified = m_memberActiveInvoiceQuery.value(4).toDateTime();
            pInvoiceResultPtr->m_pInvoice = pInvoicePtr;
        }
        m_memberActiveInvoiceQuery.finish();
        return pInvoiceResultPtr;
    }
    //
    bool DAO::removeProductInvoice(Int32 invoiceId, Int32 productId)
    {
        m_removeProductInvoiceQuery.bindValue(":invoiceid", invoiceId);
        m_removeProductInvoiceQuery.bindValue(":productid", productId);
        bool ok = m_removeProductInvoiceQuery.exec();
        if (!ok)
        {
            qDebug() << m_removeProductInvoiceQuery.lastError();
            QLOG_ERROR() << m_removeProductInvoiceQuery.lastError();
        }
        m_removeProductInvoiceQuery.finish();
        return ok;
    }
    //
    bool DAO::updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        m_updateProductInvoiceQuery.bindValue(":invoiceid", invoiceId);
        m_updateProductInvoiceQuery.bindValue(":productid", productId);
        m_updateProductInvoiceQuery.bindValue(":count", count);
        bool ok = m_updateProductInvoiceQuery.exec();
        if (!ok)
        {
            qDebug() << m_updateProductInvoiceQuery.lastError();
            QLOG_ERROR() << m_updateProductInvoiceQuery.lastError();
        }
        m_updateProductInvoiceQuery.finish();
        return ok;
    }
    //
    // Returns number of rows affected
    // -1 for error
    Int32 DAO::increaseProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        m_increaseProductInvoiceQuery.bindValue(":invoiceid", invoiceId);
        m_increaseProductInvoiceQuery.bindValue(":productid", productId);
        m_increaseProductInvoiceQuery.bindValue(":count", count);
        Int32 numRowsAffected = -1;
        if (!m_increaseProductInvoiceQuery.exec())
        {
            qDebug() << m_increaseProductInvoiceQuery.lastError();
            QLOG_ERROR() << m_increaseProductInvoiceQuery.lastError();
        } else {
            numRowsAffected = m_increaseProductInvoiceQuery.numRowsAffected();
        }
        m_increaseProductInvoiceQuery.finish();
        return numRowsAffected;
    }
    //
    InvoiceResultPtr DAO::createInvoice(Int32 memberId)
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);
        InvoicePtr pInvoicePtr(new Invoice);
        pInvoicePtr->m_id = 0;
        pInvoicePtr->m_memberId = memberId;
        pInvoicePtr->m_state = InvoiceState::Open;
        pInvoicePtr->m_date = QDateTime::currentDateTime();
        pInvoicePtr->m_total = 0.0;
        pInvoicePtr->m_lastModified = QDateTime::currentDateTime();
        pInvoiceResultPtr->m_pInvoice = pInvoicePtr;

        m_insertInvoiceQuery.bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
        m_insertInvoiceQuery.bindValue(":date", pInvoicePtr->m_date);
        m_insertInvoiceQuery.bindValue(":total", pInvoicePtr->m_total);
        m_insertInvoiceQuery.bindValue(":idmember", pInvoicePtr->m_memberId);
        m_insertInvoiceQuery.bindValue(":lastmodified", pInvoicePtr->m_lastModified);
        if (!m_insertInvoiceQuery.exec())
        {
            qDebug() << m_insertInvoiceQuery.lastError();
            QLOG_ERROR() << m_insertInvoiceQuery.lastError();
            pInvoiceResultPtr->m_error = 1;
        }
        m_insertInvoiceQuery.finish();
        if (pInvoiceResultPtr->m_error) {
            return pInvoiceResultPtr;
        }

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        if (!m_getLastIdQuery.exec())
        {
            qDebug() << m_getLastIdQuery.lastError();
            QLOG_ERROR() << m_getLastIdQuery.lastError();
            pInvoiceResultPtr->m_error = 1;
        } else if (m_getLastIdQuery.next())
        {
            pInvoiceResultPtr->m_pInvoice->m_id = m_getLastIdQuery.value(0).toUInt();
        }
        m_getLastIdQuery.finish();
        return pInvoiceResultPtr;
    }
    //
    Int32 DAO::countInvoiceProductItems(Int32 invoiceId)
    {
        Uint32 count = 0;
        m_productInvoiceCountQuery.bindValue(":invoiceid", invoiceId);
        if (!m_productInvoiceCountQuery.exec())
        {
            qDebug() << m_productInvoiceCountQuery.lastError();
            QLOG_ERROR() << m_productInvoiceCountQuery.lastError();
            count = -1;
        } else if (m_productInvoiceCountQuery.next())
        {
            count = m_productInvoiceCountQuery.value(0).toUInt();
        }
        m_productInvoiceCountQuery.finish();
        return count;
    }
    //
    InvoiceProductItemListResultPtr DAO::getInvoiceProductItems(Int32 invoiceId)
    {
        InvoiceProductItemListResultPtr pInvoicePILResult(new InvoiceProductItemListResult);
        // bind value
        m_productInvoiceItemsQuery.bindValue(":invoiceid", invoiceId);
        // run query
        if (!m_productInvoiceItemsQuery.exec())
        {
            qDebug() << m_productInvoiceItemsQuery.lastError();
            QLOG_ERROR() << m_productInvoiceItemsQuery.lastError();
            pInvoicePILResult->m_error = 1;
        } else {
            pInvoicePILResult->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (m_productInvoiceItemsQuery.next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId = m_productInvoiceItemsQuery.value(0).toInt();
                pInvoiceProductItemPtr->m_productname = m_productInvoiceItemsQuery.value(1).toString();
                pInvoiceProductItemPtr->m_imagePath = m_productInvoiceItemsQuery.value(2).toString();
                pInvoiceProductItemPtr->m_priceperunit = m_productInvoiceItemsQuery.value(3).toFloat();
                pInvoiceProductItemPtr->m_count = m_productInvoiceItemsQuery.value(4).toUInt();
                pInvoicePILResult->m_list->push_back(pInvoiceProductItemPtr);
            }
        }

        m_productInvoiceItemsQuery.finish();
        return pInvoicePILResult;
    }
    //
    bool DAO::updateInvoice(const InvoicePtr &pInvoicePtr)
    {
        // bind value
        m_updateInvoiceQuery.bindValue(":invoiceid", pInvoicePtr->m_id);
        m_updateInvoiceQuery.bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
        m_updateInvoiceQuery.bindValue(":date", pInvoicePtr->m_date);
        m_updateInvoiceQuery.bindValue(":total", pInvoicePtr->m_total);
        m_updateInvoiceQuery.bindValue(":lastmodified", pInvoicePtr->m_lastModified);
        bool ok = m_updateInvoiceQuery.exec();
        if (!ok) {
            qDebug() << m_updateInvoiceQuery.lastError();
            QLOG_ERROR() << m_updateInvoiceQuery.lastError();
        }
        m_updateInvoiceQuery.finish();
        return ok;
    }
    //
    TransactionResultPtr DAO::getLastAccountInfo(Int32 memberId)
    {
        TransactionResultPtr pLastAccountInfoResultPtr(new TransactionResult);
        m_memberLastAccountInfoQuery.bindValue(":memberid", memberId);
        if (!m_memberLastAccountInfoQuery.exec())
        {
            qDebug() << m_memberLastAccountInfoQuery.lastError();
            QLOG_ERROR() << m_memberLastAccountInfoQuery.lastError();
            pLastAccountInfoResultPtr->m_error = 1;
        } else if (m_memberLastAccountInfoQuery.next())
        {
            Uint32 column = 0;
            TransactionPtr pLastAccountInfoPtr(new Transaction);
            pLastAccountInfoPtr->m_memberId = memberId;
            pLastAccountInfoPtr->m_memberUsername = m_memberLastAccountInfoQuery.value(column++).toInt();
            pLastAccountInfoPtr->m_amount = m_memberLastAccountInfoQuery.value(column++).toFloat();
            pLastAccountInfoPtr->m_date = m_memberLastAccountInfoQuery.value(column++).toDateTime();
            pLastAccountInfoPtr->m_balance = m_memberLastAccountInfoQuery.value(column++).toFloat();
            pLastAccountInfoPtr->m_descr = m_memberLastAccountInfoQuery.value(column++).toString();
            pLastAccountInfoPtr->m_type = static_cast<TransactionType>(m_memberLastAccountInfoQuery.value(column++).toUInt());
            pLastAccountInfoResultPtr->m_transaction = pLastAccountInfoPtr;
        }
        m_memberLastAccountInfoQuery.finish();
        return pLastAccountInfoResultPtr;
    }
    //
    bool DAO::insertTransaction(const TransactionPtr &pTransactionPtr)
    {
        m_insertTransactionQuery.bindValue(":memberid", pTransactionPtr->m_memberId);
        m_insertTransactionQuery.bindValue(":amount", pTransactionPtr->m_amount);
        m_insertTransactionQuery.bindValue(":date", pTransactionPtr->m_date);
        m_insertTransactionQuery.bindValue(":balance", pTransactionPtr->m_balance);
        m_insertTransactionQuery.bindValue(":description", pTransactionPtr->m_descr);
        m_insertTransactionQuery.bindValue(":type", static_cast<Int32>(pTransactionPtr->m_type));
        bool ok = m_insertTransactionQuery.exec();
        if (!ok) {
            qDebug() << m_insertTransactionQuery.lastError();
            QLOG_ERROR() << m_insertTransactionQuery.lastError();
        }
        m_insertTransactionQuery.finish();
        return ok;
    }
    //
    DepositResultPtr DAO::createDeposit(const DepositPtr &pDepositPtr)
    {
        DepositResultPtr pNewDepositResultPtr(new DepositResult);
        m_insertDepositQuery.bindValue(":memberid", pDepositPtr->m_memberId);
        m_insertDepositQuery.bindValue(":state", static_cast<Int32>(pDepositPtr->m_state));
        m_insertDepositQuery.bindValue(":date", pDepositPtr->m_date);
        m_insertDepositQuery.bindValue(":total", pDepositPtr->m_total);
        m_insertDepositQuery.bindValue(":description", pDepositPtr->m_descr);
        if (!m_insertDepositQuery.exec())
        {
            qDebug() << m_insertDepositQuery.lastError();
            QLOG_ERROR() << m_insertDepositQuery.lastError();
            pNewDepositResultPtr->m_error = 1;
        }
        m_insertDepositQuery.finish();
        if (pNewDepositResultPtr->m_error) {
            return pNewDepositResultPtr;
        }
        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        if (!m_getLastIdQuery.exec())
        {
            qDebug() << m_getLastIdQuery.lastError();
            QLOG_ERROR() << m_getLastIdQuery.lastError();
            pNewDepositResultPtr->m_error = 1;
        } else {
            m_getLastIdQuery.next();
            pNewDepositResultPtr->m_deposit = pDepositPtr;
            pNewDepositResultPtr->m_deposit->m_id = m_getLastIdQuery.value(0).toUInt();
        }
        m_getLastIdQuery.finish();
        return pNewDepositResultPtr;
    }
    //
    TransactionListResultPtr DAO::getAccountList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        TransactionListResultPtr pTransactionListResultPtr(new TransactionListResult);
        // bind value
        m_accountListQuery.bindValue(":fromDate", fromDate);
        m_accountListQuery.bindValue(":toDate", toDate);
        m_accountListQuery.bindValue(":limit", count);
        m_accountListQuery.bindValue(":offset", page * count);
        // run query
        if (!m_accountListQuery.exec())
        {
            qDebug() << m_accountListQuery.lastError();
            QLOG_ERROR() << m_accountListQuery.lastError();
            pTransactionListResultPtr->m_error = 1;
        } else {
            pTransactionListResultPtr->m_list = TransactionListPtr(new TransactionList);
            while (m_accountListQuery.next()) {
                Uint32 value = 0;
                TransactionPtr pTransactionPtr(new Transaction());
                pTransactionPtr->m_memberId = m_accountListQuery.value(value++).toInt();
                pTransactionPtr->m_memberUsername = m_accountListQuery.value(value++).toInt();
                pTransactionPtr->m_amount = m_accountListQuery.value(value++).toFloat();
                pTransactionPtr->m_date = m_accountListQuery.value(value++).toDateTime();
                pTransactionPtr->m_descr = m_accountListQuery.value(value++).toString();
                pTransactionPtr->m_balance = m_accountListQuery.value(value++).toFloat();
                pTransactionPtr->m_type = static_cast<TransactionType>(m_accountListQuery.value(value++).toUInt());
                pTransactionListResultPtr->m_list->push_back(pTransactionPtr);
            }
        }

        m_accountListQuery.finish();
        return pTransactionListResultPtr;
    }
    //
    Int32 DAO::getAccountListCount(const QDate &fromDate, const QDate &toDate)
    {
        Int32 count = 0.0;
        m_accountListCountQuery.bindValue(":fromDate", fromDate);
        m_accountListCountQuery.bindValue(":toDate", toDate);
        if (!m_accountListCountQuery.exec())
        {
            qDebug() << m_accountListCountQuery.lastError();
            QLOG_ERROR() << m_accountListCountQuery.lastError();
            count = -1;
        } else if (m_accountListCountQuery.next())
        {
            count = m_accountListCountQuery.value(0).toUInt();
        }
        m_accountListCountQuery.finish();
        return count;
    }
    //
    Float DAO::getAccountListInvoicesSum(const QDate &fromDate, const QDate &toDate)
    {
        Float count = 0.0;
        m_accountListInvoicesSumQuery.bindValue(":fromDate", fromDate);
        m_accountListInvoicesSumQuery.bindValue(":toDate", toDate);
        if (!m_accountListInvoicesSumQuery.exec())
        {
            qDebug() << m_accountListInvoicesSumQuery.lastError();
            QLOG_ERROR() << m_accountListInvoicesSumQuery.lastError();
            count = -1;
        } else if (m_accountListInvoicesSumQuery.next())
        {
            count = m_accountListInvoicesSumQuery.value(0).toInt();
        }
        m_accountListInvoicesSumQuery.finish();
        return count;
    }
    //
    Float DAO::getAccountListDepositsSum(const QDate &fromDate, const QDate &toDate)
    {
        Float count = 0.0;
        m_accountListDepositsSumQuery.bindValue(":fromDate", fromDate);
        m_accountListDepositsSumQuery.bindValue(":toDate", toDate);
        if (!m_accountListDepositsSumQuery.exec())
        {
            qDebug() << m_accountListDepositsSumQuery.lastError();
            QLOG_ERROR() << m_accountListDepositsSumQuery.lastError();
            count = -1;
        } else if (m_accountListDepositsSumQuery.next())
        {
            count = m_accountListDepositsSumQuery.value(0).toFloat();
        }
        m_accountListDepositsSumQuery.finish();
        return count;
    }
    //
    Float DAO::getAccountListBankChargesSum(const QDate &fromDate, const QDate &toDate)
    {
        Float count = 0.0;
        m_accountListBankChargesSumQuery.bindValue(":fromDate", fromDate);
        m_accountListBankChargesSumQuery.bindValue(":toDate", toDate);
        if (!m_accountListBankChargesSumQuery.exec())
        {
            qDebug() << m_accountListBankChargesSumQuery.lastError();
            QLOG_ERROR() << m_accountListBankChargesSumQuery.lastError();
            count = -1;
        } else if (m_accountListBankChargesSumQuery.next())
        {
            count = m_accountListBankChargesSumQuery.value(0).toFloat();
        }
        m_accountListBankChargesSumQuery.finish();
        return count;
    }
    //
    Int32 DAO::getAccountListByMemberIdCount(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        Uint32 count = 0.0;
        m_accountListByMemberIdCountQuery.bindValue(":memberid", memberId);
        m_accountListByMemberIdCountQuery.bindValue(":fromDate", fromDate);
        m_accountListByMemberIdCountQuery.bindValue(":toDate", toDate);
        if (!m_accountListByMemberIdCountQuery.exec())
        {
            qDebug() << m_accountListByMemberIdCountQuery.lastError();
            QLOG_ERROR() << m_accountListByMemberIdCountQuery.lastError();
            count = -1;
        } else if (m_accountListByMemberIdCountQuery.next())
        {
            count = m_accountListByMemberIdCountQuery.value(0).toUInt();
        }
        m_accountListByMemberIdCountQuery.finish();
        return count;
    }
    //
    Float DAO::getAccountListByMemberIdInvoicesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        Float count = 0.0;
        m_accountListByMemberIdInvoicesSumQuery.bindValue(":memberid", memberId);
        m_accountListByMemberIdInvoicesSumQuery.bindValue(":fromDate", fromDate);
        m_accountListByMemberIdInvoicesSumQuery.bindValue(":toDate", toDate);
        if (!m_accountListByMemberIdInvoicesSumQuery.exec())
        {
            qDebug() << m_accountListByMemberIdInvoicesSumQuery.lastError();
            QLOG_ERROR() << m_accountListByMemberIdInvoicesSumQuery.lastError();
            count = -1;
        } else if (m_accountListByMemberIdInvoicesSumQuery.next())
        {
            count = m_accountListByMemberIdInvoicesSumQuery.value(0).toFloat();
        }
        m_accountListByMemberIdInvoicesSumQuery.finish();
        return count;
    }
    //
    Float DAO::getAccountListByMemberIdDepositsSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        Float count = 0.0;
        m_accountListByMemberIdDepositsSumQuery.bindValue(":memberid", memberId);
        m_accountListByMemberIdDepositsSumQuery.bindValue(":fromDate", fromDate);
        m_accountListByMemberIdDepositsSumQuery.bindValue(":toDate", toDate);
        if (!m_accountListByMemberIdDepositsSumQuery.exec())
        {
            qDebug() << m_accountListByMemberIdDepositsSumQuery.lastError();
            QLOG_ERROR() << m_accountListByMemberIdDepositsSumQuery.lastError();
            count = -1;
        } else if (m_accountListByMemberIdDepositsSumQuery.next())
        {
            count = m_accountListByMemberIdDepositsSumQuery.value(0).toFloat();
        }
        m_accountListByMemberIdDepositsSumQuery.finish();
        return count;
    }
    //
    Float DAO::getAccountListByMemberIdBankChargesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        Float count = 0.0;
        m_accountListByMemberIdBankChargesSumQuery.bindValue(":memberid", memberId);
        m_accountListByMemberIdBankChargesSumQuery.bindValue(":fromDate", fromDate);
        m_accountListByMemberIdBankChargesSumQuery.bindValue(":toDate", toDate);
        if (!m_accountListByMemberIdBankChargesSumQuery.exec())
        {
            qDebug() << m_accountListByMemberIdBankChargesSumQuery.lastError();
            QLOG_ERROR() << m_accountListByMemberIdBankChargesSumQuery.lastError();
            count = -1;
        } else if (m_accountListByMemberIdBankChargesSumQuery.next())
        {
            count = m_accountListByMemberIdBankChargesSumQuery.value(0).toFloat();
        }
        m_accountListByMemberIdBankChargesSumQuery.finish();
        return count;
    }
    //
    TransactionListResultPtr DAO::getAccountListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        TransactionListResultPtr pTransactionListResultPtr(new TransactionListResult);
        // bind value
        m_memberAccountListQuery.bindValue(":memberid", memberId);
        m_memberAccountListQuery.bindValue(":fromDate", fromDate);
        m_memberAccountListQuery.bindValue(":toDate", toDate);
        m_memberAccountListQuery.bindValue(":limit", count);
        m_memberAccountListQuery.bindValue(":offset", page * count);
        // run query
        if (!m_memberAccountListQuery.exec())
        {
            qDebug() << m_memberAccountListQuery.lastError();
            QLOG_ERROR() << m_memberAccountListQuery.lastError();
            pTransactionListResultPtr->m_error = 1;
        } else {
            pTransactionListResultPtr->m_list = TransactionListPtr(new TransactionList);
            while (m_memberAccountListQuery.next()) {
                Uint32 value = 0;
                TransactionPtr pTransactionPtr(new Transaction());
                pTransactionPtr->m_memberId = memberId;
                pTransactionPtr->m_memberUsername = m_memberAccountListQuery.value(value++).toInt();
                pTransactionPtr->m_amount = m_memberAccountListQuery.value(value++).toFloat();
                pTransactionPtr->m_date = m_memberAccountListQuery.value(value++).toDateTime();
                pTransactionPtr->m_descr = m_memberAccountListQuery.value(value++).toString();
                pTransactionPtr->m_balance = m_memberAccountListQuery.value(value++).toFloat();
                pTransactionPtr->m_type = static_cast<TransactionType>(m_memberAccountListQuery.value(value++).toUInt());
                pTransactionListResultPtr->m_list->push_back(pTransactionPtr);
            }
        }
        m_memberAccountListQuery.finish();
        return pTransactionListResultPtr;
    }
    //
    ReservationListResultPtr DAO::getTableReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);
        // bind value
        m_tableReservationListQuery.bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
        m_tableReservationListQuery.bindValue(":dateid", now);
        // run query
        if (!m_tableReservationListQuery.exec())
        {
            qDebug() << m_tableReservationListQuery.lastError();
            QLOG_ERROR() << m_tableReservationListQuery.lastError();
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list =  ReservationListPtr(new ReservationList);
            while (m_tableReservationListQuery.next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = m_tableReservationListQuery.value(column++).toInt();
                pReservationPtr->m_idItem = m_tableReservationListQuery.value(column++).toInt();
                pReservationPtr->m_memberUsername = m_tableReservationListQuery.value(column++).toInt();
                pReservationPtr->m_memberName = m_tableReservationListQuery.value(column++).toString();
                pReservationPtr->m_memberSurname = m_tableReservationListQuery.value(column++).toString();
                pReservationPtr->m_idMember = m_tableReservationListQuery.value(column++).toInt();
                pReservationPtr->m_guestNum = m_tableReservationListQuery.value(column++).toUInt();
                pReservationPtr->m_isAdmin = m_tableReservationListQuery.value(column++).toInt() == 1;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }

        m_tableReservationListQuery.finish();
        return pReservationListResultPtr;
    }
    //
    ReservationListResultPtr DAO::getOvenReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);
        // bind value
        m_ovenReservationListQuery.bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
        m_ovenReservationListQuery.bindValue(":dateid", now);
        // run query
        if (!m_ovenReservationListQuery.exec())
        {
            qDebug() << m_ovenReservationListQuery.lastError();
            QLOG_ERROR() << m_ovenReservationListQuery.lastError();
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list = ReservationListPtr(new ReservationList);
            while (m_ovenReservationListQuery.next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = m_ovenReservationListQuery.value(column++).toInt();
                pReservationPtr->m_idItem = m_ovenReservationListQuery.value(column++).toInt();
                pReservationPtr->m_memberUsername = m_ovenReservationListQuery.value(column++).toInt();
                pReservationPtr->m_memberName = m_ovenReservationListQuery.value(column++).toString();
                pReservationPtr->m_memberSurname = m_ovenReservationListQuery.value(column++).toString();
                pReservationPtr->m_idMember = m_ovenReservationListQuery.value(column++).toInt();
                pReservationPtr->m_guestNum = 0;
                pReservationPtr->m_isAdmin = m_ovenReservationListQuery.value(column++).toInt() == 1;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }

        m_ovenReservationListQuery.finish();
        return pReservationListResultPtr;
    }
    //
    ReservationListResultPtr DAO::getFireplaceReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);
        // bind value
        m_fireplaceReservationListQuery.bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
        m_fireplaceReservationListQuery.bindValue(":dateid", now);
        // run query
        if (!m_fireplaceReservationListQuery.exec())
        {
            qDebug() << m_fireplaceReservationListQuery.lastError();
            QLOG_ERROR() << m_fireplaceReservationListQuery.lastError();
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list = ReservationListPtr(new ReservationList);
            while (m_fireplaceReservationListQuery.next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = m_fireplaceReservationListQuery.value(column++).toInt();
                pReservationPtr->m_idItem = m_fireplaceReservationListQuery.value(column++).toInt();
                pReservationPtr->m_memberUsername = m_fireplaceReservationListQuery.value(column++).toInt();
                pReservationPtr->m_memberName = m_fireplaceReservationListQuery.value(column++).toString();
                pReservationPtr->m_memberSurname = m_fireplaceReservationListQuery.value(column++).toString();
                pReservationPtr->m_idMember = m_fireplaceReservationListQuery.value(column++).toInt();
                pReservationPtr->m_isAdmin = m_fireplaceReservationListQuery.value(column++).toInt() == 1;
                pReservationPtr->m_guestNum = 0;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }
        m_fireplaceReservationListQuery.finish();
        return pReservationListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getLunchTableList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);
        // run query
        if (!m_lunchTablesListQuery.exec())
        {
            qDebug() << m_lunchTablesListQuery.lastError();
            QLOG_ERROR() << m_lunchTablesListQuery.lastError();
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (m_lunchTablesListQuery.next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::LunchTableType;
                pReservationItemPtr->m_idItem = m_lunchTablesListQuery.value(0).toInt();
                pReservationItemPtr->m_itemName = m_lunchTablesListQuery.value(1).toString();
                pReservationItemPtr->m_guestNum = m_lunchTablesListQuery.value(2).toUInt();
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        m_lunchTablesListQuery.finish();
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getOvenList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);
        // run query
        if (!m_ovenListQuery.exec())
        {
            qDebug() << m_ovenListQuery.lastError();
            QLOG_ERROR() << m_ovenListQuery.lastError();
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (m_ovenListQuery.next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::OvenType;
                pReservationItemPtr->m_idItem = m_ovenListQuery.value(0).toInt();
                pReservationItemPtr->m_itemName = m_ovenListQuery.value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        m_ovenListQuery.finish();
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getFireplaceList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);
        // run query
        if (!m_fireplaceListQuery.exec())
        {
            qDebug() << m_fireplaceListQuery.lastError();
            QLOG_ERROR() << m_fireplaceListQuery.lastError();
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (m_fireplaceListQuery.next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::FireplaceType;
                pReservationItemPtr->m_idItem = m_fireplaceListQuery.value(0).toInt();
                pReservationItemPtr->m_itemName = m_fireplaceListQuery.value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        m_fireplaceListQuery.finish();
        return pReservationItemListResultPtr;
    }
    //
    bool DAO::makeTableReservation(const QDate &date, ReservationType reservationType, Uint16 guestNum, Int32 memberId, Int32 idTable, bool isAdmin)
    {
        m_insertTableReservationQuery.bindValue(":date", date);
        m_insertTableReservationQuery.bindValue(":reservationtype", static_cast<Uint16>(reservationType));
        m_insertTableReservationQuery.bindValue(":guestnum", guestNum);
        m_insertTableReservationQuery.bindValue(":idmember", memberId);
        m_insertTableReservationQuery.bindValue(":idtable", idTable);
        m_insertTableReservationQuery.bindValue(":isadmin", (isAdmin)?(1):(0));
        bool ok = m_insertTableReservationQuery.exec();
        if (!ok) {
            qDebug() << m_insertTableReservationQuery.lastError();
            QLOG_ERROR() << m_insertTableReservationQuery.lastError();
        }
        m_insertTableReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::updateTableReservation(Int32 reservationId, bool isAdmin)
    {
        m_updateTableReservationQuery.bindValue(":idreservation", reservationId);
        m_updateTableReservationQuery.bindValue(":isadmin", (isAdmin)?(1):(0));
        bool ok = m_updateTableReservationQuery.exec();
        if (!ok) {
            qDebug() << m_updateTableReservationQuery.lastError();
            QLOG_ERROR() << m_updateTableReservationQuery.lastError();
        }
        m_updateTableReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::cancelTableReservation(Int32 reservationId)
    {
        m_cancelTableReservationQuery.bindValue(":idreservation", reservationId);
        bool ok = m_cancelTableReservationQuery.exec();
        if (!ok) {
            qDebug() << m_cancelTableReservationQuery.lastError();
            QLOG_ERROR() << m_cancelTableReservationQuery.lastError();
        }
        m_cancelTableReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::makeOvenReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idOven, bool isAdmin)
    {
        m_insertOvenReservationQuery.bindValue(":date", date);
        m_insertOvenReservationQuery.bindValue(":reservationtype", static_cast<Uint16>(reservationType));
        m_insertOvenReservationQuery.bindValue(":idmember", memberId);
        m_insertOvenReservationQuery.bindValue(":idoven", idOven);
        m_insertOvenReservationQuery.bindValue(":isadmin", (isAdmin)?(1):(0));
        bool ok = m_insertOvenReservationQuery.exec();
        if (!ok) {
            qDebug() << m_insertOvenReservationQuery.lastError();
            QLOG_ERROR() << m_insertOvenReservationQuery.lastError();
        }
        m_insertOvenReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::updateOvenReservation(Int32 reservationId, bool isAdmin)
    {
        m_updateOvenReservationQuery.bindValue(":idreservation", reservationId);
        m_updateOvenReservationQuery.bindValue(":isadmin", (isAdmin)?(1):(0));
        bool ok = m_updateOvenReservationQuery.exec();
        if (!ok) {
            qDebug() << m_updateOvenReservationQuery.lastError();
            QLOG_ERROR() << m_updateOvenReservationQuery.lastError();
        }
        m_updateOvenReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::cancelOvenReservation(Int32 reservationId)
    {
        m_cancelOvenReservationQuery.bindValue(":idreservation", reservationId);
        bool ok = m_cancelOvenReservationQuery.exec();
        if (!ok) {
            qDebug() << m_cancelOvenReservationQuery.lastError();
            QLOG_ERROR() << m_cancelOvenReservationQuery.lastError();
        }
        m_cancelOvenReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::updateFireplaceReservation(Int32 reservationId, bool isAdmin)
    {
        m_updateFireplaceReservationQuery.bindValue(":idreservation", reservationId);
        m_updateFireplaceReservationQuery.bindValue(":isadmin", (isAdmin)?(1):(0));
        bool ok = m_updateFireplaceReservationQuery.exec();
        if (!ok) {
            qDebug() << m_updateFireplaceReservationQuery.lastError();
            QLOG_ERROR() << m_updateFireplaceReservationQuery.lastError();
        }
        m_updateFireplaceReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::makeFireplaceReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idFireplace, bool isAdmin)
    {
        m_insertFireplaceReservationQuery.bindValue(":date", date);
        m_insertFireplaceReservationQuery.bindValue(":reservationtype", static_cast<Uint16>(reservationType));
        m_insertFireplaceReservationQuery.bindValue(":idmember", memberId);
        m_insertFireplaceReservationQuery.bindValue(":idfireplace", idFireplace);
        m_insertFireplaceReservationQuery.bindValue(":isadmin", (isAdmin)?(1):(0));
        bool ok = m_insertFireplaceReservationQuery.exec();
        if (!ok) {
            qDebug() << m_insertFireplaceReservationQuery.lastError();
            QLOG_ERROR() << m_insertFireplaceReservationQuery.lastError();
        }
        m_insertFireplaceReservationQuery.finish();
        return ok;
    }
    //
    bool DAO::cancelFireplaceReservation(Int32 reservationId)
    {
        m_cancelFireplaceReservationQuery.bindValue(":idreservation", reservationId);
        bool ok = m_cancelFireplaceReservationQuery.exec();
        if (!ok) {
            qDebug() << m_cancelFireplaceReservationQuery.lastError();
            QLOG_ERROR() << m_cancelFireplaceReservationQuery.lastError();
        }
        m_cancelFireplaceReservationQuery.finish();
        return ok;
    }
    //
    MemberListResultPtr DAO::getSlowPayersList()
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);
        // only active members
        if (!m_slowPayersQuery.exec())
        {
            qDebug() << m_slowPayersQuery.lastError();
            QLOG_ERROR() << m_slowPayersQuery.lastError();
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (m_slowPayersQuery.next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  m_slowPayersQuery.value(column++).toInt();
                pMemberPtr->m_username =  m_slowPayersQuery.value(column++).toInt();
                pMemberPtr->m_name =  m_slowPayersQuery.value(column++).toString();
                pMemberPtr->m_surname =  m_slowPayersQuery.value(column++).toString();
                pMemberPtr->m_imagePath =  m_slowPayersQuery.value(column++).toString();
                pMemberPtr->m_balance =  m_slowPayersQuery.value(column++).toFloat();
                pMemberPtr->m_lastModified =  m_slowPayersQuery.value(column++).toDateTime();
                pMemberPtr->m_regDate =  m_slowPayersQuery.value(column++).toDateTime();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        m_slowPayersQuery.finish();
        return pMemberListResultPtr;
    }
    //
    InvoiceListResultPtr DAO::getInvoiceListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceListResultPtr pInvoiceListResultPtr(new InvoiceListResult);
        // only active invoices
        m_invoiceListByMemberIdQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListByMemberIdQuery.bindValue(":memberid", memberId);
        m_invoiceListByMemberIdQuery.bindValue(":fromDate", fromDate);
        m_invoiceListByMemberIdQuery.bindValue(":toDate", toDate);
        m_invoiceListByMemberIdQuery.bindValue(":limit", count);
        m_invoiceListByMemberIdQuery.bindValue(":offset", page * count);
        if (!m_invoiceListByMemberIdQuery.exec())
        {
            qDebug() << m_invoiceListByMemberIdQuery.lastError();
            QLOG_ERROR() << m_invoiceListByMemberIdQuery.lastError();
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = InvoiceListPtr(new InvoiceList);
            while (m_invoiceListByMemberIdQuery.next()) {
                Uint32 column = 0;
                InvoicePtr pInvoicePtr(new Invoice);
                pInvoicePtr->m_memberUsername = m_invoiceListByMemberIdQuery.value(column++).toInt();
                pInvoicePtr->m_id =  m_invoiceListByMemberIdQuery.value(column++).toInt();
                pInvoicePtr->m_memberId =  memberId;
                pInvoicePtr->m_state =  InvoiceState::Closed;
                pInvoicePtr->m_date =  m_invoiceListByMemberIdQuery.value(column++).toDateTime();
                pInvoicePtr->m_total =  m_invoiceListByMemberIdQuery.value(column++).toFloat();
                pInvoicePtr->m_lastModified =  m_invoiceListByMemberIdQuery.value(column++).toDateTime();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        m_invoiceListByMemberIdQuery.finish();
        return pInvoiceListResultPtr;
    }
    //
    InvoiceListStatsResultPtr DAO::getInvoiceListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        InvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new InvoiceListStatsResult);

        // only active invoices
        m_invoiceListByMemberIdStatsQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListByMemberIdStatsQuery.bindValue(":memberid", memberId);
        m_invoiceListByMemberIdStatsQuery.bindValue(":fromDate", fromDate);
        m_invoiceListByMemberIdStatsQuery.bindValue(":toDate", toDate);
        if (!m_invoiceListByMemberIdStatsQuery.exec())
        {
            qDebug() << m_invoiceListByMemberIdStatsQuery.lastError();
            QLOG_ERROR() << m_invoiceListByMemberIdStatsQuery.lastError();
            pInvoiceListStatsResultPtr->m_error = 1;
        } else {
            pInvoiceListStatsResultPtr->m_stats = InvoiceListStatsPtr(new InvoiceListStats);
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices= 0;
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = 0;
            m_invoiceListByMemberIdStatsQuery.next();
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = m_invoiceListByMemberIdStatsQuery.value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = m_invoiceListByMemberIdStatsQuery.value(1).toFloat();
        }
        m_invoiceListByMemberIdStatsQuery.finish();
        return pInvoiceListStatsResultPtr;
    }
    //
    InvoiceListResultPtr DAO::getInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceListResultPtr pInvoiceListResultPtr(new InvoiceListResult);
        // only active invoices
        m_invoiceListQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListQuery.bindValue(":fromDate", fromDate);
        m_invoiceListQuery.bindValue(":toDate", toDate);
        m_invoiceListQuery.bindValue(":limit", count);
        m_invoiceListQuery.bindValue(":offset", page * count);
        if (!m_invoiceListQuery.exec())
        {
            qDebug() << m_invoiceListQuery.lastError();
            QLOG_ERROR() << m_invoiceListQuery.lastError();
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = InvoiceListPtr(new InvoiceList);
            while (m_invoiceListQuery.next()) {
                InvoicePtr pInvoicePtr(new Invoice);
                Uint32 column = 0;
                pInvoicePtr->m_memberUsername = m_invoiceListQuery.value(column++).toInt();
                pInvoicePtr->m_id = m_invoiceListQuery.value(column++).toInt();
                pInvoicePtr->m_memberId = m_invoiceListQuery.value(column++).toInt();
                pInvoicePtr->m_state = InvoiceState::Closed;
                pInvoicePtr->m_date = m_invoiceListQuery.value(column++).toDateTime();
                pInvoicePtr->m_total = m_invoiceListQuery.value(column++).toFloat();
                pInvoicePtr->m_lastModified = m_invoiceListQuery.value(column++).toDateTime();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        m_invoiceListQuery.finish();
        return pInvoiceListResultPtr;
    }
    //
    InvoiceListStatsResultPtr DAO::getInvoiceListStats(const QDate &fromDate, const QDate &toDate)
    {
        InvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new InvoiceListStatsResult);
        // only active invoices
        m_invoiceListStatsQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListStatsQuery.bindValue(":fromDate", fromDate);
        m_invoiceListStatsQuery.bindValue(":toDate", toDate);
        if (!m_invoiceListStatsQuery.exec())
        {
            qDebug() << m_invoiceListStatsQuery.lastError();
            QLOG_ERROR() << m_invoiceListStatsQuery.lastError();
            pInvoiceListStatsResultPtr->m_error = 1;
        } else {
            pInvoiceListStatsResultPtr->m_stats = InvoiceListStatsPtr(new InvoiceListStats);
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices= 0;
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = 0;
            m_invoiceListStatsQuery.next();
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = m_invoiceListStatsQuery.value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = m_invoiceListStatsQuery.value(1).toFloat();
        }
        m_invoiceListStatsQuery.finish();
        return pInvoiceListStatsResultPtr;
    }
    //
    ProviderListResultPtr DAO::getProviderList()
    {
        ProviderListResultPtr pProviderListResultPtr(new ProviderListResult);
        // run query
        if (!m_providerListQuery.exec())
        {
            qDebug() << m_providerListQuery.lastError();
            QLOG_ERROR() << m_providerListQuery.lastError();
            pProviderListResultPtr->m_error = 1;
        } else {
            pProviderListResultPtr->m_list = ProviderListPtr(new ProviderList);
            while (m_providerListQuery.next()) {
                ProviderPtr pProviderPtr(new Provider);
                pProviderPtr->m_id = m_providerListQuery.value(0).toInt();
                pProviderPtr->m_name = m_providerListQuery.value(1).toString();
                pProviderPtr->m_image = m_providerListQuery.value(2).toString();
                pProviderPtr->m_regDate = m_providerListQuery.value(3).toDateTime();
                pProviderPtr->m_phone = m_providerListQuery.value(4).toString();
                pProviderListResultPtr->m_list->push_back(pProviderPtr);
            }
        }
        m_providerListQuery.finish();
        return pProviderListResultPtr;
    }
    //
    ProductItemListResultPtr DAO::getProductsFromProvider(Int32 providerId)
    {
        ProductItemListResultPtr pIListResultPtr(new ProductItemListResult);
        // bind value
        m_productItemsByProviderQuery.bindValue(":providerId", providerId);
        // run query
        if (!m_productItemsByProviderQuery.exec())
        {
            qDebug() << m_productItemsByProviderQuery.lastError();
            QLOG_ERROR() << m_productItemsByProviderQuery.lastError();
            pIListResultPtr->m_error = 1;

        } else {
            pIListResultPtr->m_list = ProductItemListPtr(new ProductItemList);
            while (m_productItemsByProviderQuery.next()) {
                ProductItemPtr pfPtr(new ProductItem);
                pfPtr->m_id = m_productItemsByProviderQuery.value(0).toUInt();
                pfPtr->m_name = m_productItemsByProviderQuery.value(1).toString();
                pfPtr->m_imagePath = m_productItemsByProviderQuery.value(2).toString();
                pfPtr->m_active = true;
                pfPtr->m_regDate = m_productItemsByProviderQuery.value(3).toDateTime();
                pfPtr->m_familyId = m_productItemsByProviderQuery.value(4).toInt();
                pfPtr->m_price = m_productItemsByProviderQuery.value(5).toFloat();
                pIListResultPtr->m_list->push_back(pfPtr);
            }
        }
        m_productFamiliesQuery.finish();
        return pIListResultPtr;
    }
    //
    bool DAO::createProvider(const QString &name, const QString &imageFileName, const QString &phone)
    {
        QDate today(QDateTime::currentDateTime().date());
        m_createProviderQuery.bindValue(":name", name);
        if (imageFileName.isEmpty()) {
            m_createProviderQuery.bindValue(":image", QVariant());
        } else {
            m_createProviderQuery.bindValue(":image", imageFileName);
        }
        m_createProviderQuery.bindValue(":reg_date", today);
        if (phone.isEmpty()) {
            m_createProviderQuery.bindValue(":phone", QVariant());
        } else {
            m_createProviderQuery.bindValue(":phone", phone);
        }
        bool ok = m_createProviderQuery.exec();
        if (!ok) {
            qDebug() << m_createProviderQuery.lastError();
            QLOG_ERROR() << m_createProviderQuery.lastError();
        }
        m_createProviderQuery.finish();
        return ok;
    }
    //
    ProductItemListResultPtr DAO::getProductsList(Uint32 page, Uint32 count)
    {
        ProductItemListResultPtr pIListResultPtr(new ProductItemListResult);
        // only active invoices
        m_productItemListQuery.bindValue(":limit", count);
        m_productItemListQuery.bindValue(":offset", page * count);
        if (!m_productItemListQuery.exec())
        {
            qDebug() << m_productItemListQuery.lastError();
            QLOG_ERROR() << m_productItemListQuery.lastError();
            pIListResultPtr->m_error = 1;
        } else {
            pIListResultPtr->m_list = ProductItemListPtr(new ProductItemList);
            while (m_productItemListQuery.next()) {
                ProductItemPtr pProductItemPtr(new ProductItem);
                pProductItemPtr->m_id =  m_productItemListQuery.value(0).toInt();
                pProductItemPtr->m_name =  m_productItemListQuery.value(1).toString();
                pProductItemPtr->m_active =  m_productItemListQuery.value(2).toInt() == 1;
                pProductItemPtr->m_imagePath =  m_productItemListQuery.value(3).toString();
                pProductItemPtr->m_regDate =  m_productItemListQuery.value(4).toDateTime();
                pProductItemPtr->m_price =  m_productItemListQuery.value(5).toFloat();
                pProductItemPtr->m_familyId =  m_productItemListQuery.value(6).toInt();
                pProductItemPtr->m_providerId =  m_productItemListQuery.value(7).toInt();
                pProductItemPtr->m_stock =  m_productItemListQuery.value(8).toInt();
                pIListResultPtr->m_list->push_back(pProductItemPtr);
            }
        }
        m_productItemListQuery.finish();
        return pIListResultPtr;
    }
    //
    ProductListStatsResultPtr DAO::getProductsListStats()
    {
        ProductListStatsResultPtr pProductListStatsResultPtr(new ProductListStatsResult);
        if (!m_productItemsStatsQuery.exec())
        {
            qDebug() << m_productItemsStatsQuery.lastError();
            QLOG_ERROR() << m_productItemsStatsQuery.lastError();
            pProductListStatsResultPtr->m_error = 1;
        } else {
            pProductListStatsResultPtr->m_stats = ProductListStatsPtr(new ProductListStats);
            m_productItemsStatsQuery.next();
            pProductListStatsResultPtr->m_stats->m_totalNumProducts = m_productItemsStatsQuery.value(0).toUInt();
        }
        m_productItemsStatsQuery.finish();
        return pProductListStatsResultPtr;
    }
    //
    bool DAO::updateStock(Int32 productItemId, Int32 count)
    {
        m_updateStockQuery.bindValue(":count", count);
        m_updateStockQuery.bindValue(":productid", productItemId);
        bool ok = m_updateStockQuery.exec();
        if (!ok) {
            qDebug() << m_updateStockQuery.lastError();
            QLOG_ERROR() << m_updateStockQuery.lastError();
        }
        m_updateStockQuery.finish();
        return ok;
    }
    //
    ProductItemResultPtr DAO::getProductItem(Int32 productItemId)
    {
        ProductItemResultPtr pProductItemResultPtr(new ProductItemResult);
        m_productItemQuery.bindValue(":productid", productItemId);
        if (!m_productItemQuery.exec())
        {
            qDebug() << m_productItemQuery.lastError();
            QLOG_ERROR() << m_productItemQuery.lastError();
            pProductItemResultPtr->m_error = 1;
        } else {
            ProductItemPtr pProductItemPtr(new ProductItem);
            m_productItemQuery.next();
            pProductItemPtr->m_id = productItemId;
            pProductItemPtr->m_name = m_productItemQuery.value(0).toString();
            pProductItemPtr->m_active =  m_productItemQuery.value(1).toInt() == 1;
            pProductItemPtr->m_imagePath = m_productItemQuery.value(2).toString();
            pProductItemPtr->m_regDate = m_productItemQuery.value(3).toDateTime();
            pProductItemPtr->m_price = m_productItemQuery.value(4).toFloat();
            pProductItemPtr->m_familyId = m_productItemQuery.value(5).toInt();
            pProductItemPtr->m_providerId = m_productItemQuery.value(6).toInt();
            pProductItemPtr->m_stock = m_productItemQuery.value(7).toInt();
            pProductItemResultPtr->m_item = pProductItemPtr;
        }
        m_productItemQuery.finish();
        return pProductItemResultPtr;
    }
    //
    bool DAO::updateProductItem(const ProductItemPtr &pProductPtr)
    {
        m_updateProductItemQuery.bindValue(":name", pProductPtr->m_name);
        m_updateProductItemQuery.bindValue(":image", pProductPtr->m_imagePath);
        m_updateProductItemQuery.bindValue(":active", (pProductPtr->m_active)?(1):(0));
        m_updateProductItemQuery.bindValue(":familyid", pProductPtr->m_familyId);
        m_updateProductItemQuery.bindValue(":price", pProductPtr->m_price);
        m_updateProductItemQuery.bindValue(":providerid", pProductPtr->m_providerId);
        m_updateProductItemQuery.bindValue(":stock", pProductPtr->m_stock);
        m_updateProductItemQuery.bindValue(":productid", pProductPtr->m_id);
        bool ok = m_updateProductItemQuery.exec();
        if (!ok) {
            qDebug() << m_updateProductItemQuery.lastError();
            QLOG_ERROR() << m_updateProductItemQuery.lastError();
        }
        m_updateProductItemQuery.finish();
        return ok;
    }
    //
    Int32 DAO::createProductItem(const ProductItemPtr &pProductPtr)
    {
        Int32 itemId = -1;
        m_createProductItemQuery.bindValue(":name", pProductPtr->m_name);
        m_createProductItemQuery.bindValue(":image", pProductPtr->m_imagePath);
        m_createProductItemQuery.bindValue(":active", (pProductPtr->m_active)?(1):(0));
        m_createProductItemQuery.bindValue(":reg_date", pProductPtr->m_regDate);
        m_createProductItemQuery.bindValue(":familyid", pProductPtr->m_familyId);
        m_createProductItemQuery.bindValue(":price", pProductPtr->m_price);
        m_createProductItemQuery.bindValue(":providerid", pProductPtr->m_providerId);
        m_createProductItemQuery.bindValue(":stock", pProductPtr->m_stock);
        bool ok = m_createProductItemQuery.exec();
        if (!ok) {
            qDebug() << m_createProductItemQuery.lastError();
            QLOG_ERROR() << m_createProductItemQuery.lastError();
        }
        m_createProductItemQuery.finish();
        if (ok) {
            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            ok = m_getLastIdQuery.exec();
            if (!ok) {
                qDebug() << m_getLastIdQuery.lastError();
                QLOG_ERROR() << m_getLastIdQuery.lastError();
            } else {
                m_getLastIdQuery.next();
                itemId = m_getLastIdQuery.value(0).toUInt();
            }
            m_getLastIdQuery.finish();
        }

        return itemId;
    }
    //
    ProductFamilyResultPtr DAO::getProductFamily(Int32 familyId)
    {
        ProductFamilyResultPtr pProductFamilyResultPtr(new ProductFamilyResult);
        m_productFamilyItemQuery.bindValue(":familyid", familyId);
        if (!m_productFamilyItemQuery.exec())
        {
            qDebug() << m_productFamilyItemQuery.lastError();
            QLOG_ERROR() << m_productFamilyItemQuery.lastError();
            pProductFamilyResultPtr->m_error = 1;
        } else {
            ProductFamilyPtr pProductFamilyPtr(new ProductFamily);
            m_productFamilyItemQuery.next();
            pProductFamilyPtr->m_id = familyId;
            pProductFamilyPtr->m_name = m_productFamilyItemQuery.value(0).toString();
            pProductFamilyPtr->m_active =  m_productFamilyItemQuery.value(1).toInt() == 1;
            pProductFamilyPtr->m_imagePath = m_productFamilyItemQuery.value(2).toString();
            pProductFamilyPtr->m_regDate = m_productFamilyItemQuery.value(3).toDateTime();
            pProductFamilyResultPtr->m_family = pProductFamilyPtr;
        }
        m_productFamilyItemQuery.finish();
        return pProductFamilyResultPtr;
    }
    //
    bool DAO::updateProductFamilyItem(const ProductFamilyPtr &pFamilyPtr)
    {
        m_updateProductFamilyItemQuery.bindValue(":name", pFamilyPtr->m_name);
        m_updateProductFamilyItemQuery.bindValue(":image", pFamilyPtr->m_imagePath);
        m_updateProductFamilyItemQuery.bindValue(":active", (pFamilyPtr->m_active)?(1):(0));
        m_updateProductFamilyItemQuery.bindValue(":familyid", pFamilyPtr->m_id);
        bool ok = m_updateProductFamilyItemQuery.exec();
        if (!ok) {
            qDebug() << m_updateProductFamilyItemQuery.lastError();
            QLOG_ERROR() << m_updateProductFamilyItemQuery.lastError();
        }
        m_updateProductFamilyItemQuery.finish();
        return ok;
    }
    //
    Int32 DAO::createProductFamilyItem(const ProductFamilyPtr &pFamilyPtr)
    {
        Int32 familyId = -1;
        m_createProductFamilyItemQuery.bindValue(":name", pFamilyPtr->m_name);
        m_createProductFamilyItemQuery.bindValue(":image", pFamilyPtr->m_imagePath);
        m_createProductFamilyItemQuery.bindValue(":active", (pFamilyPtr->m_active)?(1):(0));
        m_createProductFamilyItemQuery.bindValue(":reg_date", pFamilyPtr->m_regDate);
        bool ok = m_createProductFamilyItemQuery.exec();
        if (!ok) {
            qDebug() << m_createProductFamilyItemQuery.lastError();
            QLOG_ERROR() << m_createProductFamilyItemQuery.lastError();
        }
        m_createProductFamilyItemQuery.finish();

        if (ok) {
            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            if (!m_getLastIdQuery.exec())
            {
                qDebug() << m_getLastIdQuery.lastError();
                QLOG_ERROR() << m_getLastIdQuery.lastError();
            } else {
                m_getLastIdQuery.next();
                familyId = m_getLastIdQuery.value(0).toUInt();
            }
            m_getLastIdQuery.finish();
        }

        return familyId;
    }
    //
    InvoiceProductItemListResultPtr DAO::getProductExpensesList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr(new InvoiceProductItemListResult);
        // only active invoices
        m_productExpensesListQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListQuery.bindValue(":toDate", toDate);
        m_productExpensesListQuery.bindValue(":limit", count);
        m_productExpensesListQuery.bindValue(":offset", page * count);
        if (!m_productExpensesListQuery.exec())
        {
            qDebug() << m_productExpensesListQuery.lastError();
            QLOG_ERROR() << m_productExpensesListQuery.lastError();
            pInvoiceProductItemListResultPtr->m_error = 1;
        } else {
            pInvoiceProductItemListResultPtr->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (m_productExpensesListQuery.next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId =  m_productExpensesListQuery.value(0).toInt();
                pInvoiceProductItemPtr->m_productname =  m_productExpensesListQuery.value(1).toString();
                pInvoiceProductItemPtr->m_imagePath =  m_productExpensesListQuery.value(2).toString();
                pInvoiceProductItemPtr->m_priceperunit =  m_productExpensesListQuery.value(3).toFloat();
                pInvoiceProductItemPtr->m_count =  m_productExpensesListQuery.value(4).toUInt();
                pInvoiceProductItemListResultPtr->m_list->push_back(pInvoiceProductItemPtr);
            }
        }
        m_productExpensesListQuery.finish();
        return pInvoiceProductItemListResultPtr;
    }
    //
    InvoiceProductItemStatsResultPtr DAO::getProductExpensesListStats(const QDate &fromDate, const QDate &toDate)
    {
        InvoiceProductItemStatsResultPtr pIPISResultPtr(new InvoiceProductItemStatsResult);
        m_productExpensesListStatsQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListStatsQuery.bindValue(":toDate", toDate);
        if (!m_productExpensesListStatsQuery.exec())
        {
            qDebug() << m_productExpensesListStatsQuery.lastError();
            QLOG_ERROR() << m_productExpensesListStatsQuery.lastError();
            pIPISResultPtr->m_error = 1;
        } else {
            pIPISResultPtr->m_stats = InvoiceProductItemStatsPtr(new InvoiceProductItemStats);
            m_productExpensesListStatsQuery.next();
            pIPISResultPtr->m_stats->m_totalProducts = m_productExpensesListStatsQuery.value(0).toUInt();
        }
        m_productExpensesListStatsQuery.finish();
        return pIPISResultPtr;
    }
    //
    InvoiceProductItemListResultPtr DAO::getProductExpensesListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceProductItemListResultPtr pIPILResult(new InvoiceProductItemListResult);
        m_productExpensesListByMemberIdQuery.bindValue(":memberid", memberId);
        m_productExpensesListByMemberIdQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListByMemberIdQuery.bindValue(":toDate", toDate);
        m_productExpensesListByMemberIdQuery.bindValue(":limit", count);
        m_productExpensesListByMemberIdQuery.bindValue(":offset", page * count);
        if (!m_productExpensesListByMemberIdQuery.exec())
        {
            qDebug() << m_productExpensesListByMemberIdQuery.lastError();
            QLOG_ERROR() << m_productExpensesListByMemberIdQuery.lastError();
            pIPILResult->m_error = 1;
        } else {
            pIPILResult->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (m_productExpensesListByMemberIdQuery.next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId =  m_productExpensesListByMemberIdQuery.value(0).toInt();
                pInvoiceProductItemPtr->m_productname =  m_productExpensesListByMemberIdQuery.value(1).toString();
                pInvoiceProductItemPtr->m_imagePath =  m_productExpensesListByMemberIdQuery.value(2).toString();
                pInvoiceProductItemPtr->m_priceperunit =  m_productExpensesListByMemberIdQuery.value(3).toFloat();
                pInvoiceProductItemPtr->m_count =  m_productExpensesListByMemberIdQuery.value(4).toUInt();
                pIPILResult->m_list->push_back(pInvoiceProductItemPtr);
            }
        }
        m_productExpensesListByMemberIdQuery.finish();
        return pIPILResult;
    }
    //
    InvoiceProductItemStatsResultPtr DAO::getProductExpensesListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        InvoiceProductItemStatsResultPtr pIPISResult(new InvoiceProductItemStatsResult);
        m_productExpensesListByMemberIdStatsQuery.bindValue(":memberid", memberId);
        m_productExpensesListByMemberIdStatsQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListByMemberIdStatsQuery.bindValue(":toDate", toDate);
        if (!m_productExpensesListByMemberIdStatsQuery.exec())
        {
            qDebug() << m_productExpensesListByMemberIdStatsQuery.lastError();
            QLOG_ERROR() << m_productExpensesListByMemberIdStatsQuery.lastError();
            pIPISResult->m_error = 1;
        } else {
            pIPISResult->m_stats = InvoiceProductItemStatsPtr(new InvoiceProductItemStats);
            m_productExpensesListByMemberIdStatsQuery.next();
            pIPISResult->m_stats->m_totalProducts = m_productExpensesListByMemberIdStatsQuery.value(0).toUInt();
        }
        m_productExpensesListByMemberIdStatsQuery.finish();
        return pIPISResult;
    }
    //
    bool DAO::createProviderInvoice(const ProviderInvoicePtr &pProviderInvoicePtr)
    {
        m_createProviderInvoiceQuery.bindValue(":id", pProviderInvoicePtr->m_id);
        m_createProviderInvoiceQuery.bindValue(":date", pProviderInvoicePtr->m_regDate);
        m_createProviderInvoiceQuery.bindValue(":total", pProviderInvoicePtr->m_total);
        m_createProviderInvoiceQuery.bindValue(":providerid", pProviderInvoicePtr->m_providerid);
        bool ok = m_createProviderInvoiceQuery.exec();
        if (!ok) {
            qDebug() << m_createProviderInvoiceQuery.lastError();
            QLOG_ERROR() << m_createProviderInvoiceQuery.lastError();
        }
        m_createProviderInvoiceQuery.finish();
        return ok;
    }
    //
    bool DAO::createProviderInvoiceProduct(const QString &invoiceId, Int32 productId, Uint32 count)
    {
        m_createProviderInvoiceProductQuery.bindValue(":providerinvoiceid", invoiceId);
        m_createProviderInvoiceProductQuery.bindValue(":productid", productId);
        m_createProviderInvoiceProductQuery.bindValue(":count", count);
        bool ok = m_createProviderInvoiceProductQuery.exec();
        if (!ok) {
            qDebug() << m_createProviderInvoiceProductQuery.lastError();
            QLOG_ERROR() << m_createProviderInvoiceProductQuery.lastError();
        }
        m_createProviderInvoiceProductQuery.finish();
        return ok;
    }
    //
    ProviderInvoiceListResultPtr DAO::getProviderInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        ProviderInvoiceListResultPtr pInvoiceListResultPtr(new ProviderInvoiceListResult);
        m_providerInvoiceListQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListQuery.bindValue(":toDate", toDate);
        m_providerInvoiceListQuery.bindValue(":limit", count);
        m_providerInvoiceListQuery.bindValue(":offset", page * count);
        if (!m_providerInvoiceListQuery.exec())
        {
            qDebug() << m_providerInvoiceListQuery.lastError();
            QLOG_ERROR() << m_providerInvoiceListQuery.lastError();
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = ProviderInvoiceListPtr(new ProviderInvoiceList);
            while (m_providerInvoiceListQuery.next()) {
                ProviderInvoicePtr pInvoicePtr(new ProviderInvoice);
                pInvoicePtr->m_id = m_providerInvoiceListQuery.value(0).toString();
                pInvoicePtr->m_regDate = m_providerInvoiceListQuery.value(1).toDate();
                pInvoicePtr->m_total = m_providerInvoiceListQuery.value(2).toFloat();
                pInvoicePtr->m_providerid = m_providerInvoiceListQuery.value(3).toInt();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        m_providerInvoiceListQuery.finish();
        return pInvoiceListResultPtr;
    }
    //
    ProviderInvoiceListStatsResultPtr DAO::getProviderInvoiceListStats(const QDate &fromDate, const QDate &toDate)
    {
        ProviderInvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new ProviderInvoiceListStatsResult);
        m_providerInvoiceListStatsQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListStatsQuery.bindValue(":toDate", toDate);
        if (!m_providerInvoiceListStatsQuery.exec())
        {
            qDebug() << m_providerInvoiceListStatsQuery.lastError();
            QLOG_ERROR() << m_providerInvoiceListStatsQuery.lastError();
            pInvoiceListStatsResultPtr->m_error = 1;
        } else {
            pInvoiceListStatsResultPtr->m_stats = ProviderInvoiceListStatsPtr(new ProviderInvoiceListStats);
            m_providerInvoiceListStatsQuery.next();
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = m_providerInvoiceListStatsQuery.value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = m_providerInvoiceListStatsQuery.value(1).toFloat();
        }
        m_providerInvoiceListStatsQuery.finish();
        return pInvoiceListStatsResultPtr;
    }
    //
    ProviderInvoiceListResultPtr DAO::getProviderInvoiceListByProviderId(Int32 providerId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        ProviderInvoiceListResultPtr pInvoiceListResultPtr(new ProviderInvoiceListResult);
        m_providerInvoiceListByProviderIdQuery.bindValue(":providerid", providerId);
        m_providerInvoiceListByProviderIdQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListByProviderIdQuery.bindValue(":toDate", toDate);
        m_providerInvoiceListByProviderIdQuery.bindValue(":limit", count);
        m_providerInvoiceListByProviderIdQuery.bindValue(":offset", page * count);
        if (!m_providerInvoiceListByProviderIdQuery.exec())
        {
            qDebug() << m_providerInvoiceListByProviderIdQuery.lastError();
            QLOG_ERROR() << m_providerInvoiceListByProviderIdQuery.lastError();
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = ProviderInvoiceListPtr(new ProviderInvoiceList);
            while (m_providerInvoiceListByProviderIdQuery.next()) {
                ProviderInvoicePtr pInvoicePtr(new ProviderInvoice);
                pInvoicePtr->m_id = m_providerInvoiceListByProviderIdQuery.value(0).toString();
                pInvoicePtr->m_regDate = m_providerInvoiceListByProviderIdQuery.value(1).toDate();
                pInvoicePtr->m_total = m_providerInvoiceListByProviderIdQuery.value(2).toFloat();
                pInvoicePtr->m_providerid = m_providerInvoiceListByProviderIdQuery.value(3).toInt();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        m_providerInvoiceListByProviderIdQuery.finish();
        return pInvoiceListResultPtr;
    }
    //
    ProviderInvoiceListStatsResultPtr DAO::getProviderInvoiceListByProviderIdStats(Int32 providerId, const QDate &fromDate, const QDate &toDate)
    {
        ProviderInvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new ProviderInvoiceListStatsResult);
        m_providerInvoiceListByProviderIdStatsQuery.bindValue(":providerid", providerId);
        m_providerInvoiceListByProviderIdStatsQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListByProviderIdStatsQuery.bindValue(":toDate", toDate);
        if (!m_providerInvoiceListByProviderIdStatsQuery.exec())
        {
            qDebug() << m_providerInvoiceListByProviderIdStatsQuery.lastError();
            QLOG_ERROR() << m_providerInvoiceListByProviderIdStatsQuery.lastError();
            pInvoiceListStatsResultPtr->m_error = 1;
        } else {
            pInvoiceListStatsResultPtr->m_stats = ProviderInvoiceListStatsPtr(new ProviderInvoiceListStats);
            m_providerInvoiceListByProviderIdStatsQuery.next();
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = m_providerInvoiceListByProviderIdStatsQuery.value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = m_providerInvoiceListByProviderIdStatsQuery.value(1).toFloat();
        }
        m_providerInvoiceListByProviderIdStatsQuery.finish();
        return pInvoiceListStatsResultPtr;
    }
    //
    DepositListResultPtr DAO::getUncheckedDeposits()
    {
        DepositListResultPtr pDepositListResultPtr(new DepositListResult);
        if (!m_uncheckedDepositListQuery.exec())
        {
            qDebug() << m_uncheckedDepositListQuery.lastError();
            QLOG_ERROR() << m_uncheckedDepositListQuery.lastError();
            pDepositListResultPtr->m_error = 1;
        } else {
            pDepositListResultPtr->m_list = DepositListPtr(new DepositList);
            while (m_uncheckedDepositListQuery.next()) {
                Uint32 column = 0;
                DepositPtr pDepositPtr(new Deposit);
                pDepositPtr->m_memberUsername = m_uncheckedDepositListQuery.value(column++).toInt();
                pDepositPtr->m_id = m_uncheckedDepositListQuery.value(column++).toInt();
                pDepositPtr->m_date = m_uncheckedDepositListQuery.value(column++).toDateTime();
                pDepositPtr->m_total = m_uncheckedDepositListQuery.value(column++).toFloat();
                pDepositPtr->m_descr = m_uncheckedDepositListQuery.value(column++).toString();
                pDepositPtr->m_memberId = m_uncheckedDepositListQuery.value(column++).toInt();
                pDepositListResultPtr->m_list->push_back(pDepositPtr);
            }
        }

        m_uncheckedDepositListQuery.finish();
        return pDepositListResultPtr;
    }
    //
    bool DAO::closeDeposit(Int32 depositId)
    {
        m_closeDepositQuery.bindValue(":depositid", depositId);
        bool ok = m_closeDepositQuery.exec();
        if (!ok) {
            qDebug() << m_closeDepositQuery.lastError();
            QLOG_ERROR() << m_closeDepositQuery.lastError();
        }
        m_closeDepositQuery.finish();
        return ok;
    }
    //
    MemberListResultPtr DAO::getMemberList(bool onlyPostalSend, Uint32 page, Uint32 count)
    {
        QSqlQuery *pQuery = onlyPostalSend?(&m_memberListFilteredQuery):(&m_memberListQuery);

        MemberListResultPtr pMemberListResultPtr(new MemberListResult);
        pQuery->bindValue(":limit", count);
        pQuery->bindValue(":offset", page * count);
        if (!pQuery->exec())
        {
            qDebug() << pQuery->lastError();
            QLOG_ERROR() << pQuery->lastError();
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (pQuery->next()) {
                Uint32 column = 0;
                MemberPtr pMemberPtr(new Member);
                pMemberPtr->m_id = pQuery->value(column++).toInt();
                pMemberPtr->m_username = pQuery->value(column++).toInt();
                pMemberPtr->m_name = pQuery->value(column++).toString();
                pMemberPtr->m_surname = pQuery->value(column++).toString();
                pMemberPtr->m_imagePath = pQuery->value(column++).toString();
                pMemberPtr->m_lastModified = pQuery->value(column++).toDateTime();
                pMemberPtr->m_regDate = pQuery->value(column++).toDateTime();
                pMemberPtr->m_active = pQuery->value(column++).toInt() == 1;
                pMemberPtr->m_isAdmin = pQuery->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = pQuery->value(column++).toDate();
                pMemberPtr->m_address = pQuery->value(column++).toString();
                pMemberPtr->m_zipCode = pQuery->value(column++).toString();
                pMemberPtr->m_town = pQuery->value(column++).toString();
                pMemberPtr->m_state = pQuery->value(column++).toString();
                pMemberPtr->m_phone = pQuery->value(column++).toString();
                pMemberPtr->m_phone2 = pQuery->value(column++).toString();
                pMemberPtr->m_email = pQuery->value(column++).toString();
                pMemberPtr->m_bank_account = pQuery->value(column++).toString();
                pMemberPtr->m_postalSend = pQuery->value(column++).toInt() == 1;
                pMemberPtr->m_notes = pQuery->value(column++).toString();
                pMemberPtr->m_balance =  pQuery->value(column++).toFloat();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }

        pQuery->finish();
        return pMemberListResultPtr;
    }
    //
    MemberListStatsResultPtr DAO::getMemberListStats(bool onlyPostalSend)
    {
        MemberListStatsResultPtr pMemberListStatsResultPtr(new MemberListStatsResult);

        QSqlQuery *pQuery = onlyPostalSend?(&m_memberListFilteredStatsQuery):(&m_memberListStatsQuery);

        if (!pQuery->exec())
        {
            qDebug() << pQuery->lastError();
            QLOG_ERROR() << pQuery->lastError();
            pMemberListStatsResultPtr->m_error = 1;
        } else {
            pMemberListStatsResultPtr->m_stats = MemberListStatsPtr(new MemberListStats);
            pQuery->next();
            pMemberListStatsResultPtr->m_stats->m_totalMembers = pQuery->value(0).toUInt();
        }
        pQuery->finish();
        return pMemberListStatsResultPtr;
    }
    //
    bool DAO::updateMember(const MemberPtr &pMemberPtr)
    {
        // obligatory
        m_updateMemberQuery.bindValue(":memberid", pMemberPtr->m_id);
        m_updateMemberQuery.bindValue(":username", pMemberPtr->m_username);
        m_updateMemberQuery.bindValue(":name", pMemberPtr->m_name);
        m_updateMemberQuery.bindValue(":surname", pMemberPtr->m_surname);
        m_updateMemberQuery.bindValue(":lastmodified", pMemberPtr->m_lastModified);
        m_updateMemberQuery.bindValue(":active", pMemberPtr->m_active?1:0);
        m_updateMemberQuery.bindValue(":isadmin", pMemberPtr->m_isAdmin?1:0);
        m_updateMemberQuery.bindValue(":bank_account", pMemberPtr->m_bank_account);
        m_updateMemberQuery.bindValue(":postal_send", pMemberPtr->m_postalSend?1:0);
        // optional
        if (pMemberPtr->m_imagePath.isEmpty()) {
            m_updateMemberQuery.bindValue(":image", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":image", pMemberPtr->m_imagePath);
        }
        if (pMemberPtr->m_birthdate.isValid()) {
            m_updateMemberQuery.bindValue(":birth", pMemberPtr->m_birthdate);
        } else {
            m_updateMemberQuery.bindValue(":birth", QVariant());
        }
        if (pMemberPtr->m_address.isEmpty()) {
            m_updateMemberQuery.bindValue(":address", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":address", pMemberPtr->m_address);
        }
        if (pMemberPtr->m_zipCode.isEmpty()) {
            m_updateMemberQuery.bindValue(":zip_code", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":zip_code", pMemberPtr->m_zipCode);
        }
        if (pMemberPtr->m_town.isEmpty()) {
            m_updateMemberQuery.bindValue(":town", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":town", pMemberPtr->m_town);
        }
        if (pMemberPtr->m_state.isEmpty()) {
            m_updateMemberQuery.bindValue(":state", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":state", pMemberPtr->m_state);
        }
        if (pMemberPtr->m_phone.isEmpty()) {
            m_updateMemberQuery.bindValue(":tel", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":tel", pMemberPtr->m_phone);
        }
        if (pMemberPtr->m_phone2.isEmpty()) {
            m_updateMemberQuery.bindValue(":tel2", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":tel2", pMemberPtr->m_phone2);
        }
        if (pMemberPtr->m_email.isEmpty()) {
            m_updateMemberQuery.bindValue(":email", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":email", pMemberPtr->m_email);
        }
        if (pMemberPtr->m_notes.isEmpty()) {
            m_updateMemberQuery.bindValue(":notes", QVariant());
        } else {
            m_updateMemberQuery.bindValue(":notes", pMemberPtr->m_notes);
        }
        // execute query
        bool ok = m_updateMemberQuery.exec();
        if (!ok) {
            qDebug() << m_updateMemberQuery.lastError();
            QLOG_ERROR() << m_updateMemberQuery.lastError();
        }
        m_updateMemberQuery.finish();
        return ok;
    }
    //
    Int32 DAO::createMember(const MemberPtr &pMemberPtr)
    {
        // obligatory
        m_createMemberQuery.bindValue(":username", pMemberPtr->m_username);
        m_createMemberQuery.bindValue(":name", pMemberPtr->m_name);
        m_createMemberQuery.bindValue(":surname", pMemberPtr->m_surname);
        m_createMemberQuery.bindValue(":lastmodified", pMemberPtr->m_lastModified);
        m_createMemberQuery.bindValue(":reg_date", pMemberPtr->m_regDate);
        m_createMemberQuery.bindValue(":active", pMemberPtr->m_active?1:0);
        m_createMemberQuery.bindValue(":isadmin", pMemberPtr->m_isAdmin?1:0);
        m_createMemberQuery.bindValue(":bank_account", pMemberPtr->m_bank_account);
        m_createMemberQuery.bindValue(":postal_send", pMemberPtr->m_postalSend?1:0);
        m_createMemberQuery.bindValue(":pwd", pMemberPtr->m_pwd);
        m_createMemberQuery.bindValue(":lastlogin", pMemberPtr->m_lastLogin);
        // optional
        if (pMemberPtr->m_imagePath.isEmpty()) {
            m_createMemberQuery.bindValue(":image", QVariant());
        } else {
            m_createMemberQuery.bindValue(":image", pMemberPtr->m_imagePath);
        }
        if (pMemberPtr->m_birthdate.isValid()) {
            m_createMemberQuery.bindValue(":birth", pMemberPtr->m_birthdate);
        } else {
            m_createMemberQuery.bindValue(":birth", QVariant());
        }
        if (pMemberPtr->m_address.isEmpty()) {
            m_createMemberQuery.bindValue(":address", QVariant());
        } else {
            m_createMemberQuery.bindValue(":address", pMemberPtr->m_address);
        }
        if (pMemberPtr->m_zipCode.isEmpty()) {
            m_createMemberQuery.bindValue(":zip_code", QVariant());
        } else {
            m_createMemberQuery.bindValue(":zip_code", pMemberPtr->m_zipCode);
        }
        if (pMemberPtr->m_town.isEmpty()) {
            m_createMemberQuery.bindValue(":town", QVariant());
        } else {
            m_createMemberQuery.bindValue(":town", pMemberPtr->m_town);
        }
        if (pMemberPtr->m_state.isEmpty()) {
            m_createMemberQuery.bindValue(":state", QVariant());
        } else {
            m_createMemberQuery.bindValue(":state", pMemberPtr->m_state);
        }
        if (pMemberPtr->m_phone.isEmpty()) {
            m_createMemberQuery.bindValue(":tel", QVariant());
        } else {
            m_createMemberQuery.bindValue(":tel", pMemberPtr->m_phone);
        }
        if (pMemberPtr->m_phone2.isEmpty()) {
            m_createMemberQuery.bindValue(":tel2", QVariant());
        } else {
            m_createMemberQuery.bindValue(":tel2", pMemberPtr->m_phone2);
        }
        if (pMemberPtr->m_email.isEmpty()) {
            m_createMemberQuery.bindValue(":email", QVariant());
        } else {
            m_createMemberQuery.bindValue(":email", pMemberPtr->m_email);
        }
        if (pMemberPtr->m_notes.isEmpty()) {
            m_createMemberQuery.bindValue(":notes", QVariant());
        } else {
            m_createMemberQuery.bindValue(":notes", pMemberPtr->m_notes);
        }

        // execute query
        if (!m_createMemberQuery.exec())
        {
            qDebug() << m_createMemberQuery.lastError();
            QLOG_ERROR() << m_createMemberQuery.lastError();
        }
        m_createMemberQuery.finish();

        Int32 memberId = 0;
        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        if (!m_getLastIdQuery.exec())
        {
            qDebug() << m_getLastIdQuery.lastError();
            QLOG_ERROR() << m_getLastIdQuery.lastError();
        } else {
            m_getLastIdQuery.next();
            memberId = m_getLastIdQuery.value(0).toUInt();
        }
        m_getLastIdQuery.finish();
        return memberId;
    }
    //
    bool DAO::changeMemberPassword(Int32 memberId, const QString &pwdHash, const QDateTime &lastmodified)
    {
        m_updateMemberPasswordQuery.bindValue(":pwd", pwdHash);
        m_updateMemberPasswordQuery.bindValue(":lastmodified", lastmodified);
        m_updateMemberPasswordQuery.bindValue(":memberid", memberId);
        // execute query
        bool ok = m_updateMemberPasswordQuery.exec();
        if (!ok) {
            qDebug() << m_updateMemberPasswordQuery.lastError();
            QLOG_ERROR() << m_updateMemberPasswordQuery.lastError();
        }
        m_updateMemberPasswordQuery.finish();
        return ok;
    }
    //
    bool DAO::changeMemberLastLogin(Int32 memberId, const QDateTime &lastlogin)
    {
        m_updateMemberLastLoginQuery.bindValue(":lastlogin", lastlogin);
        m_updateMemberLastLoginQuery.bindValue(":memberid", memberId);
        // execute query
        bool ok = m_updateMemberLastLoginQuery.exec();
        if (!ok) {
            qDebug() << m_updateMemberLastLoginQuery.lastError();
            QLOG_ERROR() << m_updateMemberLastLoginQuery.lastError();
        }
        m_updateMemberLastLoginQuery.finish();
        return ok;
    }
    //
    InvoiceResultPtr DAO::getLastInvoiceInfo()
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);
        if (!m_lastInvoiceQuery.exec())
        {
            qDebug() << m_lastInvoiceQuery.lastError();
            QLOG_ERROR() << m_lastInvoiceQuery.lastError();
            pInvoiceResultPtr->m_error = 1;
        } else if (m_lastInvoiceQuery.next())
        {
            InvoicePtr pInvoicePtr(new Invoice());
            pInvoicePtr->m_id = m_lastInvoiceQuery.value(0).toInt();;
            pInvoicePtr->m_state = static_cast<InvoiceState>(m_lastInvoiceQuery.value(1).toUInt());
            pInvoicePtr->m_date = m_lastInvoiceQuery.value(2).toDateTime();
            pInvoicePtr->m_total = m_lastInvoiceQuery.value(3).toFloat();
            pInvoicePtr->m_memberId = m_lastInvoiceQuery.value(4).toInt();
            pInvoicePtr->m_lastModified = m_lastInvoiceQuery.value(5).toDateTime();
            pInvoiceResultPtr->m_pInvoice = pInvoicePtr;
        }
        m_lastInvoiceQuery.finish();

        return pInvoiceResultPtr;
    }
    //
    bool DAO::updateInvoiceLastModDate(Int32 invoiceId, const QDateTime &lastModDate)
    {
        // bind value
        m_updateLastModInvoiceQuery.bindValue(":invoiceid", invoiceId);
        m_updateLastModInvoiceQuery.bindValue(":lastmodified", lastModDate);
        bool ok = m_updateLastModInvoiceQuery.exec();
        if (!ok) {
            qDebug() << m_updateLastModInvoiceQuery.lastError();
            QLOG_ERROR() << m_updateLastModInvoiceQuery.lastError();
        }
        m_updateLastModInvoiceQuery.finish();
        return ok;
    }
    //
    bool DAO::deleteInvoice(Int32 invoiceId)
    {
        // bind value
        m_removeInvoiceQuery.bindValue(":invoiceid", invoiceId);
        bool ok = m_removeInvoiceQuery.exec();
        if (!ok) {
            qDebug() << m_removeInvoiceQuery.lastError();
            QLOG_ERROR() << m_removeInvoiceQuery.lastError();
        }
        m_removeInvoiceQuery.finish();
        return ok;
    }
    //
    InvoiceListResultPtr DAO::getActiveInvoiceList()
    {
        // always return list object
        InvoiceListResultPtr pInvoiceListResultPtr(new InvoiceListResult);

        m_getActiveInvoiceListQuery.bindValue(":state", static_cast<Int32>(InvoiceState::Open));
        // run query
        if (!m_getActiveInvoiceListQuery.exec())
        {
            qDebug() << m_getActiveInvoiceListQuery.lastError();
            QLOG_ERROR() << m_getActiveInvoiceListQuery.lastError();
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = InvoiceListPtr(new InvoiceList);
            while (m_getActiveInvoiceListQuery.next()) {
                InvoicePtr pInvoicePtr = InvoicePtr(new Invoice());
                pInvoicePtr->m_id = m_getActiveInvoiceListQuery.value(0).toInt();
                pInvoicePtr->m_state = static_cast<InvoiceState>(m_getActiveInvoiceListQuery.value(1).toUInt());
                pInvoicePtr->m_date = m_getActiveInvoiceListQuery.value(2).toDateTime();
                pInvoicePtr->m_total = m_getActiveInvoiceListQuery.value(3).toFloat();
                pInvoicePtr->m_memberId = m_getActiveInvoiceListQuery.value(4).toInt();
                pInvoicePtr->m_lastModified = m_getActiveInvoiceListQuery.value(5).toDateTime();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        m_getActiveInvoiceListQuery.finish();
        return pInvoiceListResultPtr;
    }
    //
    bool DAO::checkUsername(Int32 username)
    {
        bool usernameUsed = true;
        m_checkUsernameQuery.bindValue(":username", username);
        if (!m_checkUsernameQuery.exec())
        {
            qDebug() << m_checkUsernameQuery.lastError();
            QLOG_ERROR() << m_checkUsernameQuery.lastError();
        } else {
            m_checkUsernameQuery.next();
            usernameUsed = m_checkUsernameQuery.value(0).toInt() != 0;
        }
        return usernameUsed;
    }
    //
    ProviderInvoiceResultPtr DAO::getProviderInvoiceById(const QString &providerInvoiceId)
    {
        ProviderInvoiceResultPtr pProviderInvoiceResultPtr(new ProviderInvoiceResult);
        m_providerInvoiceByIdQuery.bindValue(":providerinvoicesid", providerInvoiceId);
        if (!m_providerInvoiceByIdQuery.exec())
        {
            qDebug() << m_providerInvoiceByIdQuery.lastError();
            QLOG_ERROR() << m_providerInvoiceByIdQuery.lastError();
            pProviderInvoiceResultPtr->m_error = 1;
        } else if (m_providerInvoiceByIdQuery.next())
        {
            ProviderInvoicePtr pProviderInvoicePtr(new ProviderInvoice);
            Uint32 column = 0;
            pProviderInvoicePtr->m_id = providerInvoiceId;
            pProviderInvoicePtr->m_regDate = m_providerInvoiceByIdQuery.value(column++).toDate();
            pProviderInvoicePtr->m_total = m_providerInvoiceByIdQuery.value(column++).toFloat();
            pProviderInvoicePtr->m_providerName = m_providerInvoiceByIdQuery.value(column++).toString();
            pProviderInvoicePtr->m_providerImagePath = m_providerInvoiceByIdQuery.value(column++).toString();
            pProviderInvoiceResultPtr->m_pProviderInvoice = pProviderInvoicePtr;
        }
        m_providerInvoiceByIdQuery.finish();
        return pProviderInvoiceResultPtr;
    }
    //
    ProviderInvoiceProductItemListResultPtr DAO::getProviderInvoiceProductsByInvoiceId(const QString &providerInvoiceId)
    {
        ProviderInvoiceProductItemListResultPtr pListResultPtr = ProviderInvoiceProductItemListResultPtr(new ProviderInvoiceProductItemListResult);
        // bind value
        m_providerInvoiceProductsByInvoiceIdQuery.bindValue(":providerinvoicesid", providerInvoiceId);
        // run query
        if (!m_providerInvoiceProductsByInvoiceIdQuery.exec())
        {
            qDebug() << m_providerInvoiceProductsByInvoiceIdQuery.lastError();
            QLOG_ERROR() << m_providerInvoiceProductsByInvoiceIdQuery.lastError();
            pListResultPtr->m_error = 1;
        } else {
            pListResultPtr->m_list = ProviderInvoiceProductItemListPtr(new ProviderInvoiceProductItemList);
            while (m_providerInvoiceProductsByInvoiceIdQuery.next()) {
                ProviderInvoiceProductItemPtr pProductPtr(new ProviderInvoiceProductItem);
                Uint32 column = 0;
                pProductPtr->m_productId = m_providerInvoiceProductsByInvoiceIdQuery.value(column++).toInt();
                pProductPtr->m_count = m_providerInvoiceProductsByInvoiceIdQuery.value(column++).toInt();
                pProductPtr->m_productName = m_providerInvoiceProductsByInvoiceIdQuery.value(column++).toString();
                pProductPtr->m_productImagePath = m_providerInvoiceProductsByInvoiceIdQuery.value(column++).toString();
                pProductPtr->m_productPrice = m_providerInvoiceProductsByInvoiceIdQuery.value(column++).toFloat();
                pListResultPtr->m_list->push_back(pProductPtr);
            }
        }
        m_providerInvoiceProductsByInvoiceIdQuery.finish();
        return pListResultPtr;
    }
}

