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
            m_invoiceListStatsQuery(m_db)
    {
        // configure db connection
        m_db.setHostName(hostname);
        m_db.setDatabaseName(databaseName);
        m_db.setUserName(username);
        m_db.setPassword(pass);

        // open ddbb connection
        m_db.open();

        // ProductFamilies
        m_productFamiliesQuery.prepare("SELECT idproduct_family, name, image FROM product_family WHERE active = 1");

        // ProductItems by family
        m_productItemsByFamilyQuery.prepare("SELECT idproduct_item, name, image, reg_date, price FROM product_item WHERE active = 1 AND idproduct_family = :familyId");

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
                "SELECT product_item.idproduct_item, product_item.name, product_item.price, inv_prod.count "
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
    ProductFamilyListPtr DAO::getProductFamilies()
    {
        // run query
        if (!m_productFamiliesQuery.exec())
        {
            qDebug() << m_productFamiliesQuery.lastError();
        }

        ProductFamilyListPtr pfListPrt(new ProductFamilyList);

        while (m_productFamiliesQuery.next()) {
            Uint32 id = m_productFamiliesQuery.value(0).toUInt();
            QString name = m_productFamiliesQuery.value(1).toString();
            QString image = m_productFamiliesQuery.value(2).toString();
            ProductFamilyPtr pfPtr(new ProductFamily(name, image));
            pfPtr->m_id = id;
            pfListPrt->push_back(pfPtr);
        }
        m_productFamiliesQuery.finish();
        return pfListPrt;
    }

    //
    ProductItemListPtr DAO::getProductsFromFamily(Int32 familyId)
    {
        // bind value
        m_productItemsByFamilyQuery.bindValue(":familyId", familyId);
        // run query
        if (!m_productItemsByFamilyQuery.exec())
        {
            qDebug() << m_productItemsByFamilyQuery.lastError();
        }

        ProductItemListPtr pfListPrt(new ProductItemList);

        while (m_productItemsByFamilyQuery.next()) {
            Uint32 id = m_productItemsByFamilyQuery.value(0).toUInt();
            QString name = m_productItemsByFamilyQuery.value(1).toString();
            QString image = m_productItemsByFamilyQuery.value(2).toString();
            QDateTime regDate = m_productItemsByFamilyQuery.value(3).toDateTime();
            Float price = m_productItemsByFamilyQuery.value(4).toFloat();
            ProductItemPtr pfPtr(new ProductItem(name, image, true, regDate, familyId, price));
            pfPtr->m_id = id;
            pfListPrt->push_back(pfPtr);
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
            Int32 productId = m_productInvoiceItemsQuery.value(0).toInt();
            QString productName = m_productInvoiceItemsQuery.value(1).toString();
            Float pricePerUnit = m_productInvoiceItemsQuery.value(2).toFloat();
            Uint32 count = m_productInvoiceItemsQuery.value(3).toUInt();
            InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem(productId, productName, pricePerUnit, count));
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
}
