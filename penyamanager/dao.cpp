#include "DataTypes.h"
#include "dao.h"

namespace PenyaManager {
//
DAO::DAO(const QString& hostname, const QString& databaseName,
                const QString& username, const QString& pass)
    :
        m_db(QSqlDatabase::addDatabase("QMYSQL")),
        m_productFamiliesQuery(m_db)
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
}

//
DAO::~DAO() 
{
    if (m_db.isOpen()) 
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
}
