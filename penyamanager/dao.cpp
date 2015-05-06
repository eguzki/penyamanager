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
            m_updateMemberQuery(m_db),
            m_insertDepositQuery(m_db),
            m_memberAccountListQuery(m_db)
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
                "ON member.idmember=account.idmember "
                "WHERE member.idmember= :memberid "
                "AND member.active= :activeId "
                "ORDER BY account.date DESC LIMIT 1 "
                );

        // Invoice by ID
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

        // update existing member
        m_updateMemberQuery.prepare(
                "UPDATE member "
                "SET name=:name, surname=:surname, image=:image, lastmodified=:lastmodified, reg_date=:reg_date"
               "WHERE idmember=:memberid"
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
    void DAO::updateMember(const MemberPtr &pMemberPtr)
    {
        m_updateMemberQuery.bindValue(":idmember", pMemberPtr->m_id);
        m_updateMemberQuery.bindValue(":name", pMemberPtr->m_name);
        m_updateMemberQuery.bindValue(":surname", pMemberPtr->m_surname);
        m_updateMemberQuery.bindValue(":image", pMemberPtr->m_imagePath);
        m_updateMemberQuery.bindValue(":lastmodified", pMemberPtr->m_lastModified);
        m_updateMemberQuery.bindValue(":reg_date", pMemberPtr->m_regDate);
        if (!m_updateMemberQuery.exec())
        {
            qDebug() << m_updateMemberQuery.lastError();
        }
        m_updateMemberQuery.finish();
    }
    //
    DepositPtr DAO::createDeposit(const DepositPtr &pDepositPtr)
    {
        m_insertDepositQuery.bindValue(":memberid", pDepositPtr->m_memberId);
        m_insertDepositQuery.bindValue(":state", static_cast<Int32>(pDepositPtr->m_state));
        m_insertDepositQuery.bindValue(":date", pDepositPtr->m_date);
        m_insertDepositQuery.bindValue(":total", pDepositPtr->m_total);
        m_insertDepositQuery.bindValue(":description", pDepositPtr->m_descr);
        if (!m_insertDepositQuery.exec())
        {
            qDebug() << m_insertDepositQuery.lastError();
        }
        m_insertDepositQuery.finish();
        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        if (!m_getLastIdQuery.exec())
        {
            qDebug() << m_getLastIdQuery.lastError();
        } else {
            m_getLastIdQuery.next();
            pDepositPtr->m_id = m_getLastIdQuery.value(0).toUInt();
        }
        m_getLastIdQuery.finish();
        return pDepositPtr;
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
}
