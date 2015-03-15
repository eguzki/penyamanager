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
            m_memberByName(m_db),
            m_memberActiveInvoice(m_db)
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
        m_memberByName.prepare(
                "SELECT member.idmember, member.name, member.surname, member.image, account.balance "
                "FROM account "
                "INNER JOIN member "
                "ON member.idmember=account.idmember "
                "WHERE member.name = :memberName "
                "AND member.active = :activeId "
                "ORDER BY account.date DESC LIMIT 1"
                );

        // Invoice by ID
        m_memberActiveInvoice.prepare(
                "SELECT idinvoice, state, date, total, idmember, payment FROM invoice "
                "WHERE idmember = :memberId AND state = :stateId "
                "ORDER BY date DESC LIMIT 1"
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
    MemberPtr DAO::getActiveMemberByName(const QString &memberLoginName)
    {
        // member and balance
        m_memberByName.bindValue(":memberName", memberLoginName);
        // only active members
        m_memberByName.bindValue(":activeId", 1);
        m_memberByName.exec();
        if (!m_memberByName.next())
        {
            return MemberPtr();
        }
        MemberPtr memberPtr(new Member());
        memberPtr->m_id = m_memberByName.value(0).toUInt();
        memberPtr->m_name = m_memberByName.value(1).toString();
        memberPtr->m_surename = m_memberByName.value(2).toString();
        memberPtr->m_imagePath = m_memberByName.value(3).toString();
        memberPtr->m_balance = m_memberByName.value(4).toFloat();

        m_memberByName.finish();
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
}
