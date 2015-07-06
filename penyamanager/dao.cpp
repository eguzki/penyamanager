//

#include "dao.h"

namespace PenyaManager {
    //
    DAO::DAO(const QString& hostname, const QString& databaseName,
            const QString& username, const QString& pass)
        :
            m_db(QSqlDatabase::addDatabase("QMYSQL")),
            m_productFamiliesQuery(m_db),
            m_productItemsByFamilyQuery(m_db),
            m_memberByIdQuery(m_db),
            m_invoiceQuery(m_db),
            m_memberActiveInvoiceQuery(m_db),
            m_removeProductInvoiceQuery(m_db),
            m_updateProductInvoiceQuery(m_db),
            m_insertInvoiceQuery(m_db),
            m_getLastIdQuery("SELECT LAST_INSERT_ID()", m_db),
            m_productInvoiceItemsQuery(m_db),
            m_resetInvoiceProductItemsQuery(m_db),
            m_updateInvoiceQuery(m_db),
            m_memberLastAccountInfoQuery(m_db),
            m_insertTransactionQuery(m_db),
            m_insertDepositQuery(m_db),
            m_memberAccountListQuery(m_db),
            m_tableReservationListQuery(m_db),
            m_lunchTablesListQuery(m_db),
            m_insertTableReservationQuery(m_db),
            m_cancelTableReservationQuery(m_db),
            m_slowPayersQuery(m_db),
            m_invoiceListByMemberIdQuery(m_db),
            m_invoiceListByMemberIdStatsQuery(m_db),
            m_invoiceListQuery(m_db),
            m_invoiceListStatsQuery(m_db),
            m_providerListQuery(m_db),
            m_productItemsByProviderQuery(m_db),
            m_createProviderQuery(m_db),
            m_productItemListQuery(m_db),
            m_productItemsStatsQuery(m_db),
            m_updateStockQuery(m_db),
            m_productItemQuery(m_db),
            m_updateProductItemQuery(m_db),
            m_createProductItemQuery(m_db),
            m_productFamilyItemQuery(m_db),
            m_updateProductFamilyItemQuery(m_db),
            m_createProductFamilyItemQuery(m_db),
            m_productExpensesListByMemberIdQuery(m_db),
            m_productExpensesListByMemberIdStatsQuery(m_db),
            m_productExpensesListQuery(m_db),
            m_productExpensesListStatsQuery(m_db),
            m_createProviderInvoiceQuery(m_db),
            m_createProviderInvoiceProductQuery(m_db),
            m_providerInvoiceListByProviderIdQuery(m_db),
            m_providerInvoiceListByProviderIdStatsQuery(m_db),
            m_providerInvoiceListQuery(m_db),
            m_providerInvoiceListStatsQuery(m_db),
            m_uncheckedDepositListQuery(m_db)
    {
        // configure db connection
        m_db.setHostName(hostname);
        m_db.setDatabaseName(databaseName);
        m_db.setUserName(username);
        m_db.setPassword(pass);

        // open ddbb connection
        m_db.open();

        // ProductFamilies
        // for filterinf only active, fetch all and filter with code
        m_productFamiliesQuery.prepare("SELECT idproduct_family, name, image, active FROM product_family");

        // ProductItems by family
        // for filterinf only active, fetch all and filter with code
        m_productItemsByFamilyQuery.prepare("SELECT idproduct_item, name, image, active, reg_date, price, idprovider FROM product_item WHERE idproduct_family = :familyId");

        // Member by name
        m_memberByIdQuery.prepare(
                "SELECT member.idmember, member.name, member.surname, member.image, account.balance, member.lastmodified, member.reg_date "
                "FROM account "
                "INNER JOIN member "
                "ON account.idmember=member.idmember "
                "WHERE account.idmember= :memberid "
                "AND member.active= :activeId "
                "ORDER BY account.date DESC LIMIT 1 "
                );

        // Member selected by Admin
        m_memberByAdmin.prepare(
                "SELECT member.idmember, member.name, member.surname, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, "
                "member.birth, member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, "
                "member.postal_send, member.notes, account.balance "
                "FROM account "
                "INNER JOIN member "
                "ON member.idmember=account.idmember "
                "WHERE member.idmember= :memberId "
                "ORDER BY account.date DESC LIMIT 1 "
                );
        // Invoice by member ID
        m_invoiceQuery.prepare(
                "SELECT state, date, total, idmember FROM invoice "
                "WHERE idinvoice = :invoiceid "
                );

        // Invoice by member ID
        m_memberActiveInvoiceQuery.prepare(
                "SELECT idinvoice, state, date, total FROM invoice "
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
                "count=:newcount"
                );

        // insert new invoice
        m_insertInvoiceQuery.prepare(
                "INSERT INTO invoice"
                "(idinvoice, state, date, total, idmember) "
                "VALUES (NULL, :state, :date, :total, :idmember)"
                );

        // invoice product items by invoiceId
        m_productInvoiceItemsQuery.prepare(
                "SELECT product_item.idproduct_item, product_item.name, product_item.image, product_item.price, inv_prod.count "
                "FROM inv_prod INNER JOIN product_item ON inv_prod.idproduct_item=product_item.idproduct_item "
                "WHERE idinvoice=:invoiceid"
                );
        // reset all products from invoice
        m_resetInvoiceProductItemsQuery.prepare(
                "DELETE FROM inv_prod "
                "WHERE idinvoice = :invoiceid"
                );

        // update existing invoice
        m_updateInvoiceQuery.prepare(
                "UPDATE invoice "
                "SET state=:state, date=:date, total=:total "
                "WHERE idinvoice=:invoiceid"
                );

        // member's last account transaction
        m_memberLastAccountInfoQuery.prepare(
                "SELECT amount, date, balance, description, type "
                "FROM account "
                "WHERE idmember=:memberid "
                "ORDER BY date DESC "
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
                "SELECT amount, date, description, type "
                "FROM account "
                "WHERE idmember=:memberid "
                "AND date BETWEEN :fromDate AND :toDate "
                "ORDER BY date DESC"
                );
        // table reservation list for a given moment (date and reservationtype)
        m_tableReservationListQuery.prepare(
                "SELECT tablereservation.idtablereservation, tablereservation.idtable, member.name, member.surname, tablereservation.idmember, tablereservation.guestnum "
                "FROM tablereservation "
                "INNER JOIN member ON tablereservation.idmember=member.idmember "
                "WHERE date=:dateid "
                "AND reservationtype=:reservationtypeid"
                );
        // lunch tables list
        m_lunchTablesListQuery.prepare(
                "SELECT idtable, name, guestnum "
                "FROM lunchtables"
                );
        // insert table reservation
        m_insertTableReservationQuery.prepare(
                "INSERT INTO tablereservation "
                "(date, reservationtype, guestnum, idmember, idtable) "
                "VALUES (:date, :reservationtype, :guestnum, :idmember, :idtable)"
                );
        // cancel table reservation
        m_cancelTableReservationQuery.prepare(
                "DELETE FROM tablereservation "
                "WHERE idtablereservation = :idtablereservation"
                );
        // slow payers
        // SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember
        // returns list of distinct idmembers and their last account date
        // First INNER JOIN on the same table (account) gets balance for the row with last (newest) account date
        // Second INNER JOIN on members table get member information
        m_slowPayersQuery.prepare(
                "SELECT ac.idmember, member.name, member.surname, member.image, ac.balance, member.lastmodified, member.reg_date "
                "FROM account ac "
                "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                "INNER JOIN member ON member.idmember=ac.idmember "
                "WHERE ac.balance<0 AND member.active=:activeId"
                );
        // active invoice list by memberId
        m_invoiceListByMemberIdQuery.prepare(
                "SELECT idinvoice, date, total FROM invoice "
                "WHERE idmember = :memberid AND state = :stateid "
                "AND date BETWEEN :fromDate AND :toDate "
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
                "SELECT idinvoice, idmember, date, total FROM invoice "
                "WHERE state = :stateid "
                "AND date BETWEEN :fromDate AND :toDate "
                "ORDER BY date DESC "
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
        // provider invoice list
        m_providerInvoiceListStatsQuery.prepare(
                "SELECT COUNT(*), SUM(total) FROM provider_invoices "
                "WHERE date BETWEEN :fromDate AND :toDate"
                );
        // unchecked deposit list
        m_uncheckedDepositListQuery.prepare(
                "SELECT iddeposit, date, total, description, idmember FROM deposit "
                "WHERE state = 0"
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
    ProductFamilyListPtr DAO::getProductFamilies(bool onlyActive)
    {
        ProductFamilyListPtr pfListPrt(new ProductFamilyList);

        // run query
        if (!m_productFamiliesQuery.exec())
        {
            qDebug() << m_productFamiliesQuery.lastError();
        } else {
            while (m_productFamiliesQuery.next()) {
                ProductFamilyPtr pfPtr(new ProductFamily);
                pfPtr->m_id = m_productFamiliesQuery.value(0).toUInt();
                pfPtr->m_name = m_productFamiliesQuery.value(1).toString();
                pfPtr->m_imagePath = m_productFamiliesQuery.value(2).toString();
                pfPtr->m_active = m_productFamiliesQuery.value(3).toInt() == 1;
                // discard when onlyActive filter is on and family is not active
                if (!onlyActive || pfPtr->m_active) {
                    pfListPrt->push_back(pfPtr);
                }
            }
        }
        m_productFamiliesQuery.finish();
        return pfListPrt;
    }

    //
    ProductItemListPtr DAO::getProductsFromFamily(Int32 familyId, bool onlyActive)
    {
        ProductItemListPtr pfListPrt(new ProductItemList);

        // bind value
        m_productItemsByFamilyQuery.bindValue(":familyId", familyId);
        // run query
        if (!m_productItemsByFamilyQuery.exec())
        {
            qDebug() << m_productItemsByFamilyQuery.lastError();
        } else {
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
                    pfListPrt->push_back(pfPtr);
                }
            }
        }
        m_productFamiliesQuery.finish();
        return pfListPrt;
    }
    //
    MemberPtr DAO::getActiveMemberById(Int32 memberLoginId)
    {
        // member and balance
        m_memberByIdQuery.bindValue(":memberid", memberLoginId);
        // only active members
        m_memberByIdQuery.bindValue(":activeId", 1);
        if (!m_memberByIdQuery.exec())
        {
            qDebug() << m_memberByIdQuery.lastError();
        }
        if (!m_memberByIdQuery.next())
        {
            return MemberPtr();
        }
        MemberPtr memberPtr(new Member());
        memberPtr->m_id = m_memberByIdQuery.value(0).toUInt();
        memberPtr->m_name = m_memberByIdQuery.value(1).toString();
        memberPtr->m_surname = m_memberByIdQuery.value(2).toString();
        memberPtr->m_imagePath = m_memberByIdQuery.value(3).toString();
        memberPtr->m_balance = m_memberByIdQuery.value(4).toFloat();
        memberPtr->m_lastModified = m_memberByIdQuery.value(5).toDateTime();
        memberPtr->m_regDate = m_memberByIdQuery.value(6).toDateTime();
        m_memberByIdQuery.finish();
        return memberPtr;
    }
    //

    MemberByAdminPtr DAO::getActiveMemberByAdmin(Int32 memberLoginId)
    {
        // member and balance
        m_memberByAdmin.bindValue(":memberId", memberLoginId);
        m_memberByAdmin.exec();
        if (!m_memberByAdmin.next())
        {
            return MemberByAdminPtr();
        }
        MemberByAdminPtr memberPtr(new MemberByAdmin);
        memberPtr->m_id = m_memberByAdmin.value(0).toUInt();
        memberPtr->m_name = m_memberByAdmin.value(1).toString();
        memberPtr->m_surname = m_memberByAdmin.value(2).toString();
        memberPtr->m_image = m_memberByAdmin.value(3).toString();
        memberPtr->m_reg_date = m_memberByAdmin.value(5).toDate();
        memberPtr->m_zip_code = m_memberByAdmin.value(11).toUInt();
        memberPtr->m_bank_account = m_memberByAdmin.value(16).toString();
        memberPtr->m_active = m_memberByAdmin.value(6).toUInt() == 1;

        //memberPtr->m_balance = m_memberByAdmin.value(22222).toFloat();

       /* member.idmember, member.name, member.surname, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, "
                        "member.birth, member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, "
                        "member.postal_send, member.notes, account.balance*/

        m_memberByAdmin.finish();
        return memberPtr;
    }
    //

    InvoicePtr DAO::getInvoice(Int32 invoiceId)
    {
        m_invoiceQuery.bindValue(":invoiceid", invoiceId);
        if (!m_invoiceQuery.exec())
        {
            qDebug() << m_invoiceQuery.lastError();
        }
        if (!m_invoiceQuery.next())
        {
            return InvoicePtr();
        }
        InvoicePtr pInvoicePtr(new Invoice());
        pInvoicePtr->m_id = invoiceId;
        pInvoicePtr->m_state = static_cast<InvoiceState>(m_invoiceQuery.value(0).toUInt());
        pInvoicePtr->m_date = m_invoiceQuery.value(1).toDateTime();
        pInvoicePtr->m_total = m_invoiceQuery.value(2).toFloat();
        pInvoicePtr->m_memberId = m_invoiceQuery.value(3).toInt();
        m_invoiceQuery.finish();

        return pInvoicePtr;
    }

    InvoicePtr DAO::getMemberActiveInvoice(Int32 memberId)
    {
        m_memberActiveInvoiceQuery.bindValue(":memberid", memberId);
        m_memberActiveInvoiceQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Open));
        if (!m_memberActiveInvoiceQuery.exec())
        {
            qDebug() << m_memberActiveInvoiceQuery.lastError();
        }
        if (!m_memberActiveInvoiceQuery.next())
        {
            return InvoicePtr();
        }
        InvoicePtr pInvoicePtr(new Invoice());
        pInvoicePtr->m_id = m_memberActiveInvoiceQuery.value(0).toUInt();
        pInvoicePtr->m_state = static_cast<InvoiceState>(m_memberActiveInvoiceQuery.value(1).toUInt());
        pInvoicePtr->m_date = m_memberActiveInvoiceQuery.value(2).toDateTime();
        pInvoicePtr->m_total = m_memberActiveInvoiceQuery.value(3).toFloat();
        m_memberActiveInvoiceQuery.finish();

        return pInvoicePtr;
    }
    //
    void DAO::removeProductInvoice(Int32 invoiceId, Int32 productId)
    {
        m_removeProductInvoiceQuery.bindValue(":invoiceid", invoiceId);
        m_removeProductInvoiceQuery.bindValue(":productid", productId);
        if (!m_removeProductInvoiceQuery.exec())
        {
            qDebug() << m_removeProductInvoiceQuery.lastError();
        }
        m_removeProductInvoiceQuery.finish();
    }
    //
    void DAO::updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        m_updateProductInvoiceQuery.bindValue(":invoiceid", invoiceId);
        m_updateProductInvoiceQuery.bindValue(":productid", productId);
        m_updateProductInvoiceQuery.bindValue(":count", count);
        m_updateProductInvoiceQuery.bindValue(":newcount", count);
        if (!m_updateProductInvoiceQuery.exec())
        {
            qDebug() << m_updateProductInvoiceQuery.lastError();
        }
        m_updateProductInvoiceQuery.finish();
    }
    //
    InvoicePtr DAO::createInvoice(Int32 memberId)
    {
        InvoicePtr pInvoicePtr(new Invoice(
                    0,
                    memberId,
                    InvoiceState::Open,
                    QDateTime::currentDateTime(),
                    0.0
                    ));

        m_insertInvoiceQuery.bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
        m_insertInvoiceQuery.bindValue(":date", pInvoicePtr->m_date);
        m_insertInvoiceQuery.bindValue(":total", pInvoicePtr->m_total);
        m_insertInvoiceQuery.bindValue(":idmember", pInvoicePtr->m_memberId);
        if (!m_insertInvoiceQuery.exec())
        {
            qDebug() << m_insertInvoiceQuery.lastError();
        }
        m_insertInvoiceQuery.finish();

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        if (!m_getLastIdQuery.exec())
        {
            qDebug() << m_getLastIdQuery.lastError();
        }
        m_getLastIdQuery.next();
        pInvoicePtr->m_id = m_getLastIdQuery.value(0).toUInt();
        m_getLastIdQuery.finish();
        return pInvoicePtr;
    }
    //
    InvoiceProductItemListPtr DAO::getInvoiceProductItems(Int32 invoiceId)
    {
        // bind value
        m_productInvoiceItemsQuery.bindValue(":invoiceid", invoiceId);
        // run query
        if (!m_productInvoiceItemsQuery.exec())
        {
            qDebug() << m_productInvoiceItemsQuery.lastError();
        }

        InvoiceProductItemListPtr pIPIListPrt(new InvoiceProductItemList);
        while (m_productInvoiceItemsQuery.next()) {
            InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
            pInvoiceProductItemPtr->m_productId = m_productInvoiceItemsQuery.value(0).toInt();
            pInvoiceProductItemPtr->m_productname = m_productInvoiceItemsQuery.value(1).toString();
            pInvoiceProductItemPtr->m_imagePath = m_productInvoiceItemsQuery.value(2).toString();
            pInvoiceProductItemPtr->m_priceperunit = m_productInvoiceItemsQuery.value(3).toFloat();
            pInvoiceProductItemPtr->m_count = m_productInvoiceItemsQuery.value(4).toUInt();
            pIPIListPrt->push_back(pInvoiceProductItemPtr);
        }
        m_productInvoiceItemsQuery.finish();
        return pIPIListPrt;
    }
    //
    void DAO::resetInvoiceProductItems(Int32 invoiceId)
    {
        m_resetInvoiceProductItemsQuery.bindValue(":invoiceid", invoiceId);
        if (!m_resetInvoiceProductItemsQuery.exec())
        {
            qDebug() << m_resetInvoiceProductItemsQuery.lastError();
        }
        m_resetInvoiceProductItemsQuery.finish();
    }
    //
    void DAO::updateInvoice(const InvoicePtr &pInvoicePtr)
    {
        // bind value
        m_updateInvoiceQuery.bindValue(":invoiceid", pInvoicePtr->m_id);
        m_updateInvoiceQuery.bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
        m_updateInvoiceQuery.bindValue(":date", pInvoicePtr->m_date);
        m_updateInvoiceQuery.bindValue(":total", pInvoicePtr->m_total);
        if (!m_updateInvoiceQuery.exec())
        {
            qDebug() << m_updateInvoiceQuery.lastError();
        }
        m_updateInvoiceQuery.finish();
    }
    //
    TransactionPtr DAO::getLastAccountInfo(Int32 memberId)
    {
        m_memberLastAccountInfoQuery.bindValue(":memberid", memberId);
        if (!m_memberLastAccountInfoQuery.exec())
        {
            qDebug() << m_memberLastAccountInfoQuery.lastError();
        }
        if (!m_memberLastAccountInfoQuery.next())
        {
            return TransactionPtr();
        }
        TransactionPtr pLastAccountInfoPtr(new Transaction);
        pLastAccountInfoPtr->m_memberId = memberId;
        pLastAccountInfoPtr->m_amount = m_memberLastAccountInfoQuery.value(0).toFloat();
        pLastAccountInfoPtr->m_date = m_memberLastAccountInfoQuery.value(1).toDateTime();
        pLastAccountInfoPtr->m_balance = m_memberLastAccountInfoQuery.value(2).toFloat();
        pLastAccountInfoPtr->m_descr = m_memberLastAccountInfoQuery.value(3).toString();
        pLastAccountInfoPtr->m_type = static_cast<TransactionType>(m_memberLastAccountInfoQuery.value(4).toUInt());
        m_memberLastAccountInfoQuery.finish();
        return pLastAccountInfoPtr;
    }
    //
    void DAO::insertTransaction(const TransactionPtr &pTransactionPtr)
    {
        m_insertTransactionQuery.bindValue(":memberid", pTransactionPtr->m_memberId);
        m_insertTransactionQuery.bindValue(":amount", pTransactionPtr->m_amount);
        m_insertTransactionQuery.bindValue(":date", pTransactionPtr->m_date);
        m_insertTransactionQuery.bindValue(":balance", pTransactionPtr->m_balance);
        m_insertTransactionQuery.bindValue(":description", pTransactionPtr->m_descr);
        m_insertTransactionQuery.bindValue(":type", static_cast<Int32>(pTransactionPtr->m_type));
        if (!m_insertTransactionQuery.exec())
        {
            qDebug() << m_insertTransactionQuery.lastError();
        }
        m_insertTransactionQuery.finish();
    }
    //
    DepositPtr DAO::createDeposit(const DepositPtr &pDepositPtr)
    {
        DepositPtr pNewDepositPtr;
        m_insertDepositQuery.bindValue(":memberid", pDepositPtr->m_memberId);
        m_insertDepositQuery.bindValue(":state", static_cast<Int32>(pDepositPtr->m_state));
        m_insertDepositQuery.bindValue(":date", pDepositPtr->m_date);
        m_insertDepositQuery.bindValue(":total", pDepositPtr->m_total);
        m_insertDepositQuery.bindValue(":description", pDepositPtr->m_descr);
        if (!m_insertDepositQuery.exec())
        {
            qDebug() << m_insertDepositQuery.lastError();
            // TODO on error, finish query and exit
        }
        m_insertDepositQuery.finish();
        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        if (!m_getLastIdQuery.exec())
        {
            qDebug() << m_getLastIdQuery.lastError();
        } else {
            m_getLastIdQuery.next();
            pNewDepositPtr = pDepositPtr;
            pNewDepositPtr->m_id = m_getLastIdQuery.value(0).toUInt();
        }
        m_getLastIdQuery.finish();
        return pNewDepositPtr;
    }
    //
    TransactionListPtr DAO::getAccountList(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        // bind value
        m_memberAccountListQuery.bindValue(":memberid", memberId);
        m_memberAccountListQuery.bindValue(":fromDate", fromDate);
        m_memberAccountListQuery.bindValue(":toDate", toDate);
        // run query
        if (!m_memberAccountListQuery.exec())
        {
            qDebug() << m_memberAccountListQuery.lastError();
        }

        TransactionListPtr pTransactionListPtr(new TransactionList);
        while (m_memberAccountListQuery.next()) {
            TransactionPtr pTransactionPtr(new Transaction());
            pTransactionPtr->m_amount = m_memberAccountListQuery.value(0).toFloat();
            pTransactionPtr->m_date = m_memberAccountListQuery.value(1).toDateTime();
            pTransactionPtr->m_descr = m_memberAccountListQuery.value(2).toString();
            pTransactionPtr->m_type = static_cast<TransactionType>(m_memberAccountListQuery.value(3).toUInt());
            pTransactionListPtr->push_back(pTransactionPtr);
        }
        m_memberAccountListQuery.finish();
        return pTransactionListPtr;
    }
    //
    TableReservationListPtr DAO::getTableReservation(ReservationType reservationType, const QDate &now)
    {
        // bind value
        m_tableReservationListQuery.bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
        m_tableReservationListQuery.bindValue(":dateid", now);
        // run query
        if (!m_tableReservationListQuery.exec())
        {
            qDebug() << m_tableReservationListQuery.lastError();
        }

        TableReservationListPtr pTableReservationListPtr(new TableReservationList);
        while (m_tableReservationListQuery.next()) {
            TableReservationPtr pTableReservationPtr(new TableReservation);
            pTableReservationPtr->m_reservationId = m_tableReservationListQuery.value(0).toInt();
            pTableReservationPtr->m_idTable = m_tableReservationListQuery.value(1).toInt();
            pTableReservationPtr->m_memberName = m_tableReservationListQuery.value(2).toString();
            pTableReservationPtr->m_memberSurname = m_tableReservationListQuery.value(3).toString();
            pTableReservationPtr->m_idMember = m_tableReservationListQuery.value(4).toInt();
            pTableReservationPtr->m_guestNum = m_tableReservationListQuery.value(5).toUInt();
            pTableReservationListPtr->push_back(pTableReservationPtr);
        }
        m_tableReservationListQuery.finish();
        return pTableReservationListPtr;
    }
    //
    LunchTableListPtr DAO::getLunchTableList()
    {
        // run query
        if (!m_lunchTablesListQuery.exec())
        {
            qDebug() << m_lunchTablesListQuery.lastError();
        }

        LunchTableListPtr pLunchTableListPtr(new LunchTableList);
        while (m_lunchTablesListQuery.next()) {
            LunchTablePtr pLunchTablePtr(new LunchTable);
            pLunchTablePtr->m_idTable = m_lunchTablesListQuery.value(0).toInt();
            pLunchTablePtr->m_tableName = m_lunchTablesListQuery.value(1).toString();
            pLunchTablePtr->m_guestNum = m_lunchTablesListQuery.value(2).toUInt();
            pLunchTableListPtr->push_back(pLunchTablePtr);
        }
        m_lunchTablesListQuery.finish();
        return pLunchTableListPtr;
    }
    //
    void DAO::makeTableReservation(const QDate &date, ReservationType reservationType, Uint16 guestNum, Int32 memberId, Int32 idTable)
    {
        m_insertTableReservationQuery.bindValue(":date", date);
        m_insertTableReservationQuery.bindValue(":reservationtype", static_cast<Uint16>(reservationType));
        m_insertTableReservationQuery.bindValue(":guestnum", guestNum);
        m_insertTableReservationQuery.bindValue(":idmember", memberId);
        m_insertTableReservationQuery.bindValue(":idtable", idTable);
        if (!m_insertTableReservationQuery.exec())
        {
            qDebug() << m_insertTableReservationQuery.lastError();
        }
        m_insertTableReservationQuery.finish();
    }
    //
    void DAO::cancelTableReservation(Int32 reservationId)
    {
        m_cancelTableReservationQuery.bindValue(":idtablereservation", reservationId);
        if (!m_cancelTableReservationQuery.exec())
        {
            qDebug() << m_cancelTableReservationQuery.lastError();
        }
        m_cancelTableReservationQuery.finish();
    }
    //
    MemberListPtr DAO::getSlowPayersList()
    {
        // only active members
        m_slowPayersQuery.bindValue(":activeId", 1);
        if (!m_slowPayersQuery.exec())
        {
            qDebug() << m_slowPayersQuery.lastError();
        }

        MemberListPtr pMemberListPtr(new MemberPtrList);
        while (m_slowPayersQuery.next()) {
            MemberPtr pMemberPtr(new Member);
            pMemberPtr->m_id =  m_slowPayersQuery.value(0).toInt();
            pMemberPtr->m_name =  m_slowPayersQuery.value(1).toString();
            pMemberPtr->m_surname =  m_slowPayersQuery.value(2).toString();
            pMemberPtr->m_imagePath =  m_slowPayersQuery.value(3).toString();
            pMemberPtr->m_balance =  m_slowPayersQuery.value(4).toFloat();
            pMemberPtr->m_lastModified =  m_slowPayersQuery.value(5).toDateTime();
            pMemberPtr->m_regDate =  m_slowPayersQuery.value(6).toDateTime();
            pMemberListPtr->push_back(pMemberPtr);
        }

        m_slowPayersQuery.finish();
        return pMemberListPtr;
    }
    //
    InvoiceListPtr DAO::getInvoiceListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
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
        }

        InvoiceListPtr pInvoiceListPtr(new InvoiceList);
        while (m_invoiceListByMemberIdQuery.next()) {
            InvoicePtr pInvoicePtr(new Invoice);
            pInvoicePtr->m_id =  m_invoiceListByMemberIdQuery.value(0).toInt();
            pInvoicePtr->m_memberId =  memberId;
            pInvoicePtr->m_state =  InvoiceState::Closed;
            pInvoicePtr->m_date =  m_invoiceListByMemberIdQuery.value(1).toDateTime();
            pInvoicePtr->m_total =  m_invoiceListByMemberIdQuery.value(2).toFloat();
            pInvoiceListPtr->push_back(pInvoicePtr);
        }

        m_invoiceListByMemberIdQuery.finish();
        return pInvoiceListPtr;
    }
    //
    InvoiceListStatsPtr DAO::getInvoiceListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        InvoiceListStatsPtr pInvoiceListStatsPtr(new InvoiceListStats);
        pInvoiceListStatsPtr->m_totalNumInvoices= 0;
        pInvoiceListStatsPtr->m_totalAmount = 0;
        // only active invoices
        m_invoiceListByMemberIdStatsQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListByMemberIdStatsQuery.bindValue(":memberid", memberId);
        m_invoiceListByMemberIdStatsQuery.bindValue(":fromDate", fromDate);
        m_invoiceListByMemberIdStatsQuery.bindValue(":toDate", toDate);
        if (!m_invoiceListByMemberIdStatsQuery.exec())
        {
            qDebug() << m_invoiceListByMemberIdStatsQuery.lastError();
        } else {
            m_invoiceListByMemberIdStatsQuery.next();
            pInvoiceListStatsPtr->m_totalNumInvoices = m_invoiceListByMemberIdStatsQuery.value(0).toUInt();
            pInvoiceListStatsPtr->m_totalAmount = m_invoiceListByMemberIdStatsQuery.value(1).toFloat();
        }
        m_invoiceListByMemberIdStatsQuery.finish();
        return pInvoiceListStatsPtr;
    }
    //
    InvoiceListPtr DAO::getInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        // only active invoices
        m_invoiceListQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListQuery.bindValue(":fromDate", fromDate);
        m_invoiceListQuery.bindValue(":toDate", toDate);
        m_invoiceListQuery.bindValue(":limit", count);
        m_invoiceListQuery.bindValue(":offset", page * count);
        if (!m_invoiceListQuery.exec())
        {
            qDebug() << m_invoiceListQuery.lastError();
        }

        InvoiceListPtr pInvoiceListPtr(new InvoiceList);
        while (m_invoiceListQuery.next()) {
            InvoicePtr pInvoicePtr(new Invoice);
            pInvoicePtr->m_id =  m_invoiceListQuery.value(0).toInt();
            pInvoicePtr->m_memberId =  m_invoiceListQuery.value(1).toInt();
            pInvoicePtr->m_state =  InvoiceState::Closed;
            pInvoicePtr->m_date =  m_invoiceListQuery.value(2).toDateTime();
            pInvoicePtr->m_total =  m_invoiceListQuery.value(3).toFloat();
            pInvoiceListPtr->push_back(pInvoicePtr);
        }
        m_invoiceListQuery.finish();
        return pInvoiceListPtr;
    }
    //
    InvoiceListStatsPtr DAO::getInvoiceListStats(const QDate &fromDate, const QDate &toDate)
    {
        InvoiceListStatsPtr pInvoiceListStatsPtr(new InvoiceListStats);
        pInvoiceListStatsPtr->m_totalNumInvoices= 0;
        pInvoiceListStatsPtr->m_totalAmount = 0;
        // only active invoices
        m_invoiceListStatsQuery.bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
        m_invoiceListStatsQuery.bindValue(":fromDate", fromDate);
        m_invoiceListStatsQuery.bindValue(":toDate", toDate);
        if (!m_invoiceListStatsQuery.exec())
        {
            qDebug() << m_invoiceListStatsQuery.lastError();
        } else {
            m_invoiceListStatsQuery.next();
            pInvoiceListStatsPtr->m_totalNumInvoices = m_invoiceListStatsQuery.value(0).toUInt();
            pInvoiceListStatsPtr->m_totalAmount = m_invoiceListStatsQuery.value(1).toFloat();
        }
        m_invoiceListStatsQuery.finish();
        return pInvoiceListStatsPtr;
    }
    //
    ProviderListPtr DAO::getProviderList()
    {
        // run query
        if (!m_providerListQuery.exec())
        {
            qDebug() << m_providerListQuery.lastError();
        }

        ProviderListPtr pProviderListPtr(new ProviderList);
        while (m_providerListQuery.next()) {
            ProviderPtr pProviderPtr(new Provider);
            pProviderPtr->m_id = m_providerListQuery.value(0).toInt();
            pProviderPtr->m_name = m_providerListQuery.value(1).toString();
            pProviderPtr->m_image = m_providerListQuery.value(2).toString();
            pProviderPtr->m_regDate = m_providerListQuery.value(3).toDateTime();
            pProviderPtr->m_phone = m_providerListQuery.value(4).toString();
            pProviderListPtr->push_back(pProviderPtr);
        }
        m_providerListQuery.finish();
        return pProviderListPtr;
    }
    //
    ProductItemListPtr DAO::getProductsFromProvider(Int32 providerId)
    {
        // bind value
        m_productItemsByProviderQuery.bindValue(":providerId", providerId);
        // run query
        if (!m_productItemsByProviderQuery.exec())
        {
            qDebug() << m_productItemsByProviderQuery.lastError();
        }

        ProductItemListPtr pfListPrt(new ProductItemList);

        while (m_productItemsByProviderQuery.next()) {
            ProductItemPtr pfPtr(new ProductItem);
            pfPtr->m_id = m_productItemsByProviderQuery.value(0).toUInt();
            pfPtr->m_name = m_productItemsByProviderQuery.value(1).toString();
            pfPtr->m_imagePath = m_productItemsByProviderQuery.value(2).toString();
            pfPtr->m_active = true;
            pfPtr->m_regDate = m_productItemsByProviderQuery.value(3).toDateTime();
            pfPtr->m_familyId = m_productItemsByProviderQuery.value(4).toInt();
            pfPtr->m_price = m_productItemsByProviderQuery.value(5).toFloat();
            pfListPrt->push_back(pfPtr);
        }
        m_productFamiliesQuery.finish();
        return pfListPrt;
    }
    //
    void DAO::createProvider(const QString &name, const QString &imageFileName, const QString &phone)
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
        if (!m_createProviderQuery.exec())
        {
            qDebug() << m_createProviderQuery.lastError();
        }
        m_createProviderQuery.finish();
    }
    //
    ProductItemListPtr DAO::getProductsList(Uint32 page, Uint32 count)
    {
        // only active invoices
        m_productItemListQuery.bindValue(":limit", count);
        m_productItemListQuery.bindValue(":offset", page * count);
        if (!m_productItemListQuery.exec())
        {
            qDebug() << m_productItemListQuery.lastError();
        }

        ProductItemListPtr pProductItemListPtr(new ProductItemList);
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
            pProductItemListPtr->push_back(pProductItemPtr);
        }

        m_productItemListQuery.finish();
        return pProductItemListPtr;
    }
    //
    ProductListStatsPtr DAO::getProductsListStats()
    {
        ProductListStatsPtr pProductListStatsPtr(new ProductListStats);
        pProductListStatsPtr->m_totalNumProducts = 0;
        if (!m_productItemsStatsQuery.exec())
        {
            qDebug() << m_productItemsStatsQuery.lastError();
        } else {
            m_productItemsStatsQuery.next();
            pProductListStatsPtr->m_totalNumProducts = m_productItemsStatsQuery.value(0).toUInt();
        }
        m_productItemsStatsQuery.finish();
        return pProductListStatsPtr;
    }
    //
    void DAO::updateStock(Int32 productItemId, Int32 count)
    {
        m_updateStockQuery.bindValue(":count", count);
        m_updateStockQuery.bindValue(":productid", productItemId);
        if (!m_updateStockQuery.exec())
        {
            qDebug() << m_updateStockQuery.lastError();
        }
        m_updateStockQuery.finish();
    }
    //
    ProductItemPtr DAO::getProductItem(Int32 productItemId)
    {
        ProductItemPtr pProductItemPtr(new ProductItem);
        m_productItemQuery.bindValue(":productid", productItemId);
        if (!m_productItemQuery.exec())
        {
            qDebug() << m_productItemQuery.lastError();
        } else {
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
        }
        m_productItemQuery.finish();
        return pProductItemPtr;
    }
    //
    void DAO::updateProductItem(const ProductItemPtr &pProductPtr)
    {
        m_updateProductItemQuery.bindValue(":name", pProductPtr->m_name);
        m_updateProductItemQuery.bindValue(":image", pProductPtr->m_imagePath);
        m_updateProductItemQuery.bindValue(":active", (pProductPtr->m_active)?(1):(0));
        m_updateProductItemQuery.bindValue(":familyid", pProductPtr->m_familyId);
        m_updateProductItemQuery.bindValue(":price", pProductPtr->m_price);
        m_updateProductItemQuery.bindValue(":providerid", pProductPtr->m_providerId);
        m_updateProductItemQuery.bindValue(":stock", pProductPtr->m_stock);
        m_updateProductItemQuery.bindValue(":productid", pProductPtr->m_id);
        if (!m_updateProductItemQuery.exec())
        {
            qDebug() << m_updateProductItemQuery.lastError();
        }
        m_updateProductItemQuery.finish();
    }
    //
    void DAO::createProductItem(const ProductItemPtr &pProductPtr)
    {
        m_createProductItemQuery.bindValue(":name", pProductPtr->m_name);
        m_createProductItemQuery.bindValue(":image", pProductPtr->m_imagePath);
        m_createProductItemQuery.bindValue(":active", (pProductPtr->m_active)?(1):(0));
        m_createProductItemQuery.bindValue(":reg_date", pProductPtr->m_regDate);
        m_createProductItemQuery.bindValue(":familyid", pProductPtr->m_familyId);
        m_createProductItemQuery.bindValue(":price", pProductPtr->m_price);
        m_createProductItemQuery.bindValue(":providerid", pProductPtr->m_providerId);
        m_createProductItemQuery.bindValue(":stock", pProductPtr->m_stock);
        if (!m_createProductItemQuery.exec())
        {
            qDebug() << m_createProductItemQuery.lastError();
        }
        m_createProductItemQuery.finish();
    }
    //
    ProductFamilyPtr DAO::getProductFamily(Int32 familyId)
    {
        ProductFamilyPtr pProductFamilyPtr(new ProductFamily);
        m_productFamilyItemQuery.bindValue(":familyid", familyId);
        if (!m_productFamilyItemQuery.exec())
        {
            qDebug() << m_productFamilyItemQuery.lastError();
        } else {
            m_productFamilyItemQuery.next();
            pProductFamilyPtr->m_id = familyId;
            pProductFamilyPtr->m_name = m_productFamilyItemQuery.value(0).toString();
            pProductFamilyPtr->m_active =  m_productFamilyItemQuery.value(1).toInt() == 1;
            pProductFamilyPtr->m_imagePath = m_productFamilyItemQuery.value(2).toString();
            pProductFamilyPtr->m_regDate = m_productFamilyItemQuery.value(3).toDateTime();
        }
        m_productFamilyItemQuery.finish();
        return pProductFamilyPtr;
    }
    //
    void DAO::updateProductFamilyItem(const ProductFamilyPtr &pFamilyPtr)
    {
        m_updateProductFamilyItemQuery.bindValue(":name", pFamilyPtr->m_name);
        m_updateProductFamilyItemQuery.bindValue(":image", pFamilyPtr->m_imagePath);
        m_updateProductFamilyItemQuery.bindValue(":active", (pFamilyPtr->m_active)?(1):(0));
        m_updateProductFamilyItemQuery.bindValue(":familyid", pFamilyPtr->m_id);
        if (!m_updateProductFamilyItemQuery.exec())
        {
            qDebug() << m_updateProductFamilyItemQuery.lastError();
        }
        m_updateProductFamilyItemQuery.finish();
    }
    //
    void DAO::createProductFamilyItem(const ProductFamilyPtr &pFamilyPtr)
    {
        m_createProductFamilyItemQuery.bindValue(":name", pFamilyPtr->m_name);
        m_createProductFamilyItemQuery.bindValue(":image", pFamilyPtr->m_imagePath);
        m_createProductFamilyItemQuery.bindValue(":active", (pFamilyPtr->m_active)?(1):(0));
        m_createProductFamilyItemQuery.bindValue(":reg_date", pFamilyPtr->m_regDate);
        if (!m_createProductFamilyItemQuery.exec())
        {
            qDebug() << m_createProductFamilyItemQuery.lastError();
        }
        m_createProductFamilyItemQuery.finish();
    }
    //
    InvoiceProductItemListPtr DAO::getProductExpensesList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        // only active invoices
        m_productExpensesListQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListQuery.bindValue(":toDate", toDate);
        m_productExpensesListQuery.bindValue(":limit", count);
        m_productExpensesListQuery.bindValue(":offset", page * count);
        if (!m_productExpensesListQuery.exec())
        {
            qDebug() << m_productExpensesListQuery.lastError();
        }

        InvoiceProductItemListPtr pInvoiceProductItemListPtr(new InvoiceProductItemList);
        while (m_productExpensesListQuery.next()) {
            InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
            pInvoiceProductItemPtr->m_productId =  m_productExpensesListQuery.value(0).toInt();
            pInvoiceProductItemPtr->m_productname =  m_productExpensesListQuery.value(1).toString();
            pInvoiceProductItemPtr->m_imagePath =  m_productExpensesListQuery.value(2).toString();
            pInvoiceProductItemPtr->m_priceperunit =  m_productExpensesListQuery.value(3).toFloat();
            pInvoiceProductItemPtr->m_count =  m_productExpensesListQuery.value(4).toUInt();
            pInvoiceProductItemListPtr->push_back(pInvoiceProductItemPtr);
        }
        m_productExpensesListQuery.finish();
        return pInvoiceProductItemListPtr;
    }
    //
    InvoiceProductItemStatsPtr DAO::getProductExpensesListStats(const QDate &fromDate, const QDate &toDate)
    {
        m_productExpensesListStatsQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListStatsQuery.bindValue(":toDate", toDate);
        InvoiceProductItemStatsPtr pInvoiceProductItemStatsPtr(new InvoiceProductItemStats);
        pInvoiceProductItemStatsPtr->m_totalProducts = 0;
        if (!m_productExpensesListStatsQuery.exec())
        {
            qDebug() << m_productExpensesListStatsQuery.lastError();
        } else {
            m_productExpensesListStatsQuery.next();
            pInvoiceProductItemStatsPtr->m_totalProducts = m_productExpensesListStatsQuery.value(0).toUInt();
        }
        m_productExpensesListStatsQuery.finish();
        return pInvoiceProductItemStatsPtr;
    }
    //
    InvoiceProductItemListPtr DAO::getProductExpensesListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        m_productExpensesListByMemberIdQuery.bindValue(":memberid", memberId);
        m_productExpensesListByMemberIdQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListByMemberIdQuery.bindValue(":toDate", toDate);
        m_productExpensesListByMemberIdQuery.bindValue(":limit", count);
        m_productExpensesListByMemberIdQuery.bindValue(":offset", page * count);
        if (!m_productExpensesListByMemberIdQuery.exec())
        {
            qDebug() << m_productExpensesListByMemberIdQuery.lastError();
        }

        InvoiceProductItemListPtr pInvoiceProductItemListPtr(new InvoiceProductItemList);
        while (m_productExpensesListByMemberIdQuery.next()) {
            InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
            pInvoiceProductItemPtr->m_productId =  m_productExpensesListByMemberIdQuery.value(0).toInt();
            pInvoiceProductItemPtr->m_productname =  m_productExpensesListByMemberIdQuery.value(1).toString();
            pInvoiceProductItemPtr->m_imagePath =  m_productExpensesListByMemberIdQuery.value(2).toString();
            pInvoiceProductItemPtr->m_priceperunit =  m_productExpensesListByMemberIdQuery.value(3).toFloat();
            pInvoiceProductItemPtr->m_count =  m_productExpensesListByMemberIdQuery.value(4).toUInt();
            pInvoiceProductItemListPtr->push_back(pInvoiceProductItemPtr);
        }
        m_productExpensesListByMemberIdQuery.finish();
        return pInvoiceProductItemListPtr;
    }
    //
    InvoiceProductItemStatsPtr DAO::getProductExpensesListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        m_productExpensesListByMemberIdStatsQuery.bindValue(":memberid", memberId);
        m_productExpensesListByMemberIdStatsQuery.bindValue(":fromDate", fromDate);
        m_productExpensesListByMemberIdStatsQuery.bindValue(":toDate", toDate);
        InvoiceProductItemStatsPtr pInvoiceProductItemStatsPtr(new InvoiceProductItemStats);
        pInvoiceProductItemStatsPtr->m_totalProducts = 0;
        if (!m_productExpensesListByMemberIdStatsQuery.exec())
        {
            qDebug() << m_productExpensesListByMemberIdStatsQuery.lastError();
        } else {
            m_productExpensesListByMemberIdStatsQuery.next();
            pInvoiceProductItemStatsPtr->m_totalProducts = m_productExpensesListByMemberIdStatsQuery.value(0).toUInt();
        }
        m_productExpensesListByMemberIdStatsQuery.finish();
        return pInvoiceProductItemStatsPtr;
    }
    //
    void DAO::createProviderInvoice(const ProviderInvoicePtr &pProviderInvoicePtr)
    {
        m_createProviderInvoiceQuery.bindValue(":id", pProviderInvoicePtr->m_id);
        m_createProviderInvoiceQuery.bindValue(":date", pProviderInvoicePtr->m_regDate);
        m_createProviderInvoiceQuery.bindValue(":total", pProviderInvoicePtr->m_total);
        m_createProviderInvoiceQuery.bindValue(":providerid", pProviderInvoicePtr->m_providerid);
        if (!m_createProviderInvoiceQuery.exec())
        {
            qDebug() << m_createProviderInvoiceQuery.lastError();
        }
        m_createProviderInvoiceQuery.finish();
    }
    //
    void DAO::createProviderInvoiceProduct(const QString &invoiceId, Int32 productId, Uint32 count)
    {
        m_createProviderInvoiceProductQuery.bindValue(":providerinvoiceid", invoiceId);
        m_createProviderInvoiceProductQuery.bindValue(":productid", productId);
        m_createProviderInvoiceProductQuery.bindValue(":count", count);
        if (!m_createProviderInvoiceProductQuery.exec())
        {
            qDebug() << m_createProviderInvoiceProductQuery.lastError();
        }
        m_createProviderInvoiceProductQuery.finish();
    }
    //
    ProviderInvoiceListPtr DAO::getProviderInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        ProviderInvoiceListPtr pInvoiceListPtr(new ProviderInvoiceList);
        m_providerInvoiceListQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListQuery.bindValue(":toDate", toDate);
        m_providerInvoiceListQuery.bindValue(":limit", count);
        m_providerInvoiceListQuery.bindValue(":offset", page * count);
        if (!m_providerInvoiceListQuery.exec())
        {
            qDebug() << m_providerInvoiceListQuery.lastError();
        } else {
            while (m_providerInvoiceListQuery.next()) {
                ProviderInvoicePtr pInvoicePtr(new ProviderInvoice);
                pInvoicePtr->m_id = m_providerInvoiceListQuery.value(0).toString();
                pInvoicePtr->m_regDate = m_providerInvoiceListQuery.value(1).toDate();
                pInvoicePtr->m_total = m_providerInvoiceListQuery.value(2).toFloat();
                pInvoicePtr->m_providerid = m_providerInvoiceListQuery.value(3).toInt();
                pInvoiceListPtr->push_back(pInvoicePtr);
            }
        }

        m_providerInvoiceListQuery.finish();
        return pInvoiceListPtr;
    }
    //
    ProviderInvoiceListStatsPtr DAO::getProviderInvoiceListStats(const QDate &fromDate, const QDate &toDate)
    {
        ProviderInvoiceListStatsPtr pInvoiceListStatsPtr(new ProviderInvoiceListStats);
        pInvoiceListStatsPtr->m_totalNumInvoices= 0;
        pInvoiceListStatsPtr->m_totalAmount = 0;

        m_providerInvoiceListStatsQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListStatsQuery.bindValue(":toDate", toDate);
        if (!m_providerInvoiceListStatsQuery.exec())
        {
            qDebug() << m_providerInvoiceListStatsQuery.lastError();
        } else {
            m_providerInvoiceListStatsQuery.next();
            pInvoiceListStatsPtr->m_totalNumInvoices = m_providerInvoiceListStatsQuery.value(0).toUInt();
            pInvoiceListStatsPtr->m_totalAmount = m_providerInvoiceListStatsQuery.value(1).toFloat();
        }
        m_providerInvoiceListStatsQuery.finish();
        return pInvoiceListStatsPtr;
    }
    //
    ProviderInvoiceListPtr DAO::getProviderInvoiceListByProviderId(Int32 providerId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        ProviderInvoiceListPtr pInvoiceListPtr(new ProviderInvoiceList);
        m_providerInvoiceListByProviderIdQuery.bindValue(":providerid", providerId);
        m_providerInvoiceListByProviderIdQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListByProviderIdQuery.bindValue(":toDate", toDate);
        m_providerInvoiceListByProviderIdQuery.bindValue(":limit", count);
        m_providerInvoiceListByProviderIdQuery.bindValue(":offset", page * count);
        if (!m_providerInvoiceListByProviderIdQuery.exec())
        {
            qDebug() << m_providerInvoiceListByProviderIdQuery.lastError();
        } else {
            while (m_providerInvoiceListByProviderIdQuery.next()) {
                ProviderInvoicePtr pInvoicePtr(new ProviderInvoice);
                pInvoicePtr->m_id = m_providerInvoiceListByProviderIdQuery.value(0).toString();
                pInvoicePtr->m_regDate = m_providerInvoiceListByProviderIdQuery.value(1).toDate();
                pInvoicePtr->m_total = m_providerInvoiceListByProviderIdQuery.value(2).toFloat();
                pInvoicePtr->m_providerid = m_providerInvoiceListByProviderIdQuery.value(3).toInt();
                pInvoiceListPtr->push_back(pInvoicePtr);
            }
        }

        m_providerInvoiceListByProviderIdQuery.finish();
        return pInvoiceListPtr;
    }
    //
    ProviderInvoiceListStatsPtr DAO::getProviderInvoiceListByProviderIdStats(Int32 providerId, const QDate &fromDate, const QDate &toDate)
    {
        ProviderInvoiceListStatsPtr pInvoiceListStatsPtr(new ProviderInvoiceListStats);
        pInvoiceListStatsPtr->m_totalNumInvoices= 0;
        pInvoiceListStatsPtr->m_totalAmount = 0;

        m_providerInvoiceListByProviderIdStatsQuery.bindValue(":providerid", providerId);
        m_providerInvoiceListByProviderIdStatsQuery.bindValue(":fromDate", fromDate);
        m_providerInvoiceListByProviderIdStatsQuery.bindValue(":toDate", toDate);
        if (!m_providerInvoiceListByProviderIdStatsQuery.exec())
        {
            qDebug() << m_providerInvoiceListByProviderIdStatsQuery.lastError();
        } else {
            m_providerInvoiceListByProviderIdStatsQuery.next();
            pInvoiceListStatsPtr->m_totalNumInvoices = m_providerInvoiceListByProviderIdStatsQuery.value(0).toUInt();
            pInvoiceListStatsPtr->m_totalAmount = m_providerInvoiceListByProviderIdStatsQuery.value(1).toFloat();
        }
        m_providerInvoiceListByProviderIdStatsQuery.finish();
        return pInvoiceListStatsPtr;
    }
    //
    DepositListPtr DAO::getUncheckedDeposits()
    {
        DepositListPtr pDepositListPtr(new DepositList);
        if (!m_uncheckedDepositListQuery.exec())
        {
            qDebug() << m_uncheckedDepositListQuery.lastError();
        } else {
            while (m_uncheckedDepositListQuery.next()) {
                DepositPtr pDepositPtr(new Deposit);
                pDepositPtr->m_id = m_uncheckedDepositListQuery.value(0).toInt();
                pDepositPtr->m_date = m_uncheckedDepositListQuery.value(1).toDateTime();
                pDepositPtr->m_total = m_uncheckedDepositListQuery.value(2).toFloat();
                pDepositPtr->m_descr = m_uncheckedDepositListQuery.value(3).toString();
                pDepositPtr->m_memberId = m_uncheckedDepositListQuery.value(4).toInt();
                pDepositListPtr->push_back(pDepositPtr);
            }
        }

        m_uncheckedDepositListQuery.finish();
        return pDepositListPtr;
    }
}

