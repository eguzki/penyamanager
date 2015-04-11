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
            m_resetInvoiceProductItemsQuery(m_db)
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
                "SELECT member.idmember, member.name, member.surname, member.image, account.balance "
                "FROM account "
                "INNER JOIN member "
                "ON member.idmember=account.idmember "
                "WHERE member.idmember= :memberId "
                "AND member.active= :activeId "
                "ORDER BY account.date DESC LIMIT 1 "
                );

        // Invoice by ID
        m_memberActiveInvoiceQuery.prepare(
                "SELECT idinvoice, state, date, total, idmember, payment FROM invoice "
                "WHERE idmember = :memberId AND state = :stateId "
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

        //insert new invoice by
        m_insertInvoiceQuery.prepare(
                "INSERT INTO invoice"
                "(idinvoice, state, date, total, idmember, payment) "
                "VALUES (NULL, :state, :date, :total, :idmember, :payment)"
                );

        // invoice product items by invoiceId
        m_productInvoiceItemsQuery.prepare(
                "SELECT product_item.name, product_item.price, inv_prod.count "
                "FROM inv_prod INNER JOIN product_item ON inv_prod.idproduct_item=product_item.idproduct_item "
                "WHERE idinvoice=:invoiceid"
                );
        // reset all products from invoice
        m_resetInvoiceProductItemsQuery.prepare(
                "DELETE FROM inv_prod "
                "WHERE idinvoice = :invoiceid"
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
        m_productFamiliesQuery.exec();

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
        m_productItemsByFamilyQuery.exec();

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
        m_memberByIdQuery.bindValue(":memberId", memberLoginId);
        // only active members
        m_memberByIdQuery.bindValue(":activeId", 1);
        m_memberByIdQuery.exec();
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

        m_memberByIdQuery.finish();
        return memberPtr;
    }
    //
    InvoicePtr DAO::getMemberActiveInvoice(Int32 memberId)
    {
        m_memberActiveInvoiceQuery.bindValue(":memberId", memberId);
        m_memberActiveInvoiceQuery.bindValue(":stateId", static_cast<Int32>(InvoiceState::Open));
        m_memberActiveInvoiceQuery.exec();
        if (!m_memberActiveInvoiceQuery.next())
        {
            return InvoicePtr();
        }
        InvoicePtr pInvoicePtr(new Invoice());
        pInvoicePtr->m_id = m_memberActiveInvoiceQuery.value(0).toUInt();
        pInvoicePtr->m_state = static_cast<InvoiceState>(m_memberActiveInvoiceQuery.value(2).toUInt());
        pInvoicePtr->m_date = m_memberActiveInvoiceQuery.value(3).toDateTime();
        pInvoicePtr->m_total = m_memberActiveInvoiceQuery.value(4).toFloat();
        pInvoicePtr->m_payment = static_cast<PaymentType>(m_memberActiveInvoiceQuery.value(5).toUInt());
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
                    0.0,
                    PaymentType::Account
                    ));

        m_insertInvoiceQuery.bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
        m_insertInvoiceQuery.bindValue(":date", pInvoicePtr->m_date);
        m_insertInvoiceQuery.bindValue(":total", pInvoicePtr->m_total);
        m_insertInvoiceQuery.bindValue(":idmember", pInvoicePtr->m_memberId);
        m_insertInvoiceQuery.bindValue(":payment", static_cast<Int32>(pInvoicePtr->m_payment));
        m_insertInvoiceQuery.exec();
        m_insertInvoiceQuery.finish();

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        m_getLastIdQuery.exec();
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
        m_productInvoiceItemsQuery.exec();

        InvoiceProductItemListPtr pIPIListPrt(new InvoiceProductItemList);
        while (m_productInvoiceItemsQuery.next()) {
            QString productName = m_productInvoiceItemsQuery.value(0).toString();
            Float pricePerUnit = m_productInvoiceItemsQuery.value(1).toFloat();
            Uint32 count = m_productInvoiceItemsQuery.value(2).toUInt();
            InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem(productName, pricePerUnit, count));
            pIPIListPrt->push_back(pInvoiceProductItemPtr);
        }
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
}
