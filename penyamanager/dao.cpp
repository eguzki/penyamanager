//

#include "DataTypes.h"
#include "dao.h"

namespace PenyaManager {
    //
    DAO::DAO(const QString& hostname, const QString& databaseName,
            const QString& username, const QString& pass)
        :
            m_db(QSqlDatabase::addDatabase("QMYSQL")),
            m_productFamiliesQuery(m_db),
            m_productItemsByFamilyQuery(m_db),
            m_memberById(m_db),
            m_memberActiveInvoice(m_db),
            m_removeProductInvoice(m_db),
            m_updateProductInvoice(m_db),
            m_insertInvoice(m_db),
            m_getLastId("SELECT LAST_INSERT_ID()", m_db),
            m_productInvoiceItemsQuery(m_db)
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
        m_productItemsByFamilyQuery.prepare("SELECT idproduct_item, name, image FROM product_item WHERE active = 1 AND idproduct_family = :familyId");

        // Member by name
        m_memberById.prepare(
                "SELECT member.idmember, member.name, member.surname, member.image, account.balance "
                "FROM account "
                "INNER JOIN member "
                "ON member.idmember=account.idmember "
                "WHERE member.idmember= :memberId "
                "AND member.active= :activeId "
                "ORDER BY account.date DESC LIMIT 1 "
                );

        // Invoice by ID
        m_memberActiveInvoice.prepare(
                "SELECT idinvoice, state, date, total, idmember, payment FROM invoice "
                "WHERE idmember = :memberId AND state = :stateId "
                "ORDER BY date DESC LIMIT 1"
                );

        // remove product invoice by ID
        m_removeProductInvoice.prepare(
                "DELETE FROM inv_prod "
                "WHERE idinvoice = :invoiceid AND idproduct_item = :productid"
                );

        // update product invoice by ID
        m_updateProductInvoice.prepare(
                "INSERT INTO inv_prod "
                "(idinvoice, idproduct_item, count) "
                "VALUES (:invoiceid, :productid, :count) "
                "ON DUPLICATE KEY UPDATE "
                "count=:newcount"
                );

        //insert new invoice by
        m_insertInvoice.prepare(
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
            ProductItemPtr pfPtr(new ProductItem(name, image));
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
        m_memberById.bindValue(":memberId", memberLoginId);
        // only active members
        m_memberById.bindValue(":activeId", 1);
        m_memberById.exec();
        if (!m_memberById.next())
        {
            return MemberPtr();
        }
        MemberPtr memberPtr(new Member());
        memberPtr->m_id = m_memberById.value(0).toUInt();
        memberPtr->m_name = m_memberById.value(1).toString();
        memberPtr->m_surname = m_memberById.value(2).toString();
        memberPtr->m_imagePath = m_memberById.value(3).toString();
        memberPtr->m_balance = m_memberById.value(4).toFloat();

        m_memberById.finish();
        return memberPtr;
    }
    //
    InvoicePtr DAO::getMemberActiveInvoice(Int32 memberId)
    {
        m_memberActiveInvoice.bindValue(":memberId", memberId);
        m_memberActiveInvoice.bindValue(":stateId", static_cast<Int32>(InvoiceState::Open));
        m_memberActiveInvoice.exec();
        if (!m_memberActiveInvoice.next())
        {
            return InvoicePtr();
        }
        InvoicePtr pInvoicePtr(new Invoice());
        pInvoicePtr->m_id = m_memberActiveInvoice.value(0).toUInt();
        pInvoicePtr->m_state = static_cast<InvoiceState>(m_memberActiveInvoice.value(2).toUInt());
        pInvoicePtr->m_date = m_memberActiveInvoice.value(3).toDateTime().toMSecsSinceEpoch();
        pInvoicePtr->m_total = m_memberActiveInvoice.value(4).toFloat();
        pInvoicePtr->m_payment = static_cast<PaymentType>(m_memberActiveInvoice.value(5).toUInt());
        m_memberActiveInvoice.finish();

        return pInvoicePtr;
    }
    //
    void DAO::removeProductInvoice(Int32 invoiceId, Int32 productId)
    {
        m_removeProductInvoice.bindValue(":invoiceid", invoiceId);
        m_removeProductInvoice.bindValue(":productid", productId);
        if (!m_removeProductInvoice.exec())
        {
            qDebug() << m_removeProductInvoice.lastError();
        }
        m_removeProductInvoice.finish();
    }
    //
    void DAO::updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        m_updateProductInvoice.bindValue(":invoiceid", invoiceId);
        m_updateProductInvoice.bindValue(":productid", productId);
        m_updateProductInvoice.bindValue(":count", count);
        m_updateProductInvoice.bindValue(":newcount", count);
        if (!m_updateProductInvoice.exec())
        {
            qDebug() << m_updateProductInvoice.lastError();
        } else {
            qDebug() << "inv_prod update ok";
        }
        m_updateProductInvoice.finish();
    }
    //
    InvoicePtr DAO::createInvoice(Int32 memberId)
    {
        InvoicePtr pInvoicePtr(new Invoice(
                    0,
                    memberId,
                    InvoiceState::Open,
                    QDateTime::currentDateTime().toMSecsSinceEpoch(),
                    0.0,
                    PaymentType::Account
                    ));

        m_insertInvoice.bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
        m_insertInvoice.bindValue(":date", QVariant(QDateTime::fromMSecsSinceEpoch(pInvoicePtr->m_date)));
        m_insertInvoice.bindValue(":total", pInvoicePtr->m_total);
        m_insertInvoice.bindValue(":idmember", pInvoicePtr->m_memberId);
        m_insertInvoice.bindValue(":payment", static_cast<Int32>(pInvoicePtr->m_payment));
        m_insertInvoice.exec();
        m_insertInvoice.finish();

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        m_getLastId.exec();
        m_getLastId.next();
        pInvoicePtr->m_id = m_getLastId.value(0).toUInt();
        qDebug() << "invoice create ok";
        qDebug() << pInvoicePtr->m_id;
        m_getLastId.finish();
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
}
