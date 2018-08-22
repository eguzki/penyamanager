//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
    //
    const QString DAO::kLastQueryId = "SELECT LAST_INSERT_ID()";
    //
    DAO::DAO(const QString& hostname, const QString& databaseName,
            const QString& username, const QString& pass)
        :
            // add QT_DEBUG_PLUGINS=1 to check plugin errors
            m_db(QSqlDatabase::addDatabase("QMYSQL"))
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
    QueryResponse DAO::exec(QueryFactory queryFactory)
    {
        // Function to recover from db server connection timeouts
        // When server reset connection, err is 2006.
        // Then query cannot be reused.
        // https://stackoverflow.com/questions/44120210/recover-from-mysql-server-connection-close-using-qt-qsqlquery
        // query has to be re-initialized
        // factory fuction creates query objects
        QueryResponse queryResponse;
        queryResponse.error = true;
        queryResponse.query = QueryPtr();
        // When database is down, qsqlquery.prepare fails, should not create query when database is down
        // When database is up again, database connection will be re-opened and sql queries can be built
        if (!isOpen()) {
            bool ok = m_db.open();
            if (!ok) {
                // database open error
                Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, m_db.lastError().text());
                return queryResponse;
            }
        }
        queryResponse.query = queryFactory();
        // log query only when debug. Generating query string may be expensive.
        if (Singletons::m_pSettings->value(Constants::kDebugConfig).toString() == "1")
        {
            Singletons::m_pLogger->Debug(Constants::kSystemUserId, PenyaManager::LogAction::kDb, getLastExecutedQuery(queryResponse.query));
        }
        queryResponse.error = !queryResponse.query->exec();
        if (queryResponse.error) {
            int err = queryResponse.query->lastError().number();
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, queryResponse.query->lastError().text());
            // in case error can not be recovered, return null
            queryResponse.query.reset();
            // try to handle server timeout connection closes by inactivity
            // QSqlError(2006, "QMYSQL: Unable to execute query", "MySQL server has gone away")
            if (err == 2006) {
                m_db.close();
                queryResponse.error = !m_db.open();
                if (!queryResponse.error) {
                    // when database connection is opened, query has to be re-initialized
                    queryResponse.query = queryFactory();
                    queryResponse.error = !queryResponse.query->exec();
                    if (queryResponse.error) {
                        qDebug() << queryResponse.query->lastError();
                        Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, queryResponse.query->lastError().text());
                        // in case error can not be recovered, return null
                        queryResponse.query.reset();
                    }
                } else {
                    // database open error
                    Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, m_db.lastError().text());
                }
            }
        }
        return queryResponse;
    }

    //
    ProductFamilyListResultPtr DAO::getProductFamilies(bool onlyActive)
    {
        ProductFamilyListResultPtr pfListPrt(new ProductFamilyListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // ProductFamilies
            // for filtering only active, fetch all and filter with code
            queryPtr->prepare("SELECT idproduct_family, name, name_es, image, active FROM product_family");
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);

        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductFamilies onlyActive %1").arg(onlyActive));
            pfListPrt->m_error = 1;
        } else {
            pfListPrt->m_list = ProductFamilyListPtr(new ProductFamilyList);
            while (queryResponse.query->next()) {
                ProductFamilyPtr pfPtr(new ProductFamily);
                pfPtr->m_id = queryResponse.query->value(0).toUInt();
                pfPtr->m_nameEus = queryResponse.query->value(1).toString();
                pfPtr->m_nameEs = queryResponse.query->value(2).toString();
                pfPtr->m_imagePath = queryResponse.query->value(3).toString();
                pfPtr->m_active = queryResponse.query->value(4).toInt() == 1;
                // discard when onlyActive filter is on and family is not active
                if (!onlyActive || pfPtr->m_active) {
                    pfListPrt->m_list->push_back(pfPtr);
                }
            }
        }
        return pfListPrt;
    }

    //
    ProductItemListResultPtr DAO::getProductsFromFamily(Int32 familyId, bool onlyActive)
    {
        ProductItemListResultPtr pIListResultPtr(new ProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // ProductItems by family
            // for filterinf only active, fetch all and filter with code
            queryPtr->prepare("SELECT idproduct_item, name, name_es, image, active, reg_date, price, idprovider FROM product_item WHERE idproduct_family = :familyId");
            // bind value
            queryPtr->bindValue(":familyId", familyId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductsFromFamily family %1 onlyActive %2").arg(familyId).arg(onlyActive));
            pIListResultPtr->m_error = 1;
        } else {
            pIListResultPtr->m_list = ProductItemListPtr(new ProductItemList);
            while (queryResponse.query->next()) {
                ProductItemPtr pfPtr(new ProductItem);
                pfPtr->m_id = queryResponse.query->value(0).toUInt();
                pfPtr->m_nameEus = queryResponse.query->value(1).toString();
                pfPtr->m_nameEs = queryResponse.query->value(2).toString();
                pfPtr->m_imagePath = queryResponse.query->value(3).toString();
                pfPtr->m_active = queryResponse.query->value(4).toInt() == 1;
                pfPtr->m_regDate = queryResponse.query->value(5).toDateTime();
                pfPtr->m_regDate.setTimeSpec(Qt::UTC);
                pfPtr->m_price = queryResponse.query->value(6).toFloat();
                pfPtr->m_providerId = queryResponse.query->value(7).toInt();
                // discard when onlyActive filter is on and product is not active
                if (!onlyActive || pfPtr->m_active) {
                    pIListResultPtr->m_list->push_back(pfPtr);
                }
            }
        }
        return pIListResultPtr;
    }
    //
    MemberResultPtr DAO::fetchMemberById(Int32 memberId)
    {
        MemberResultPtr pMemberResultPtr(new MemberResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member by id
            queryPtr->prepare(
                    "SELECT member.name, member.username, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                    "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                    "member.notes, member.pwd, member.lastlogin, member.id_card, member.card, member.type "
                    "FROM member "
                    "WHERE member.idmember=:memberid"
                    );
            // member and balance
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);

        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("fetchMemberById memberId %1").arg(memberId));
            pMemberResultPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            MemberPtr pMemberPtr(new Member);
            Uint32 column = 0;
            pMemberPtr->m_id = memberId;
            pMemberPtr->m_name = queryResponse.query->value(column++).toString();
            pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
            pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
            pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
            pMemberPtr->m_active = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
            pMemberPtr->m_address = queryResponse.query->value(column++).toString();
            pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
            pMemberPtr->m_town = queryResponse.query->value(column++).toString();
            pMemberPtr->m_state = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_email = queryResponse.query->value(column++).toString();
            pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
            pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
            pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
            pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
            pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
            pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
            pMemberResultPtr->m_member = pMemberPtr;
        }
        return pMemberResultPtr;
    }
    //
    MemberResultPtr DAO::fetchMemberByUsername(Int32 username)
    {
        MemberResultPtr pMemberResultPtr(new MemberResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member by username
            queryPtr->prepare(
                    "SELECT member.idmember, member.name, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                    "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                    "member.notes, member.pwd, member.lastlogin, member.id_card, member.card, member.type "
                    "FROM member "
                    "WHERE member.username=:username"
                    );
            // member and balance
            queryPtr->bindValue(":username", username);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("fetchMemberByUsername member %1").arg(username));
            pMemberResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            MemberPtr pMemberPtr(new Member);
            Uint32 column = 0;
            pMemberPtr->m_id = queryResponse.query->value(column++).toInt();
            pMemberPtr->m_name = queryResponse.query->value(column++).toString();
            pMemberPtr->m_username = username;
            pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
            pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
            pMemberPtr->m_active = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
            pMemberPtr->m_address = queryResponse.query->value(column++).toString();
            pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
            pMemberPtr->m_town = queryResponse.query->value(column++).toString();
            pMemberPtr->m_state = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_email = queryResponse.query->value(column++).toString();
            pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
            pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
            pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
            pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
            pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
            pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
            pMemberResultPtr->m_member = pMemberPtr;
        }
        return pMemberResultPtr;
    }
    //
    FloatBoolPairResultPtr DAO::getAccountBalance(Int32 memberId)
    {
        FloatBoolPairResultPtr pResult(new FloatBoolPairResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member account balance
            queryPtr->prepare(
                    "SELECT balance FROM account "
                    "WHERE idmember=:memberid "
                    "ORDER BY date DESC LIMIT 1"
                    );
            // member and balance
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountBalance member %1").arg(memberId));
            pResult->m_error = 1;
        } else if (queryResponse.query->next())
        {
            pResult->m_pair.b = true;
            pResult->m_pair.f = queryResponse.query->value(0).toFloat();
        }
        return pResult;
    }
    //
    InvoiceResultPtr DAO::getInvoice(Int32 invoiceId)
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Invoice by invoice ID
            queryPtr->prepare(
                    "SELECT invoice.state, invoice.date, invoice.total, invoice.idmember, invoice.last_modif, member.username "
                    "FROM invoice "
                    "JOIN member on member.idmember = invoice.idmember "
                    "WHERE idinvoice = :invoiceid "
                    );
            queryPtr->bindValue(":invoiceid", invoiceId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);

        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoice invoice %1").arg(invoiceId));
            pInvoiceResultPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            InvoicePtr pInvoicePtr(new Invoice());
            pInvoicePtr->m_id = invoiceId;
            pInvoicePtr->m_state = static_cast<InvoiceState>(queryResponse.query->value(0).toUInt());
            pInvoicePtr->m_date = queryResponse.query->value(1).toDateTime();
            pInvoicePtr->m_date.setTimeSpec(Qt::UTC);
            pInvoicePtr->m_total = queryResponse.query->value(2).toFloat();
            pInvoicePtr->m_memberId = queryResponse.query->value(3).toInt();
            pInvoicePtr->m_lastModified = queryResponse.query->value(4).toDateTime();
            pInvoicePtr->m_memberUsername = queryResponse.query->value(5).toInt();
            pInvoicePtr->m_lastModified.setTimeSpec(Qt::UTC);
            pInvoiceResultPtr->m_pInvoice = pInvoicePtr;
        }

        return pInvoiceResultPtr;
    }

    InvoiceResultPtr DAO::getMemberActiveInvoice(Int32 memberId)
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Invoice by member ID
            queryPtr->prepare(
                    "SELECT idinvoice, state, date, total, last_modif FROM invoice "
                    "WHERE idmember = :memberid AND state = :stateid "
                    "ORDER BY date DESC LIMIT 1"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":stateid", static_cast<Int32>(InvoiceState::Open));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getMemberActiveInvoice member %1").arg(memberId));
            pInvoiceResultPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            InvoicePtr pInvoicePtr(new Invoice());
            pInvoicePtr->m_memberId = memberId;
            pInvoicePtr->m_id = queryResponse.query->value(0).toUInt();
            pInvoicePtr->m_state = static_cast<InvoiceState>(queryResponse.query->value(1).toUInt());
            pInvoicePtr->m_date = queryResponse.query->value(2).toDateTime();
            pInvoicePtr->m_date.setTimeSpec(Qt::UTC);
            pInvoicePtr->m_total = queryResponse.query->value(3).toFloat();
            pInvoicePtr->m_lastModified = queryResponse.query->value(4).toDateTime();
            pInvoicePtr->m_lastModified.setTimeSpec(Qt::UTC);
            pInvoiceResultPtr->m_pInvoice = pInvoicePtr;
        }
        return pInvoiceResultPtr;
    }
    //
    bool DAO::removeProductInvoice(Int32 invoiceId, Int32 productId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // remove product invoice by ID
            queryPtr->prepare(
                    "DELETE FROM inv_prod "
                    "WHERE idinvoice = :invoiceid AND idproduct_item = :productid"
                    );
            queryPtr->bindValue(":invoiceid", invoiceId);
            queryPtr->bindValue(":productid", productId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("removeProductInvoice invoice %1 product %2").arg(invoiceId).arg(productId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::updateProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count, Float price)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update product invoice by ID
            queryPtr->prepare(
                    "INSERT INTO inv_prod "
                    "(idinvoice, idproduct_item, count, price) "
                    "VALUES (:invoiceid, :productid, :count, :price) "
                    "ON DUPLICATE KEY UPDATE "
                    "count = :count, price = :price"
                    );
            queryPtr->bindValue(":invoiceid", invoiceId);
            queryPtr->bindValue(":productid", productId);
            queryPtr->bindValue(":count", count);
            queryPtr->bindValue(":price", price);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateProductInvoice invoice %1 product %2 count %3 price %4").arg(invoiceId).arg(productId).arg(count).arg(price));
        }
        return !queryResponse.error;
    }
    //
    // Returns number of rows affected
    // -1 for error
    Int32 DAO::increaseProductInvoice(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        Int32 numRowsAffected = -1;

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update product invoice by ID
            queryPtr->prepare(
                    "UPDATE inv_prod SET count = count + :count "
                    "WHERE idinvoice = :invoiceid and idproduct_item = :productid"
                    );
            queryPtr->bindValue(":invoiceid", invoiceId);
            queryPtr->bindValue(":productid", productId);
            queryPtr->bindValue(":count", count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("increaseProductInvoice invoice %1 product %2 count %3").arg(invoiceId).arg(productId).arg(count));
        } else {
            numRowsAffected = queryResponse.query->numRowsAffected();
        }
        return numRowsAffected;
    }
    //
    InvoiceResultPtr DAO::createInvoice(Int32 memberId)
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);
        auto now = QDateTime::currentDateTimeUtc();
        InvoicePtr pInvoicePtr(new Invoice);
        pInvoicePtr->m_id = 0;
        pInvoicePtr->m_memberId = memberId;
        pInvoicePtr->m_state = InvoiceState::Open;
        pInvoicePtr->m_date = now;
        pInvoicePtr->m_total = 0.0;
        pInvoicePtr->m_lastModified = now;
        pInvoiceResultPtr->m_pInvoice = pInvoicePtr;

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert new invoice
            queryPtr->prepare(
                    "INSERT INTO invoice"
                    "(idinvoice, state, date, total, idmember, last_modif) "
                    "VALUES (NULL, :state, :date, :total, :idmember, :lastmodified)"
                    );
            queryPtr->bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
            queryPtr->bindValue(":date", pInvoicePtr->m_date);
            queryPtr->bindValue(":total", pInvoicePtr->m_total);
            queryPtr->bindValue(":idmember", pInvoicePtr->m_memberId);
            queryPtr->bindValue(":lastmodified", pInvoicePtr->m_lastModified);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createInvoice member %1").arg(memberId));
            pInvoiceResultPtr->m_error = 1;
            return pInvoiceResultPtr;
        }

        auto lastQuery = [](){
            return QueryPtr(new QSqlQuery(kLastQueryId));
        };

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        QueryResponse lastQueryResponse = exec(lastQuery);
        if (lastQueryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createInvoice could not get last ID created in db"));
            pInvoiceResultPtr->m_error = 1;
        } else if (lastQueryResponse.query->next()) {
            pInvoiceResultPtr->m_pInvoice->m_id = lastQueryResponse.query->value(0).toUInt();
        }
        return pInvoiceResultPtr;
    }
    //
    InvoiceProductItemStatsResultPtr DAO::getInvoiceProductItemsStats(Int32 invoiceId)
    {
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr(new InvoiceProductItemStatsResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // invoice product items by invoiceId
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM inv_prod "
                    "INNER JOIN product_item on inv_prod.idproduct_item=product_item.idproduct_item "
                    "WHERE idinvoice=:invoiceid"
                    );
            queryPtr->bindValue(":invoiceid", invoiceId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoiceProductItemsStats invoiceId %1").arg(invoiceId));
            invoiceProductItemStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            invoiceProductItemStatsResultPtr->m_stats = InvoiceProductItemStatsPtr(new InvoiceProductItemStats);
            invoiceProductItemStatsResultPtr->m_stats->m_totalProducts = queryResponse.query->value(0).toUInt();
        } else {
            invoiceProductItemStatsResultPtr->m_stats = InvoiceProductItemStatsPtr(new InvoiceProductItemStats);
        }
        return invoiceProductItemStatsResultPtr;
    }
    //
    InvoiceProductItemListResultPtr DAO::getInvoiceProductItems(Int32 invoiceId, Uint32 page, Uint32 count)
    {
        InvoiceProductItemListResultPtr pInvoicePILResult(new InvoiceProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // invoice product items by invoiceId
            queryPtr->prepare(
                    "SELECT product_item.idproduct_item, product_item.name, product_item.name_es, product_item.image, product_item.price, inv_prod.count, inv_prod.price "
                    "FROM inv_prod INNER JOIN product_item ON inv_prod.idproduct_item=product_item.idproduct_item "
                    "WHERE idinvoice=:invoiceid "
                    "ORDER BY inv_prod.date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // bind value
            queryPtr->bindValue(":invoiceid", invoiceId);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoiceProductItems invoiceId %1").arg(invoiceId));
            pInvoicePILResult->m_error = 1;
        } else {
            pInvoicePILResult->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (queryResponse.query->next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId = queryResponse.query->value(0).toInt();
                pInvoiceProductItemPtr->m_productnameEus = queryResponse.query->value(1).toString();
                pInvoiceProductItemPtr->m_productnameEs = queryResponse.query->value(2).toString();
                pInvoiceProductItemPtr->m_imagePath = queryResponse.query->value(3).toString();
                pInvoiceProductItemPtr->m_currentPricePerUnit = queryResponse.query->value(4).toFloat();
                pInvoiceProductItemPtr->m_count = queryResponse.query->value(5).toUInt();
                pInvoiceProductItemPtr->m_pricePerUnit = queryResponse.query->value(6).toFloat();
                pInvoicePILResult->m_list->push_back(pInvoiceProductItemPtr);
            }
        }

        return pInvoicePILResult;
    }
    //
    InvoiceProductItemListResultPtr DAO::getAllInvoiceProductItems(Int32 invoiceId)
    {
        InvoiceProductItemListResultPtr pInvoicePILResult(new InvoiceProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // invoice product items by invoiceId
            queryPtr->prepare(
                    "SELECT product_item.idproduct_item, product_item.name, product_item.name_es, product_item.image, product_item.price, inv_prod.count, inv_prod.price "
                    "FROM inv_prod INNER JOIN product_item ON inv_prod.idproduct_item=product_item.idproduct_item "
                    "WHERE idinvoice=:invoiceid"
                    );
            // bind value
            queryPtr->bindValue(":invoiceid", invoiceId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAllInvoiceProductItems invoiceId %1").arg(invoiceId));
            pInvoicePILResult->m_error = 1;
        } else {
            pInvoicePILResult->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (queryResponse.query->next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId = queryResponse.query->value(0).toInt();
                pInvoiceProductItemPtr->m_productnameEus = queryResponse.query->value(1).toString();
                pInvoiceProductItemPtr->m_productnameEs = queryResponse.query->value(2).toString();
                pInvoiceProductItemPtr->m_imagePath = queryResponse.query->value(3).toString();
                pInvoiceProductItemPtr->m_currentPricePerUnit = queryResponse.query->value(4).toFloat();
                pInvoiceProductItemPtr->m_count = queryResponse.query->value(5).toUInt();
                pInvoiceProductItemPtr->m_pricePerUnit = queryResponse.query->value(6).toFloat();
                pInvoicePILResult->m_list->push_back(pInvoiceProductItemPtr);
            }
        }

        return pInvoicePILResult;
    }
    //
    //
    bool DAO::updateInvoice(const InvoicePtr &pInvoicePtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update existing invoice
            queryPtr->prepare(
                    "UPDATE invoice "
                    "SET state=:state, date=:date, total=:total, last_modif=:lastmodified "
                    "WHERE idinvoice=:invoiceid"
                    );
            // bind value
            queryPtr->bindValue(":invoiceid", pInvoicePtr->m_id);
            queryPtr->bindValue(":state", static_cast<Int32>(pInvoicePtr->m_state));
            queryPtr->bindValue(":date", pInvoicePtr->m_date);
            queryPtr->bindValue(":total", pInvoicePtr->m_total);
            queryPtr->bindValue(":lastmodified", pInvoicePtr->m_lastModified);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateInvoice invoiceId %1").arg(pInvoicePtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    TransactionResultPtr DAO::getLastAccountInfo(Int32 memberId)
    {
        TransactionResultPtr pLastAccountInfoResultPtr(new TransactionResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // member's last account transaction
            queryPtr->prepare(
                    "SELECT member.username, account.amount, account.date, account.balance, account.description, account.type "
                    "FROM account "
                    "INNER JOIN member ON member.idmember = account.idmember "
                    "WHERE account.idmember=:memberid "
                    "ORDER BY account.date DESC "
                    "LIMIT 1"
                    );
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getLastAccountInfo memberId %1").arg(memberId));
            pLastAccountInfoResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            Uint32 column = 0;
            TransactionPtr pLastAccountInfoPtr(new Transaction);
            pLastAccountInfoPtr->m_memberId = memberId;
            pLastAccountInfoPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
            pLastAccountInfoPtr->m_amount = queryResponse.query->value(column++).toFloat();
            pLastAccountInfoPtr->m_date = queryResponse.query->value(column++).toDateTime();
            pLastAccountInfoPtr->m_date.setTimeSpec(Qt::UTC);
            pLastAccountInfoPtr->m_balance = queryResponse.query->value(column++).toFloat();
            pLastAccountInfoPtr->m_descr = queryResponse.query->value(column++).toString();
            pLastAccountInfoPtr->m_type = static_cast<TransactionType>(queryResponse.query->value(column++).toUInt());
            pLastAccountInfoResultPtr->m_transaction = pLastAccountInfoPtr;
        }
        return pLastAccountInfoResultPtr;
    }
    //
    bool DAO::insertTransaction(const TransactionPtr &pTransactionPtr)
    {
        auto createQuery = [pTransactionPtr](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert transaction
            queryPtr->prepare(
                    "INSERT INTO account "
                    "(idmember, amount, date, balance, description, type) "
                    "VALUES (:memberid, :amount, :date, :balance, :description, :type)"
                    );
            queryPtr->bindValue(":memberid", pTransactionPtr->m_memberId);
            queryPtr->bindValue(":amount", pTransactionPtr->m_amount);
            queryPtr->bindValue(":date", pTransactionPtr->m_date);
            queryPtr->bindValue(":balance", pTransactionPtr->m_balance);
            queryPtr->bindValue(":description", pTransactionPtr->m_descr);
            queryPtr->bindValue(":type", static_cast<Int32>(pTransactionPtr->m_type));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("insertTransaction memberId %1").arg(pTransactionPtr->m_memberId));
        }
        return !queryResponse.error;
    }
    //
    DepositResultPtr DAO::createDeposit(const DepositPtr &pDepositPtr)
    {
        DepositResultPtr pNewDepositResultPtr(new DepositResult);

        auto createQuery = [pDepositPtr](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert new deposit
            queryPtr->prepare(
                    "INSERT INTO deposit "
                    "(idmember, state, date, total) "
                    "VALUES (:memberid, :state, :date, :total)"
                    );
            queryPtr->bindValue(":memberid", pDepositPtr->m_memberId);
            queryPtr->bindValue(":state", static_cast<Int32>(pDepositPtr->m_state));
            queryPtr->bindValue(":date", pDepositPtr->m_date);
            queryPtr->bindValue(":total", pDepositPtr->m_total);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createDeposit memberId %1").arg(pDepositPtr->m_memberId));
            pNewDepositResultPtr->m_error = 1;
            return pNewDepositResultPtr;
        }

        auto lastQuery = [](){
            return QueryPtr(new QSqlQuery(kLastQueryId));
        };

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        QueryResponse lastQueryResponse = exec(lastQuery);
        if (lastQueryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createDeposit could not get last ID created in db"));
            pNewDepositResultPtr->m_error = 1;
        } else if (lastQueryResponse.query->next()) {
            pNewDepositResultPtr->m_deposit = pDepositPtr;
            pNewDepositResultPtr->m_deposit->m_id = lastQueryResponse.query->value(0).toUInt();
        }
        return pNewDepositResultPtr;
    }
    //
    TransactionListResultPtr DAO::getAccountList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        TransactionListResultPtr pTransactionListResultPtr(new TransactionListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // member's account transaction list
            queryPtr->prepare(
                    "SELECT account.idmember, member.username, account.amount, account.date, account.description, account.balance, account.type "
                    "FROM account "
                    "INNER JOIN member ON member.idmember = account.idmember "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "ORDER BY date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // bind value
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountList fromDate %1 toDate %2 page %3 count %4").arg(fromDateLocalized).arg(toDateLocalized).arg(page).arg(count));
            pTransactionListResultPtr->m_error = 1;
        } else {
            pTransactionListResultPtr->m_list = TransactionListPtr(new TransactionList);
            while (queryResponse.query->next()) {
                Uint32 value = 0;
                TransactionPtr pTransactionPtr(new Transaction());
                pTransactionPtr->m_memberId = queryResponse.query->value(value++).toInt();
                pTransactionPtr->m_memberUsername = queryResponse.query->value(value++).toInt();
                pTransactionPtr->m_amount = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_date = queryResponse.query->value(value++).toDateTime();
                pTransactionPtr->m_date.setTimeSpec(Qt::UTC);
                pTransactionPtr->m_descr = queryResponse.query->value(value++).toString();
                pTransactionPtr->m_balance = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_type = static_cast<TransactionType>(queryResponse.query->value(value++).toUInt());
                pTransactionListResultPtr->m_list->push_back(pTransactionPtr);
            }
        }

        return pTransactionListResultPtr;
    }
    //
    Int32 DAO::getAccountListCount(const QDate &fromDate, const QDate &toDate)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // num transactions from account
            queryPtr->prepare(
                    "SELECT COUNT(*) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        Int32 count = 0.0;
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListCount fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            count = -1;
        } else if (queryResponse.query->next()) {
            count = queryResponse.query->value(0).toUInt();
        }
        return count;
    }
    //
    FloatResult DAO::getAccountListInvoicesSum(const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of invoices from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "AND type=1"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListInvoicesSum fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListDepositsSum(const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of deposits from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "AND type IN (2, 4)"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListDepositsSum fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListBankChargesSum(const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of bank charges from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "AND type=3"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListBankChargesSum fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    Int32 DAO::getAccountListByMemberIdCount(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        Uint32 count = 0.0;
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // num transactions by memberid from account
            queryPtr->prepare(
                    "SELECT COUNT(*) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdCount memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            count = -1;
        } else if (queryResponse.query->next()) {
            count = queryResponse.query->value(0).toUInt();
        }
        return count;
    }
    //
    FloatResult DAO::getAccountListByMemberIdInvoicesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of invoices by memberid from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "AND type=1"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdInvoicesSum memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListByMemberIdDepositsSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of deposits by memberid from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "AND type IN (2, 4)"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdDepositsSum memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListByMemberIdBankChargesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of bank charger by memberid from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "AND type=3"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdBankChargesSum memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    TransactionListResultPtr DAO::getAccountListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        TransactionListResultPtr pTransactionListResultPtr(new TransactionListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // member's account transaction list
            queryPtr->prepare(
                    "SELECT member.username, account.amount, account.date, account.description, account.balance, account.type "
                    "FROM account "
                    "INNER JOIN member ON member.idmember = account.idmember "
                    "WHERE account.idmember=:memberid "
                    "AND account.date BETWEEN :fromDate AND :toDate "
                    "ORDER BY account.date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // bind value
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberId memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            pTransactionListResultPtr->m_error = 1;
        } else {
            pTransactionListResultPtr->m_list = TransactionListPtr(new TransactionList);
            while (queryResponse.query->next()) {
                Uint32 value = 0;
                TransactionPtr pTransactionPtr(new Transaction());
                pTransactionPtr->m_memberId = memberId;
                pTransactionPtr->m_memberUsername = queryResponse.query->value(value++).toInt();
                pTransactionPtr->m_amount = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_date = queryResponse.query->value(value++).toDateTime();
                pTransactionPtr->m_date.setTimeSpec(Qt::UTC);
                pTransactionPtr->m_descr = queryResponse.query->value(value++).toString();
                pTransactionPtr->m_balance = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_type = static_cast<TransactionType>(queryResponse.query->value(value++).toUInt());
                pTransactionListResultPtr->m_list->push_back(pTransactionPtr);
            }
        }
        return pTransactionListResultPtr;
    }
    //
    ReservationListResultPtr DAO::getTableReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // table reservation list for a given moment (date and reservationtype)
            queryPtr->prepare(
                    "SELECT tablereservation.idreservation, tablereservation.idtable, member.username, member.name, member.surname1, member.surname2, tablereservation.idmember, tablereservation.guestnum, tablereservation.isadmin "
                    "FROM tablereservation "
                    "INNER JOIN member ON tablereservation.idmember=member.idmember "
                    "WHERE date=:dateid "
                    "AND reservationtype=:reservationtypeid"
                    );
            // bind value
            queryPtr->bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":dateid", now);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString nowDateLocalized = locale.toString(now, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getTableReservation reservationType %1 now %2").arg(static_cast<Uint16>(reservationType)).arg(nowDateLocalized));
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list =  ReservationListPtr(new ReservationList);
            while (queryResponse.query->next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_idItem = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberName = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname1 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname2 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_idMember = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_guestNum = queryResponse.query->value(column++).toUInt();
                pReservationPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }

        return pReservationListResultPtr;
    }
    //
    ReservationListResultPtr DAO::getOvenReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // oven reservation list for a given moment (date and reservationtype)
            queryPtr->prepare(
                    "SELECT ovenreservation.idreservation, ovenreservation.idoven, member.username, member.name, member.surname1, member.surname2, ovenreservation.idmember, ovenreservation.isadmin "
                    "FROM ovenreservation "
                    "INNER JOIN member ON ovenreservation.idmember=member.idmember "
                    "WHERE date=:dateid "
                    "AND reservationtype=:reservationtypeid"
                    );
            // bind value
            queryPtr->bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":dateid", now);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString nowDateLocalized = locale.toString(now, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getOvenReservation reservationType %1 now %2").arg(static_cast<Uint16>(reservationType)).arg(nowDateLocalized));
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list = ReservationListPtr(new ReservationList);
            while (queryResponse.query->next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_idItem = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberName = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname1 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname2 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_idMember = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_guestNum = 0;
                pReservationPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }

        return pReservationListResultPtr;
    }
    //
    ReservationListResultPtr DAO::getFireplaceReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // oven reservation list for a given moment (date and reservationtype)
            queryPtr->prepare(
                    "SELECT fireplacereservation.idreservation, fireplacereservation.idfireplace, member.username, member.name, member.surname1, member.surname2, fireplacereservation.idmember, fireplacereservation.isadmin "
                    "FROM fireplacereservation "
                    "INNER JOIN member ON fireplacereservation.idmember=member.idmember "
                    "WHERE date=:dateid "
                    "AND reservationtype=:reservationtypeid"
                    );
            // bind value
            queryPtr->bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":dateid", now);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString nowDateLocalized = locale.toString(now, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getFireplaceReservation reservationType %1 now %2").arg(static_cast<Uint16>(reservationType)).arg(nowDateLocalized));
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list = ReservationListPtr(new ReservationList);
            while (queryResponse.query->next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_idItem = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberName = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname1 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname2 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_idMember = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pReservationPtr->m_guestNum = 0;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }
        return pReservationListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getLunchTableList(Uint32 page, Uint32 count)
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // lunch tables list
            queryPtr->prepare(
                    "SELECT idtable, name, guestnum "
                    "FROM lunchtables "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getLunchTableList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::LunchTableType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = queryResponse.query->value(2).toUInt();
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getAllLunchTableList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // lunch tables list
            queryPtr->prepare(
                    "SELECT idtable, name, guestnum "
                    "FROM lunchtables"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAllLunchTableList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::LunchTableType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = queryResponse.query->value(2).toUInt();
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListStatsPtr DAO::getLunchTableListStats()
    {
        ReservationItemListStatsPtr pReservationItemListStatsPtr(new ReservationItemListStats);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM lunchtables"
                    );
            return queryPtr;
        };
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getLunchTableListStats"));
            pReservationItemListStatsPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats);
            pReservationItemListStatsPtr->m_listStats->m_totalNum = queryResponse.query->value(0).toUInt();
        } else {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats(0));
        }
        return pReservationItemListStatsPtr;
    }
    //
    ReservationItemListResultPtr DAO::getOvenList(Uint32 page, Uint32 count)
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // oven list
            queryPtr->prepare(
                    "SELECT idoven, name "
                    "FROM ovens "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getOvenList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::OvenType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getAllOvenList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // oven list
            queryPtr->prepare(
                    "SELECT idoven, name "
                    "FROM ovens"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAllOvenList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::OvenType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListStatsPtr DAO::getOvenListStats()
    {
        ReservationItemListStatsPtr pReservationItemListStatsPtr(new ReservationItemListStats);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM ovens"
                    );
            return queryPtr;
        };
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getOvenListStats"));
            pReservationItemListStatsPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats);
            pReservationItemListStatsPtr->m_listStats->m_totalNum = queryResponse.query->value(0).toUInt();
        } else {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats(0));
        }
        return pReservationItemListStatsPtr;
    }
    //
    ReservationItemListResultPtr DAO::getFireplaceList(Uint32 page, Uint32 count)
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT idfireplace, name "
                    "FROM fireplaces "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getFireplaceList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::FireplaceType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getAllFireplaceList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT idfireplace, name "
                    "FROM fireplaces"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getAllFireplaceList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::FireplaceType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListStatsPtr DAO::getFireplaceListStats()
    {
        ReservationItemListStatsPtr pReservationItemListStatsPtr(new ReservationItemListStats);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM fireplaces"
                    );
            return queryPtr;
        };
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getFireplaceListStats"));
            pReservationItemListStatsPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats);
            pReservationItemListStatsPtr->m_listStats->m_totalNum = queryResponse.query->value(0).toUInt();
        } else {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats(0));
        }
        return pReservationItemListStatsPtr;
    }
    //
    bool DAO::makeTableReservation(const QDate &date, ReservationType reservationType, Uint16 guestNum, Int32 memberId, Int32 idTable, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert table reservation
            queryPtr->prepare(
                    "INSERT INTO tablereservation "
                    "(date, reservationtype, guestnum, idmember, idtable, isadmin) "
                    "VALUES (:date, :reservationtype, :guestnum, :idmember, :idtable, :isadmin)"
                    );
            queryPtr->bindValue(":date", date);
            queryPtr->bindValue(":reservationtype", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":guestnum", guestNum);
            queryPtr->bindValue(":idmember", memberId);
            queryPtr->bindValue(":idtable", idTable);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString dateLocalized = locale.toString(date, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("makeTableReservation reservationType %1 date %2 memberId %3").arg(static_cast<Uint16>(reservationType)).arg(dateLocalized).arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::updateTableReservation(Int32 reservationId, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update table reservation
            queryPtr->prepare(
                    "UPDATE tablereservation "
                    "SET isadmin = :isadmin "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateTableReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::cancelTableReservation(Int32 reservationId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // cancel table reservation
            queryPtr->prepare(
                    "DELETE FROM tablereservation "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("cancelTableReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::makeOvenReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idOven, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert oven reservation
            queryPtr->prepare(
                    "INSERT INTO ovenreservation "
                    "(date, reservationtype, idmember, idoven, isadmin) "
                    "VALUES (:date, :reservationtype, :idmember, :idoven, :isadmin)"
                    );
            queryPtr->bindValue(":date", date);
            queryPtr->bindValue(":reservationtype", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":idmember", memberId);
            queryPtr->bindValue(":idoven", idOven);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString dateLocalized = locale.toString(date, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("makeOvenReservation reservationType %1 date %2 memberId %3").arg(static_cast<Uint16>(reservationType)).arg(dateLocalized).arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::updateOvenReservation(Int32 reservationId, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update oven reservation
            queryPtr->prepare(
                    "UPDATE ovenreservation "
                    "SET isadmin = :isadmin "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateOvenReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::cancelOvenReservation(Int32 reservationId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // cancel oven reservation
            queryPtr->prepare(
                    "DELETE FROM ovenreservation "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("cancelOvenReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::updateFireplaceReservation(Int32 reservationId, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update fireplace reservation
            queryPtr->prepare(
                    "UPDATE fireplacereservation "
                    "SET isadmin = :isadmin "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateFireplaceReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::makeFireplaceReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idFireplace, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert fireplace reservation
            queryPtr->prepare(
                    "INSERT INTO fireplacereservation "
                    "(date, reservationtype, idmember, idfireplace, isadmin) "
                    "VALUES (:date, :reservationtype, :idmember, :idfireplace, :isadmin)"
                    );
            queryPtr->bindValue(":date", date);
            queryPtr->bindValue(":reservationtype", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":idmember", memberId);
            queryPtr->bindValue(":idfireplace", idFireplace);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString dateLocalized = locale.toString(date, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("makeFireplaceReservation reservationType %1 date %2 memberId %3").arg(static_cast<Uint16>(reservationType)).arg(dateLocalized).arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::cancelFireplaceReservation(Int32 reservationId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // cancel fireplace reservation
            queryPtr->prepare(
                    "DELETE FROM fireplacereservation "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("cancelFireplaceReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    MemberListResultPtr DAO::getSlowPayersList()
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // slow payers
            // SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember
            // returns list of distinct idmembers and their last account date
            // First INNER JOIN on the same table (account) gets balance for the row with last (newest) account date
            // Second INNER JOIN on members table get member information
            queryPtr->prepare(
                    "SELECT ac.idmember, member.username, member.name, member.surname1, member.surname2, member.image, ac.balance, member.lastmodified, member.reg_date "
                    "FROM account ac "
                    "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                    "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                    "INNER JOIN member ON member.idmember=ac.idmember "
                    "WHERE ac.balance<0 AND member.active=1"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getSlowPayersList"));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_username =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname1 =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_balance =  queryResponse.query->value(column++).toFloat();
                pMemberPtr->m_lastModified =  queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate =  queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        return pMemberListResultPtr;
    }
    //
    InvoiceListResultPtr DAO::getInvoiceListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceListResultPtr pInvoiceListResultPtr(new InvoiceListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // active invoice list by memberId
            queryPtr->prepare(
                    "SELECT member.username, invoice.idinvoice, invoice.date, invoice.total, invoice.last_modif "
                    "FROM invoice "
                    "INNER JOIN member ON member.idmember = invoice.idmember "
                    "WHERE invoice.idmember = :memberid AND invoice.state = :stateid "
                    "AND invoice.date BETWEEN :fromDate AND :toDate "
                    "ORDER BY date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // only active invoices
            queryPtr->bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoiceListByMemberId memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = InvoiceListPtr(new InvoiceList);
            while (queryResponse.query->next()) {
                Uint32 column = 0;
                InvoicePtr pInvoicePtr(new Invoice);
                pInvoicePtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pInvoicePtr->m_id =  queryResponse.query->value(column++).toInt();
                pInvoicePtr->m_memberId =  memberId;
                pInvoicePtr->m_state =  InvoiceState::Closed;
                pInvoicePtr->m_date =  queryResponse.query->value(column++).toDateTime();
                pInvoicePtr->m_date.setTimeSpec(Qt::UTC);
                pInvoicePtr->m_total =  queryResponse.query->value(column++).toFloat();
                pInvoicePtr->m_lastModified =  queryResponse.query->value(column++).toDateTime();
                pInvoicePtr->m_lastModified.setTimeSpec(Qt::UTC);
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        return pInvoiceListResultPtr;
    }
    //
    InvoiceListStatsResultPtr DAO::getInvoiceListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        InvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new InvoiceListStatsResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // active invoice list by memberId stats
            queryPtr->prepare(
                    "SELECT COUNT(*), SUM(total) FROM invoice "
                    "WHERE idmember = :memberid AND state = :stateid "
                    "AND date BETWEEN :fromDate AND :toDate"
                    );
            // only active invoices
            queryPtr->bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoiceListByMemberIdStats memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            pInvoiceListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pInvoiceListStatsResultPtr->m_stats = InvoiceListStatsPtr(new InvoiceListStats);
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = queryResponse.query->value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = queryResponse.query->value(1).toFloat();
        } else {
            pInvoiceListStatsResultPtr->m_stats = InvoiceListStatsPtr(new InvoiceListStats(0, 0.0));
        }
        return pInvoiceListStatsResultPtr;
    }
    //
    InvoiceListResultPtr DAO::getInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceListResultPtr pInvoiceListResultPtr(new InvoiceListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // active invoice list
            queryPtr->prepare(
                    "SELECT member.username, invoice.idinvoice, invoice.idmember, invoice.date, invoice.total, invoice.last_modif "
                    "FROM invoice "
                    "INNER JOIN member ON invoice.idmember=member.idmember "
                    "WHERE invoice.state = :stateid "
                    "AND invoice.date BETWEEN :fromDate AND :toDate "
                    "ORDER BY invoice.date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // only active invoices
            queryPtr->bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoiceList fromDate %2 toDate %3").arg(fromDateLocalized).arg(toDateLocalized));
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = InvoiceListPtr(new InvoiceList);
            while (queryResponse.query->next()) {
                InvoicePtr pInvoicePtr(new Invoice);
                Uint32 column = 0;
                pInvoicePtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pInvoicePtr->m_id = queryResponse.query->value(column++).toInt();
                pInvoicePtr->m_memberId = queryResponse.query->value(column++).toInt();
                pInvoicePtr->m_state = InvoiceState::Closed;
                pInvoicePtr->m_date = queryResponse.query->value(column++).toDateTime();
                pInvoicePtr->m_date.setTimeSpec(Qt::UTC);
                pInvoicePtr->m_total = queryResponse.query->value(column++).toFloat();
                pInvoicePtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pInvoicePtr->m_lastModified.setTimeSpec(Qt::UTC);
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        return pInvoiceListResultPtr;
    }
    //
    InvoiceListStatsResultPtr DAO::getInvoiceListStats(const QDate &fromDate, const QDate &toDate)
    {
        InvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new InvoiceListStatsResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // active invoice list stats
            queryPtr->prepare(
                    "SELECT COUNT(*), SUM(total) FROM invoice "
                    "WHERE state = :stateid "
                    "AND date BETWEEN :fromDate AND :toDate"
                    );
            // only active invoices
            queryPtr->bindValue(":stateid", static_cast<Int32>(InvoiceState::Closed));
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getInvoiceListStats fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            pInvoiceListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pInvoiceListStatsResultPtr->m_stats = InvoiceListStatsPtr(new InvoiceListStats);
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = queryResponse.query->value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = queryResponse.query->value(1).toFloat();
        } else {
            pInvoiceListStatsResultPtr->m_stats = InvoiceListStatsPtr(new InvoiceListStats(0, 0.0));
        }
        return pInvoiceListStatsResultPtr;
    }
    //
    ProviderListResultPtr DAO::getProviderList()
    {
        ProviderListResultPtr pProviderListResultPtr(new ProviderListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // provider list
            queryPtr->prepare(
                    "SELECT idprovider, name, image, reg_date, phone FROM provider"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderList"));
            pProviderListResultPtr->m_error = 1;
        } else {
            pProviderListResultPtr->m_list = ProviderListPtr(new ProviderList);
            while (queryResponse.query->next()) {
                ProviderPtr pProviderPtr(new Provider);
                pProviderPtr->m_id = queryResponse.query->value(0).toInt();
                pProviderPtr->m_name = queryResponse.query->value(1).toString();
                pProviderPtr->m_image = queryResponse.query->value(2).toString();
                pProviderPtr->m_regDate = queryResponse.query->value(3).toDate();
                pProviderPtr->m_phone = queryResponse.query->value(4).toString();
                pProviderListResultPtr->m_list->push_back(pProviderPtr);
            }
        }
        return pProviderListResultPtr;
    }
    //
    ProviderResultPtr DAO::getProviderById(Int32 providerId)
    {
        ProviderResultPtr pProviderResulPtr(new ProviderResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member by id
            queryPtr->prepare(
                    "SELECT provider.name, provider.image, provider.reg_date, provider.phone, provider.notes "
                    "FROM provider "
                    "WHERE provider.idprovider=:providerid"
                    );
            // member and balance
            queryPtr->bindValue(":providerid", providerId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);

        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderById providerId %1").arg(providerId));
            pProviderResulPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            ProviderPtr pProviderPtr(new Provider);
            Uint32 column = 0;
            pProviderPtr->m_id = providerId;
            pProviderPtr->m_name = queryResponse.query->value(column++).toString();
            pProviderPtr->m_image = queryResponse.query->value(column++).toString();
            pProviderPtr->m_regDate = queryResponse.query->value(column++).toDate();
            pProviderPtr->m_phone = queryResponse.query->value(column++).toString();
            pProviderPtr->m_notes = queryResponse.query->value(column++).toString();
            pProviderResulPtr->m_provider = pProviderPtr;
        }
        return pProviderResulPtr;
    }
    //
    bool DAO::updateProvider(const ProviderPtr &pProviderPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update  member
            queryPtr->prepare(
                    "UPDATE provider "
                    "SET name=:name, image=:image, reg_date=:reg_date, phone=:phone, notes=:notes "
                    "WHERE idprovider = :providerid"
                    );
            // obligatory
            queryPtr->bindValue(":providerid", pProviderPtr->m_id);
            queryPtr->bindValue(":name", pProviderPtr->m_name);
            queryPtr->bindValue(":reg_date", pProviderPtr->m_regDate);
            // optional
            if (pProviderPtr->m_image.isEmpty()) {
                queryPtr->bindValue(":image", QVariant());
            } else {
                queryPtr->bindValue(":image", pProviderPtr->m_image);
            }
            if (pProviderPtr->m_phone.isEmpty()) {
                queryPtr->bindValue(":phone", QVariant());
            } else {
                queryPtr->bindValue(":phone", pProviderPtr->m_phone);
            }
            if (pProviderPtr->m_notes.isEmpty()) {
                queryPtr->bindValue(":notes", QVariant());
            } else {
                queryPtr->bindValue(":notes", pProviderPtr->m_notes);
            }
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateProvider providerId %1").arg(pProviderPtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    ProductItemListResultPtr DAO::getProductsFromProvider(Int32 providerId)
    {
        ProductItemListResultPtr pIListResultPtr(new ProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // ProductItems by provider
            queryPtr->prepare("SELECT idproduct_item, name, name_es, image, reg_date, idproduct_family, price FROM product_item WHERE active=1 AND idprovider=:providerId");
            // bind value
            queryPtr->bindValue(":providerId", providerId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductsFromProvider providerId %1").arg(providerId));
            pIListResultPtr->m_error = 1;
        } else {
            pIListResultPtr->m_list = ProductItemListPtr(new ProductItemList);
            while (queryResponse.query->next()) {
                ProductItemPtr pfPtr(new ProductItem);
                pfPtr->m_id = queryResponse.query->value(0).toUInt();
                pfPtr->m_nameEus = queryResponse.query->value(1).toString();
                pfPtr->m_nameEs = queryResponse.query->value(2).toString();
                pfPtr->m_imagePath = queryResponse.query->value(3).toString();
                pfPtr->m_active = true;
                pfPtr->m_regDate = queryResponse.query->value(4).toDateTime();
                pfPtr->m_regDate.setTimeSpec(Qt::UTC);
                pfPtr->m_familyId = queryResponse.query->value(5).toInt();
                pfPtr->m_price = queryResponse.query->value(6).toFloat();
                pIListResultPtr->m_list->push_back(pfPtr);
            }
        }
        return pIListResultPtr;
    }
    //
    Int32 DAO::createProvider(const ProviderPtr &pProviderPtr)
    {
        auto createQuery = [=](){
            QDate today(QDateTime::currentDateTimeUtc().date());
            QueryPtr queryPtr(new QSqlQuery);
            // create provider
            queryPtr->prepare(
                    "INSERT INTO provider "
                    "(name, image, reg_date, phone, notes) "
                    "VALUES (:name, :image, :reg_date, :phone, :notes)"
                    );
            queryPtr->bindValue(":name", pProviderPtr->m_name);
            if (pProviderPtr->m_image.isEmpty()) {
                queryPtr->bindValue(":image", QVariant());
            } else {
                queryPtr->bindValue(":image", pProviderPtr->m_image);
            }
            queryPtr->bindValue(":reg_date", today);
            if (pProviderPtr->m_phone.isEmpty()) {
                queryPtr->bindValue(":phone", QVariant());
            } else {
                queryPtr->bindValue(":phone", pProviderPtr->m_phone);
            }
            if (pProviderPtr->m_notes.isEmpty()) {
                queryPtr->bindValue(":notes", QVariant());
            } else {
                queryPtr->bindValue(":notes", pProviderPtr->m_notes);
            }
            return queryPtr;
        };

        Int32 providerId = -1;

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createProvider name %1 image %2 phone %3").arg(pProviderPtr->m_name).arg(pProviderPtr->m_image).arg(pProviderPtr->m_phone));
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };

            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                        QString("createProvider could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                providerId = lastQueryResponse.query->value(0).toUInt();
            }
        }
        return providerId;
    }
    //
    StockProductItemListResultPtr DAO::getAllStockProductsList()
    {
        StockProductItemListResultPtr pStockProductItemListResultPtr(new StockProductItemListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // product items query
            queryPtr->prepare(
                    "SELECT product_item.idproduct_item, product_item.name, product_item.name_es, product_item.active, product_item.image, product_item.reg_date, product_item.price, product_family.name, product_family.name_es, provider.name, product_item.stock "
                    "FROM product_item "
                    "INNER JOIN product_family ON product_family.idproduct_family=product_item.idproduct_family "
                    "INNER JOIN provider ON provider.idprovider=product_item.idprovider "
                    "ORDER BY product_item.idproduct_item DESC "
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, QString("getAllStockProductsList"));
            pStockProductItemListResultPtr->m_error = 1;
        } else {
            pStockProductItemListResultPtr->m_list = StockProductItemListPtr(new StockProductItemList);
            while (queryResponse.query->next()) {
                StockProductItemPtr pStockProductItemPtr(new StockProductItem);
                pStockProductItemPtr->m_id = queryResponse.query->value(0).toInt();
                pStockProductItemPtr->m_nameEus = queryResponse.query->value(1).toString();
                pStockProductItemPtr->m_nameEs = queryResponse.query->value(2).toString();
                pStockProductItemPtr->m_active = queryResponse.query->value(3).toInt() == 1;
                pStockProductItemPtr->m_imagePath = queryResponse.query->value(4).toString();
                pStockProductItemPtr->m_regDate = queryResponse.query->value(5).toDateTime();
                pStockProductItemPtr->m_regDate.setTimeSpec(Qt::UTC);
                pStockProductItemPtr->m_price = queryResponse.query->value(6).toFloat();
                pStockProductItemPtr->m_familyNameEus = queryResponse.query->value(7).toString();
                pStockProductItemPtr->m_familyNameEs = queryResponse.query->value(8).toString();
                pStockProductItemPtr->m_providerName = queryResponse.query->value(9).toString();
                pStockProductItemPtr->m_stock = queryResponse.query->value(10).toInt();
                pStockProductItemListResultPtr->m_list->push_back(pStockProductItemPtr);
            }
        }
        return pStockProductItemListResultPtr;
    }
    //
    StockProductItemListResultPtr DAO::getStockProductsList(Uint32 page, Uint32 count)
    {
        StockProductItemListResultPtr pStockProductItemListResultPtr(new StockProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product items query
            queryPtr->prepare(
                    "SELECT product_item.idproduct_item, product_item.name, product_item.name_es, product_item.active, product_item.image, product_item.reg_date, product_item.price, product_family.name, product_family.name_es, provider.name, product_item.stock "
                    "FROM product_item "
                    "INNER JOIN product_family ON product_family.idproduct_family=product_item.idproduct_family "
                    "INNER JOIN provider ON provider.idprovider=product_item.idprovider "
                    "ORDER BY product_item.idproduct_item DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getStockProductsList page %1 count %2").arg(page).arg(count));
            pStockProductItemListResultPtr->m_error = 1;
        } else {
            pStockProductItemListResultPtr->m_list = StockProductItemListPtr(new StockProductItemList);
            while (queryResponse.query->next()) {
                StockProductItemPtr pStockProductItemPtr(new StockProductItem);
                pStockProductItemPtr->m_id = queryResponse.query->value(0).toInt();
                pStockProductItemPtr->m_nameEus = queryResponse.query->value(1).toString();
                pStockProductItemPtr->m_nameEs = queryResponse.query->value(2).toString();
                pStockProductItemPtr->m_active = queryResponse.query->value(3).toInt() == 1;
                pStockProductItemPtr->m_imagePath = queryResponse.query->value(4).toString();
                pStockProductItemPtr->m_regDate = queryResponse.query->value(5).toDateTime();
                pStockProductItemPtr->m_regDate.setTimeSpec(Qt::UTC);
                pStockProductItemPtr->m_price = queryResponse.query->value(6).toFloat();
                pStockProductItemPtr->m_familyNameEus = queryResponse.query->value(7).toString();
                pStockProductItemPtr->m_familyNameEs = queryResponse.query->value(8).toString();
                pStockProductItemPtr->m_providerName = queryResponse.query->value(9).toString();
                pStockProductItemPtr->m_stock = queryResponse.query->value(10).toInt();
                pStockProductItemListResultPtr->m_list->push_back(pStockProductItemPtr);
            }
        }
        return pStockProductItemListResultPtr;
    }
    //
    ProductListStatsResultPtr DAO::getProductsListStats()
    {
        ProductListStatsResultPtr pProductListStatsResultPtr(new ProductListStatsResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product items stats query
            queryPtr->prepare(
                    "SELECT COUNT(*) FROM product_item"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductsListStats"));
            pProductListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pProductListStatsResultPtr->m_stats = ProductListStatsPtr(new ProductListStats);
            pProductListStatsResultPtr->m_stats->m_totalNumProducts = queryResponse.query->value(0).toUInt();
        } else {
            pProductListStatsResultPtr->m_stats = ProductListStatsPtr(new ProductListStats(0));
        }
        return pProductListStatsResultPtr;
    }
    //
    bool DAO::updateStock(Int32 productItemId, Int32 count)
    {

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update product item stock
            queryPtr->prepare(
                    "UPDATE product_item SET stock = stock + :count WHERE idproduct_item = :productid"
                    );
            queryPtr->bindValue(":count", count);
            queryPtr->bindValue(":productid", productItemId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateStock productItemId %1 count %2").arg(productItemId).arg(count));
        }
        return !queryResponse.error;
    }
    //
    ProductItemResultPtr DAO::getProductItem(Int32 productItemId)
    {
        ProductItemResultPtr pProductItemResultPtr(new ProductItemResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product item
            queryPtr->prepare(
                    "SELECT name, name_es, active, image, reg_date, price, idproduct_family, idprovider, stock FROM product_item "
                    "WHERE idproduct_item = :productid"
                    );
            queryPtr->bindValue(":productid", productItemId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductItem productItemId %1").arg(productItemId));
            pProductItemResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            ProductItemPtr pProductItemPtr(new ProductItem);
            pProductItemPtr->m_id = productItemId;
            pProductItemPtr->m_nameEus = queryResponse.query->value(0).toString();
            pProductItemPtr->m_nameEs = queryResponse.query->value(1).toString();
            pProductItemPtr->m_active =  queryResponse.query->value(2).toInt() == 1;
            pProductItemPtr->m_imagePath = queryResponse.query->value(3).toString();
            pProductItemPtr->m_regDate = queryResponse.query->value(4).toDateTime();
            pProductItemPtr->m_regDate.setTimeSpec(Qt::UTC);
            pProductItemPtr->m_price = queryResponse.query->value(5).toFloat();
            pProductItemPtr->m_familyId = queryResponse.query->value(6).toInt();
            pProductItemPtr->m_providerId = queryResponse.query->value(7).toInt();
            pProductItemPtr->m_stock = queryResponse.query->value(8).toInt();
            pProductItemResultPtr->m_item = pProductItemPtr;
        }
        return pProductItemResultPtr;
    }
    //
    bool DAO::updateProductItem(const ProductItemPtr &pProductPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update product item
            queryPtr->prepare(
                    "UPDATE product_item "
                    "SET name=:name, name_es=:name_es, image=:image, active=:active, idproduct_family=:familyid, price=:price, "
                    "idprovider=:providerid, stock=:stock "
                    "WHERE idproduct_item = :productid"
                    );
            queryPtr->bindValue(":name", pProductPtr->m_nameEus);
            queryPtr->bindValue(":name_es", pProductPtr->m_nameEs);
            queryPtr->bindValue(":image", pProductPtr->m_imagePath);
            queryPtr->bindValue(":active", (pProductPtr->m_active)?(1):(0));
            queryPtr->bindValue(":familyid", pProductPtr->m_familyId);
            queryPtr->bindValue(":price", pProductPtr->m_price);
            queryPtr->bindValue(":providerid", pProductPtr->m_providerId);
            queryPtr->bindValue(":stock", pProductPtr->m_stock);
            queryPtr->bindValue(":productid", pProductPtr->m_id);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateProductItem productId %1").arg(pProductPtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    Int32 DAO::createProductItem(const ProductItemPtr &pProductPtr)
    {
        Int32 itemId = -1;
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // create product item
            queryPtr->prepare(
                    "INSERT INTO product_item "
                    "(name, name_es, image, active, reg_date, idproduct_family, price, idprovider, stock) "
                    "VALUES (:name, :name_es, :image, :active, :reg_date, :familyid, :price, :providerid, :stock)"
                    );
            queryPtr->bindValue(":name", pProductPtr->m_nameEus);
            queryPtr->bindValue(":name_es", pProductPtr->m_nameEs);
            queryPtr->bindValue(":image", pProductPtr->m_imagePath);
            queryPtr->bindValue(":active", (pProductPtr->m_active)?(1):(0));
            queryPtr->bindValue(":reg_date", pProductPtr->m_regDate);
            queryPtr->bindValue(":familyid", pProductPtr->m_familyId);
            queryPtr->bindValue(":price", pProductPtr->m_price);
            queryPtr->bindValue(":providerid", pProductPtr->m_providerId);
            queryPtr->bindValue(":stock", pProductPtr->m_stock);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createProductItem productItemName %1").arg(pProductPtr->m_nameEus));
            return -1;
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };

            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createProductItem could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                itemId = lastQueryResponse.query->value(0).toUInt();
            }
        }

        return itemId;
    }
    //
    ProductFamilyResultPtr DAO::getProductFamily(Int32 familyId)
    {
        ProductFamilyResultPtr pProductFamilyResultPtr(new ProductFamilyResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product family item
            queryPtr->prepare(
                    "SELECT name, name_es, active, image, reg_date FROM product_family "
                    "WHERE idproduct_family = :familyid"
                    );
            queryPtr->bindValue(":familyid", familyId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductFamily familyId %1").arg(familyId));
            pProductFamilyResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            ProductFamilyPtr pProductFamilyPtr(new ProductFamily);
            pProductFamilyPtr->m_id = familyId;
            pProductFamilyPtr->m_nameEus = queryResponse.query->value(0).toString();
            pProductFamilyPtr->m_nameEs = queryResponse.query->value(1).toString();
            pProductFamilyPtr->m_active =  queryResponse.query->value(2).toInt() == 1;
            pProductFamilyPtr->m_imagePath = queryResponse.query->value(3).toString();
            pProductFamilyPtr->m_regDate = queryResponse.query->value(4).toDateTime();
            pProductFamilyPtr->m_regDate.setTimeSpec(Qt::UTC);
            pProductFamilyResultPtr->m_family = pProductFamilyPtr;
        }
        return pProductFamilyResultPtr;
    }
    //
    bool DAO::updateProductFamilyItem(const ProductFamilyPtr &pFamilyPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update product family item
            queryPtr->prepare(
                    "UPDATE product_family "
                    "SET name=:name, name_es=:name_es, image=:image, active=:active "
                    "WHERE idproduct_family = :familyid"
                    );
            queryPtr->bindValue(":name", pFamilyPtr->m_nameEus);
            queryPtr->bindValue(":name_es", pFamilyPtr->m_nameEs);
            queryPtr->bindValue(":image", pFamilyPtr->m_imagePath);
            queryPtr->bindValue(":active", (pFamilyPtr->m_active)?(1):(0));
            queryPtr->bindValue(":familyid", pFamilyPtr->m_id);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateProductFamilyItem familyId %1").arg(pFamilyPtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    Int32 DAO::createProductFamilyItem(const ProductFamilyPtr &pFamilyPtr)
    {
        Int32 familyId = -1;

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // create product family item
            queryPtr->prepare(
                    "INSERT INTO product_family "
                    "(name, name_es, image, active, reg_date) "
                    "VALUES (:name, :name_es, :image, :active, :reg_date)"
                    );
            queryPtr->bindValue(":name", pFamilyPtr->m_nameEus);
            queryPtr->bindValue(":name_es", pFamilyPtr->m_nameEs);
            queryPtr->bindValue(":image", pFamilyPtr->m_imagePath);
            queryPtr->bindValue(":active", (pFamilyPtr->m_active)?(1):(0));
            queryPtr->bindValue(":reg_date", pFamilyPtr->m_regDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createProductFamilyItem familyName %1").arg(pFamilyPtr->m_nameEus));
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };
            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                        QString("createProductFamilyItem could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                familyId = lastQueryResponse.query->value(0).toUInt();
            }
        }

        return familyId;
    }
    //
    InvoiceProductItemListResultPtr DAO::getProductExpensesList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr(new InvoiceProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product expenses list
            // only closed
            queryPtr->prepare(
                    "SELECT product_item.idproduct_item, product_item.name, product_item.name_es, product_item.image, SUM(inv_prod.price * inv_prod.count), SUM(inv_prod.count) "
                    "FROM invoice "
                    "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                    "INNER JOIN product_item ON product_item.idproduct_item=inv_prod.idproduct_item "
                    "WHERE invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1 "
                    "GROUP BY inv_prod.idproduct_item "
                    "LIMIT :limit OFFSET :offset"
                    );
            // only active invoices
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductExpensesList fromDate %1 toDate %2 page %3 count %4").arg(fromDateLocalized).arg(toDateLocalized).arg(page).arg(count));
            pInvoiceProductItemListResultPtr->m_error = 1;
        } else {
            pInvoiceProductItemListResultPtr->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (queryResponse.query->next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId =  queryResponse.query->value(0).toInt();
                pInvoiceProductItemPtr->m_productnameEus =  queryResponse.query->value(1).toString();
                pInvoiceProductItemPtr->m_productnameEs =  queryResponse.query->value(2).toString();
                pInvoiceProductItemPtr->m_imagePath =  queryResponse.query->value(3).toString();
                pInvoiceProductItemPtr->m_pricePerUnit =  queryResponse.query->value(4).toFloat();
                pInvoiceProductItemPtr->m_count =  queryResponse.query->value(5).toUInt();
                pInvoiceProductItemListResultPtr->m_list->push_back(pInvoiceProductItemPtr);
            }
        }
        return pInvoiceProductItemListResultPtr;
    }
    //
    InvoiceProductItemCounterStatsResultPtr DAO::getProductExpensesListStats(const QDate &fromDate, const QDate &toDate)
    {
        InvoiceProductItemCounterStatsResultPtr pIPISResultPtr(new InvoiceProductItemCounterStatsResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product expenses list stats
            // only closed
            queryPtr->prepare(
                    "SELECT COUNT(DISTINCT inv_prod.idproduct_item) "
                    "FROM invoice "
                    "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                    "WHERE invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductExpensesListStats fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            pIPISResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pIPISResultPtr->m_stats = InvoiceProductItemCounterStatsPtr(new InvoiceProductItemCounterStats);
            pIPISResultPtr->m_stats->m_totalProducts = queryResponse.query->value(0).toUInt();
        } else {
            pIPISResultPtr->m_stats = InvoiceProductItemCounterStatsPtr(new InvoiceProductItemCounterStats);
        }
        return pIPISResultPtr;
    }
    //
    InvoiceProductItemListResultPtr DAO::getProductExpensesListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        InvoiceProductItemListResultPtr pIPILResult(new InvoiceProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product expenses list by memberId
            queryPtr->prepare(
                    "SELECT product_item.idproduct_item, product_item.name, product_item.name_es, product_item.image, SUM(inv_prod.price * inv_prod.count), SUM(inv_prod.count) "
                    "FROM invoice "
                    "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                    "INNER JOIN product_item ON product_item.idproduct_item=inv_prod.idproduct_item "
                    "WHERE invoice.idmember=:memberid AND invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1 "
                    "GROUP BY inv_prod.idproduct_item "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductExpensesListByMemberId memberId %1 fromDate %2 toDate %3 page %4 count %5").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized).arg(page).arg(count));
            pIPILResult->m_error = 1;
        } else {
            pIPILResult->m_list = InvoiceProductItemListPtr(new InvoiceProductItemList);
            while (queryResponse.query->next()) {
                InvoiceProductItemPtr pInvoiceProductItemPtr(new InvoiceProductItem);
                pInvoiceProductItemPtr->m_productId =  queryResponse.query->value(0).toInt();
                pInvoiceProductItemPtr->m_productnameEus =  queryResponse.query->value(1).toString();
                pInvoiceProductItemPtr->m_productnameEs =  queryResponse.query->value(2).toString();
                pInvoiceProductItemPtr->m_imagePath =  queryResponse.query->value(3).toString();
                pInvoiceProductItemPtr->m_pricePerUnit =  queryResponse.query->value(4).toFloat();
                pInvoiceProductItemPtr->m_count =  queryResponse.query->value(5).toUInt();
                pIPILResult->m_list->push_back(pInvoiceProductItemPtr);
            }
        }
        return pIPILResult;
    }
    //
    InvoiceProductItemCounterStatsResultPtr DAO::getProductExpensesListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        InvoiceProductItemCounterStatsResultPtr pIPISResult(new InvoiceProductItemCounterStatsResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // product expenses list by memberId stats
            queryPtr->prepare(
                    "SELECT COUNT(DISTINCT inv_prod.idproduct_item) "
                    "FROM invoice "
                    "INNER JOIN inv_prod ON inv_prod.idinvoice=invoice.idinvoice "
                    "WHERE invoice.idmember=:memberid AND invoice.date BETWEEN :fromDate AND :toDate AND invoice.state=1"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProductExpensesListByMemberIdStats memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            pIPISResult->m_error = 1;
        } else if (queryResponse.query->next()) {
            pIPISResult->m_stats = InvoiceProductItemCounterStatsPtr(new InvoiceProductItemCounterStats);
            pIPISResult->m_stats->m_totalProducts = queryResponse.query->value(0).toUInt();
        } else {
            pIPISResult->m_stats = InvoiceProductItemCounterStatsPtr(new InvoiceProductItemCounterStats);
        }
        return pIPISResult;
    }
    //
    bool DAO::createProviderInvoice(const ProviderInvoicePtr &pProviderInvoicePtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // create provider invoice
            queryPtr->prepare(
                    "INSERT INTO provider_invoices "
                    "(idprovider_invoices, date, total, idprovider) "
                    "VALUES (:id, :date, :total, :providerid)"
                    );
            queryPtr->bindValue(":id", pProviderInvoicePtr->m_id);
            queryPtr->bindValue(":date", pProviderInvoicePtr->m_regDate);
            queryPtr->bindValue(":total", pProviderInvoicePtr->m_total);
            queryPtr->bindValue(":providerid", pProviderInvoicePtr->m_providerid);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createProviderInvoice providerId %1").arg(pProviderInvoicePtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::createProviderInvoiceProduct(const QString &invoiceId, Int32 productId, Uint32 count)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // create provider invoice product
            queryPtr->prepare(
                    "INSERT INTO provider_invoices_product "
                    "(provider_invoices_idprovider_invoices, product_item_idproduct_item, count) "
                    "VALUES (:providerinvoiceid, :productid, :count)"
                    );
            queryPtr->bindValue(":providerinvoiceid", invoiceId);
            queryPtr->bindValue(":productid", productId);
            queryPtr->bindValue(":count", count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createProviderInvoiceProduct providerInvoiceId %1 productId %2 count %3").arg(invoiceId).arg(productId).arg(count));
        }
        return !queryResponse.error;
    }
    //
    ProviderInvoiceListResultPtr DAO::getProviderInvoiceList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        ProviderInvoiceListResultPtr pInvoiceListResultPtr(new ProviderInvoiceListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // provider invoice list
            queryPtr->prepare(
                    "SELECT provider_invoices.idprovider_invoices, provider_invoices.date, provider_invoices.total, provider_invoices.idprovider, provider.name "
                    "FROM provider_invoices "
                    "INNER JOIN provider ON provider.idprovider = provider_invoices.idprovider "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "ORDER BY date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderInvoiceList fromDate %1 toDate %2 page %3 count %4").arg(fromDateLocalized).arg(toDateLocalized).arg(page).arg(count));
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = ProviderInvoiceListPtr(new ProviderInvoiceList);
            while (queryResponse.query->next()) {
                ProviderInvoicePtr pInvoicePtr(new ProviderInvoice);
                pInvoicePtr->m_id = queryResponse.query->value(0).toString();
                pInvoicePtr->m_regDate = queryResponse.query->value(1).toDate();
                pInvoicePtr->m_total = queryResponse.query->value(2).toFloat();
                pInvoicePtr->m_providerid = queryResponse.query->value(3).toInt();
                pInvoicePtr->m_providerName = queryResponse.query->value(4).toString();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        return pInvoiceListResultPtr;
    }
    //
    ProviderInvoiceListStatsResultPtr DAO::getProviderInvoiceListStats(const QDate &fromDate, const QDate &toDate)
    {
        ProviderInvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new ProviderInvoiceListStatsResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // provider invoice list stats
            queryPtr->prepare(
                    "SELECT COUNT(*), SUM(total) FROM provider_invoices "
                    "WHERE date BETWEEN :fromDate AND :toDate"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderInvoiceListStats fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            pInvoiceListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pInvoiceListStatsResultPtr->m_stats = ProviderInvoiceListStatsPtr(new ProviderInvoiceListStats);
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = queryResponse.query->value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = queryResponse.query->value(1).toFloat();
        } else {
            pInvoiceListStatsResultPtr->m_stats = ProviderInvoiceListStatsPtr(new ProviderInvoiceListStats(0, 0.0));
        }
        return pInvoiceListStatsResultPtr;
    }
    //
    ProviderInvoiceListResultPtr DAO::getProviderInvoiceListByProviderId(Int32 providerId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        ProviderInvoiceListResultPtr pInvoiceListResultPtr(new ProviderInvoiceListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // provider invoice list by provider
            queryPtr->prepare(
                    "SELECT idprovider_invoices, date, total, idprovider FROM provider_invoices "
                    "WHERE idprovider = :providerid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "ORDER BY date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":providerid", providerId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderInvoiceListByProviderId providerId %1 fromDate %2 toDate %3 page %4 count %5").arg(providerId).arg(fromDateLocalized).arg(toDateLocalized).arg(page).arg(count));
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = ProviderInvoiceListPtr(new ProviderInvoiceList);
            while (queryResponse.query->next()) {
                ProviderInvoicePtr pInvoicePtr(new ProviderInvoice);
                pInvoicePtr->m_id = queryResponse.query->value(0).toString();
                pInvoicePtr->m_regDate = queryResponse.query->value(1).toDate();
                pInvoicePtr->m_total = queryResponse.query->value(2).toFloat();
                pInvoicePtr->m_providerid = queryResponse.query->value(3).toInt();
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        return pInvoiceListResultPtr;
    }
    //
    ProviderInvoiceListStatsResultPtr DAO::getProviderInvoiceListByProviderIdStats(Int32 providerId, const QDate &fromDate, const QDate &toDate)
    {
        ProviderInvoiceListStatsResultPtr pInvoiceListStatsResultPtr(new ProviderInvoiceListStatsResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // provider invoice list Stats by provider
            queryPtr->prepare(
                    "SELECT COUNT(*), SUM(total) FROM provider_invoices "
                    "WHERE idprovider = :providerid "
                    "AND date BETWEEN :fromDate AND :toDate"
                    );
            queryPtr->bindValue(":providerid", providerId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderInvoiceListByProviderIdStats providerId %1 fromDate %2 toDate %3").arg(providerId).arg(fromDateLocalized).arg(toDateLocalized));
            pInvoiceListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pInvoiceListStatsResultPtr->m_stats = ProviderInvoiceListStatsPtr(new ProviderInvoiceListStats);
            pInvoiceListStatsResultPtr->m_stats->m_totalNumInvoices = queryResponse.query->value(0).toUInt();
            pInvoiceListStatsResultPtr->m_stats->m_totalAmount = queryResponse.query->value(1).toFloat();
        } else {
            pInvoiceListStatsResultPtr->m_stats = ProviderInvoiceListStatsPtr(new ProviderInvoiceListStats(0, 0.0));
        }
        return pInvoiceListStatsResultPtr;
    }
    //
    DepositListResultPtr DAO::getUncheckedDeposits()
    {
        DepositListResultPtr pDepositListResultPtr(new DepositListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // unchecked deposit list
            queryPtr->prepare(
                    "SELECT member.username, deposit.iddeposit, deposit.date, deposit.total, deposit.idmember "
                    "FROM deposit "
                    "INNER JOIN member ON member.idmember = deposit.idmember "
                    "WHERE deposit.state = 0"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getUncheckedDeposits"));
            pDepositListResultPtr->m_error = 1;
        } else {
            pDepositListResultPtr->m_list = DepositListPtr(new DepositList);
            while (queryResponse.query->next()) {
                Uint32 column = 0;
                DepositPtr pDepositPtr(new Deposit);
                pDepositPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pDepositPtr->m_id = queryResponse.query->value(column++).toInt();
                pDepositPtr->m_date = queryResponse.query->value(column++).toDateTime();
                pDepositPtr->m_date.setTimeSpec(Qt::UTC);
                pDepositPtr->m_total = queryResponse.query->value(column++).toFloat();
                pDepositPtr->m_memberId = queryResponse.query->value(column++).toInt();
                pDepositListResultPtr->m_list->push_back(pDepositPtr);
            }
        }

        return pDepositListResultPtr;
    }
    //
    bool DAO::closeDeposit(Int32 depositId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // close deposit
            queryPtr->prepare(
                    "UPDATE deposit "
                    "SET state=1 "
                    "WHERE iddeposit=:depositid"
                    );
            queryPtr->bindValue(":depositid", depositId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("closeDeposit depositId %1").arg(depositId));
        }
        return !queryResponse.error;
    }
    //
    MemberListResultPtr DAO::getMemberList(bool onlyPostalSend, Uint32 page, Uint32 count)
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            if (onlyPostalSend) {
                // member filtered list
                queryPtr->prepare(
                        "SELECT member.idmember, member.username, member.name, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                        "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, member.id_card, member.card, member.type, "
                        "member.notes, ac.balance "
                        "FROM account ac "
                        "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                        "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                        "INNER JOIN member ON member.idmember=ac.idmember "
                        "WHERE member.postal_send = 1 "
                        "ORDER BY member.surname1 ASC "
                        "LIMIT :limit OFFSET :offset"
                        );
            } else {
                // member list
                queryPtr->prepare(
                        "SELECT member.idmember, member.username, member.name, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                        "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, member.id_card, member.card, member.type, "
                        "member.notes, ac.balance "
                        "FROM account ac "
                        "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                        "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                        "INNER JOIN member ON member.idmember=ac.idmember "
                        "ORDER BY member.surname1 ASC "
                        "LIMIT :limit OFFSET :offset"
                        );
            }
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getMemberList postalSend %1 page %2 count %3").arg(onlyPostalSend).arg(page).arg(count));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                Uint32 column = 0;
                MemberPtr pMemberPtr(new Member);
                pMemberPtr->m_id = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberPtr->m_active = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_address = queryResponse.query->value(column++).toString();
                pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
                pMemberPtr->m_town = queryResponse.query->value(column++).toString();
                pMemberPtr->m_state = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_email = queryResponse.query->value(column++).toString();
                pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
                pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
                pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
                pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
                pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
                pMemberPtr->m_balance = queryResponse.query->value(column++).toFloat();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }

        return pMemberListResultPtr;
    }
    //
    MemberListStatsResultPtr DAO::getMemberListStats(bool onlyPostalSend)
    {
        MemberListStatsResultPtr pMemberListStatsResultPtr(new MemberListStatsResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            if (onlyPostalSend) {
                // member list filtered stats
                queryPtr->prepare(
                        "SELECT COUNT(*) FROM member "
                        "WHERE postal_send = 1"
                        );
            } else {
                // member list stats
                queryPtr->prepare(
                        "SELECT COUNT(*) FROM member"
                        );
            }
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getMemberListStats postalSend %1").arg(onlyPostalSend));
            pMemberListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pMemberListStatsResultPtr->m_stats = MemberListStatsPtr(new MemberListStats);
            pMemberListStatsResultPtr->m_stats->m_totalMembers = queryResponse.query->value(0).toUInt();
        } else {
            pMemberListStatsResultPtr->m_stats = MemberListStatsPtr(new MemberListStats(0));
        }
        return pMemberListStatsResultPtr;
    }
    //
    bool DAO::updateMember(const MemberPtr &pMemberPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update  member
            queryPtr->prepare(
                    "UPDATE member "
                    "SET username=:username, name=:name, surname1=:surname1, surname2=:surname2, image=:image, lastmodified=:lastmodified, active=:active, isAdmin=:isadmin, birth=:birth, "
                    "address=:address, zip_code=:zip_code, town=:town, state=:state, tel=:tel, tel2=:tel2, email=:email, bank_account=:bank_account, postal_send=:postal_send, "
                    "notes=:notes, id_card=:id_card, card=:card, type=:type, reg_date=:reg_date "
                    "WHERE idmember = :memberid"
                    );
            // obligatory
            queryPtr->bindValue(":memberid", pMemberPtr->m_id);
            queryPtr->bindValue(":username", pMemberPtr->m_username);
            queryPtr->bindValue(":name", pMemberPtr->m_name);
            queryPtr->bindValue(":surname1", pMemberPtr->m_surname1);
            queryPtr->bindValue(":surname2", pMemberPtr->m_surname2);
            queryPtr->bindValue(":lastmodified", pMemberPtr->m_lastModified);
            queryPtr->bindValue(":active", pMemberPtr->m_active?1:0);
            queryPtr->bindValue(":isadmin", pMemberPtr->m_isAdmin?1:0);
            queryPtr->bindValue(":bank_account", pMemberPtr->m_bank_account);
            queryPtr->bindValue(":postal_send", pMemberPtr->m_postalSend?1:0);
            queryPtr->bindValue(":type", pMemberPtr->m_memberType);
            queryPtr->bindValue(":reg_date", pMemberPtr->m_regDate);
            // optional
            if (pMemberPtr->m_imagePath.isEmpty()) {
                queryPtr->bindValue(":image", QVariant());
            } else {
                queryPtr->bindValue(":image", pMemberPtr->m_imagePath);
            }
            if (pMemberPtr->m_birthdate.isValid()) {
                queryPtr->bindValue(":birth", pMemberPtr->m_birthdate);
            } else {
                queryPtr->bindValue(":birth", QVariant());
            }
            if (pMemberPtr->m_address.isEmpty()) {
                queryPtr->bindValue(":address", QVariant());
            } else {
                queryPtr->bindValue(":address", pMemberPtr->m_address);
            }
            if (pMemberPtr->m_zipCode.isEmpty()) {
                queryPtr->bindValue(":zip_code", QVariant());
            } else {
                queryPtr->bindValue(":zip_code", pMemberPtr->m_zipCode);
            }
            if (pMemberPtr->m_town.isEmpty()) {
                queryPtr->bindValue(":town", QVariant());
            } else {
                queryPtr->bindValue(":town", pMemberPtr->m_town);
            }
            if (pMemberPtr->m_state.isEmpty()) {
                queryPtr->bindValue(":state", QVariant());
            } else {
                queryPtr->bindValue(":state", pMemberPtr->m_state);
            }
            if (pMemberPtr->m_phone.isEmpty()) {
                queryPtr->bindValue(":tel", QVariant());
            } else {
                queryPtr->bindValue(":tel", pMemberPtr->m_phone);
            }
            if (pMemberPtr->m_phone2.isEmpty()) {
                queryPtr->bindValue(":tel2", QVariant());
            } else {
                queryPtr->bindValue(":tel2", pMemberPtr->m_phone2);
            }
            if (pMemberPtr->m_email.isEmpty()) {
                queryPtr->bindValue(":email", QVariant());
            } else {
                queryPtr->bindValue(":email", pMemberPtr->m_email);
            }
            if (pMemberPtr->m_notes.isEmpty()) {
                queryPtr->bindValue(":notes", QVariant());
            } else {
                queryPtr->bindValue(":notes", pMemberPtr->m_notes);
            }
            if (pMemberPtr->m_idCard.isEmpty()) {
                queryPtr->bindValue(":id_card", QVariant());
            } else {
                queryPtr->bindValue(":id_card", pMemberPtr->m_idCard);
            }
            if (pMemberPtr->m_cardNumber.isEmpty()) {
                queryPtr->bindValue(":card", QVariant());
            } else {
                queryPtr->bindValue(":card", pMemberPtr->m_cardNumber);
            }
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateMember memberId %1").arg(pMemberPtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    Int32 DAO::createMember(const MemberPtr &pMemberPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // create member
            queryPtr->prepare(
                    "INSERT INTO member "
                    "(username, name, surname1, surname2, image, lastmodified, reg_date, active, isAdmin, birth, "
                    "address, zip_code, town, state, tel, tel2, email, bank_account, postal_send, "
                    "notes, pwd, lastlogin, id_card, card, type) "
                    "VALUES (:username, :name, :surname1, :surname2, :image, :lastmodified, :reg_date, :active, :isadmin, :birth, "
                    ":address, :zip_code, :town, :state, :tel, :tel2, :email, :bank_account, :postal_send, "
                    ":notes, :pwd, :lastlogin, :id_card, :card, :type)"
                    );
            // obligatory
            queryPtr->bindValue(":username", pMemberPtr->m_username);
            queryPtr->bindValue(":name", pMemberPtr->m_name);
            queryPtr->bindValue(":surname1", pMemberPtr->m_surname1);
            queryPtr->bindValue(":surname2", pMemberPtr->m_surname2);
            queryPtr->bindValue(":lastmodified", pMemberPtr->m_lastModified);
            queryPtr->bindValue(":reg_date", pMemberPtr->m_regDate);
            queryPtr->bindValue(":active", pMemberPtr->m_active?1:0);
            queryPtr->bindValue(":isadmin", pMemberPtr->m_isAdmin?1:0);
            queryPtr->bindValue(":bank_account", pMemberPtr->m_bank_account);
            queryPtr->bindValue(":postal_send", pMemberPtr->m_postalSend?1:0);
            queryPtr->bindValue(":pwd", pMemberPtr->m_pwd);
            queryPtr->bindValue(":lastlogin", pMemberPtr->m_lastLogin);
            queryPtr->bindValue(":type", pMemberPtr->m_memberType);
            // optional
            if (pMemberPtr->m_imagePath.isEmpty()) {
                queryPtr->bindValue(":image", QVariant());
            } else {
                queryPtr->bindValue(":image", pMemberPtr->m_imagePath);
            }
            if (pMemberPtr->m_birthdate.isValid()) {
                queryPtr->bindValue(":birth", pMemberPtr->m_birthdate);
            } else {
                queryPtr->bindValue(":birth", QVariant());
            }
            if (pMemberPtr->m_address.isEmpty()) {
                queryPtr->bindValue(":address", QVariant());
            } else {
                queryPtr->bindValue(":address", pMemberPtr->m_address);
            }
            if (pMemberPtr->m_zipCode.isEmpty()) {
                queryPtr->bindValue(":zip_code", QVariant());
            } else {
                queryPtr->bindValue(":zip_code", pMemberPtr->m_zipCode);
            }
            if (pMemberPtr->m_town.isEmpty()) {
                queryPtr->bindValue(":town", QVariant());
            } else {
                queryPtr->bindValue(":town", pMemberPtr->m_town);
            }
            if (pMemberPtr->m_state.isEmpty()) {
                queryPtr->bindValue(":state", QVariant());
            } else {
                queryPtr->bindValue(":state", pMemberPtr->m_state);
            }
            if (pMemberPtr->m_phone.isEmpty()) {
                queryPtr->bindValue(":tel", QVariant());
            } else {
                queryPtr->bindValue(":tel", pMemberPtr->m_phone);
            }
            if (pMemberPtr->m_phone2.isEmpty()) {
                queryPtr->bindValue(":tel2", QVariant());
            } else {
                queryPtr->bindValue(":tel2", pMemberPtr->m_phone2);
            }
            if (pMemberPtr->m_email.isEmpty()) {
                queryPtr->bindValue(":email", QVariant());
            } else {
                queryPtr->bindValue(":email", pMemberPtr->m_email);
            }
            if (pMemberPtr->m_notes.isEmpty()) {
                queryPtr->bindValue(":notes", QVariant());
            } else {
                queryPtr->bindValue(":notes", pMemberPtr->m_notes);
            }
            if (pMemberPtr->m_idCard.isEmpty()) {
                queryPtr->bindValue(":id_card", QVariant());
            } else {
                queryPtr->bindValue(":id_card", pMemberPtr->m_idCard);
            }
            if (pMemberPtr->m_cardNumber.isEmpty()) {
                queryPtr->bindValue(":card", QVariant());
            } else {
                queryPtr->bindValue(":card", pMemberPtr->m_cardNumber);
            }
            return queryPtr;
        };

        Int32 memberId = -1;
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("createMember memberUsername %1").arg(pMemberPtr->m_username));
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };

            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                        QString("createMember could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                memberId = lastQueryResponse.query->value(0).toUInt();
            }
        }
        return memberId;
    }
    //
    bool DAO::changeMemberPassword(Int32 memberId, const QString &pwdHash, const QDateTime &lastmodified)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update member password
            queryPtr->prepare(
                    "UPDATE member "
                    "SET pwd=:pwd, lastmodified=:lastmodified "
                    "WHERE idmember = :memberid"
                    );
            queryPtr->bindValue(":pwd", pwdHash);
            queryPtr->bindValue(":lastmodified", lastmodified);
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("changeMemberPassword memberId %1").arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::changeMemberLastLogin(Int32 memberId, const QDateTime &lastlogin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update member lastlogin date
            queryPtr->prepare(
                    "UPDATE member "
                    "SET lastlogin=:lastlogin "
                    "WHERE idmember = :memberid"
                    );
            queryPtr->bindValue(":lastlogin", lastlogin);
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("changeMemberLastLogin memberId %1").arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    InvoiceResultPtr DAO::getLastInvoiceInfo()
    {
        InvoiceResultPtr pInvoiceResultPtr(new InvoiceResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Get last invoice (closed or open)
            queryPtr->prepare(
                    "SELECT idinvoice, state, date, total, idmember, last_modif FROM invoice "
                    "ORDER BY last_modif DESC "
                    "LIMIT 1"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, QString("getLastInvoiceInfo"));
            pInvoiceResultPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            InvoicePtr pInvoicePtr(new Invoice());
            pInvoicePtr->m_id = queryResponse.query->value(0).toInt();;
            pInvoicePtr->m_state = static_cast<InvoiceState>(queryResponse.query->value(1).toUInt());
            pInvoicePtr->m_date = queryResponse.query->value(2).toDateTime();
            pInvoicePtr->m_date.setTimeSpec(Qt::UTC);
            pInvoicePtr->m_total = queryResponse.query->value(3).toFloat();
            pInvoicePtr->m_memberId = queryResponse.query->value(4).toInt();
            pInvoicePtr->m_lastModified = queryResponse.query->value(5).toDateTime();
            pInvoicePtr->m_lastModified.setTimeSpec(Qt::UTC);
            pInvoiceResultPtr->m_pInvoice = pInvoicePtr;
        }

        return pInvoiceResultPtr;
    }
    //
    bool DAO::updateInvoiceLastModDate(Int32 invoiceId, const QDateTime &lastModDate)
    {
        // bind value
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update invoice's last modification date
            queryPtr->prepare(
                    "UPDATE invoice "
                    "SET last_modif=:lastmodified "
                    "WHERE idinvoice=:invoiceid"
                    );
            queryPtr->bindValue(":invoiceid", invoiceId);
            queryPtr->bindValue(":lastmodified", lastModDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("updateInvoiceLastModDate invoiceId %1").arg(invoiceId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::deleteInvoice(Int32 invoiceId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // remove invoice
            queryPtr->prepare(
                    "DELETE FROM invoice "
                    "WHERE idinvoice=:invoiceid"
                    );
            // bind value
            queryPtr->bindValue(":invoiceid", invoiceId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("deleteInvoice invoiceId %1").arg(invoiceId));
        }
        return !queryResponse.error;
    }
    //
    InvoiceListResultPtr DAO::getActiveInvoiceList()
    {
        // always return list object
        InvoiceListResultPtr pInvoiceListResultPtr(new InvoiceListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // active invoice list
            queryPtr->prepare(
                    "SELECT idinvoice, state, date, total, idmember, last_modif "
                    "FROM invoice "
                    "WHERE state = :state"
                    );
            queryPtr->bindValue(":state", static_cast<Int32>(InvoiceState::Open));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, QString("getActiveInvoiceList"));
            pInvoiceListResultPtr->m_error = 1;
        } else {
            pInvoiceListResultPtr->m_list = InvoiceListPtr(new InvoiceList);
            while (queryResponse.query->next()) {
                InvoicePtr pInvoicePtr = InvoicePtr(new Invoice());
                pInvoicePtr->m_id = queryResponse.query->value(0).toInt();
                pInvoicePtr->m_state = static_cast<InvoiceState>(queryResponse.query->value(1).toUInt());
                pInvoicePtr->m_date = queryResponse.query->value(2).toDateTime();
                pInvoicePtr->m_date.setTimeSpec(Qt::UTC);
                pInvoicePtr->m_total = queryResponse.query->value(3).toFloat();
                pInvoicePtr->m_memberId = queryResponse.query->value(4).toInt();
                pInvoicePtr->m_lastModified = queryResponse.query->value(5).toDateTime();
                pInvoicePtr->m_lastModified.setTimeSpec(Qt::UTC);
                pInvoiceListResultPtr->m_list->push_back(pInvoicePtr);
            }
        }

        return pInvoiceListResultPtr;
    }
    //
    BoolResult DAO::checkUsername(Int32 username)
    {
        BoolResult boolResult({0, false});

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // check username
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM member "
                    "WHERE username = :username"
                    );
            queryPtr->bindValue(":username", username);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("checkUsername username %1").arg(username));
            boolResult.error = 1;
        } else if (queryResponse.query->next()) {
            boolResult.result = queryResponse.query->value(0).toInt() != 0;
        } else {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("checkUsername username %1. Query does not return any result and should.").arg(username));
        }
        return boolResult;
    }
    //
    ProviderInvoiceResultPtr DAO::getProviderInvoiceById(const QString &providerInvoiceId)
    {
        ProviderInvoiceResultPtr pProviderInvoiceResultPtr(new ProviderInvoiceResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // get provider invoice by id
            queryPtr->prepare(
                    "SELECT provider_invoices.date, provider_invoices.total, provider.name, provider.image "
                    "FROM provider_invoices "
                    "INNER JOIN provider ON provider.idprovider = provider_invoices.idprovider "
                    "WHERE provider_invoices.idprovider_invoices = :providerinvoicesid"
                    );
            queryPtr->bindValue(":providerinvoicesid", providerInvoiceId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderInvoiceById providerInvoiceId %1").arg(providerInvoiceId));
            pProviderInvoiceResultPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            ProviderInvoicePtr pProviderInvoicePtr(new ProviderInvoice);
            Uint32 column = 0;
            pProviderInvoicePtr->m_id = providerInvoiceId;
            pProviderInvoicePtr->m_regDate = queryResponse.query->value(column++).toDate();
            pProviderInvoicePtr->m_total = queryResponse.query->value(column++).toFloat();
            pProviderInvoicePtr->m_providerName = queryResponse.query->value(column++).toString();
            pProviderInvoicePtr->m_providerImagePath = queryResponse.query->value(column++).toString();
            pProviderInvoiceResultPtr->m_pProviderInvoice = pProviderInvoicePtr;
        }
        return pProviderInvoiceResultPtr;
    }
    //
    ProviderInvoiceProductItemListResultPtr DAO::getProviderInvoiceProductsByInvoiceId(const QString &providerInvoiceId)
    {
        ProviderInvoiceProductItemListResultPtr pListResultPtr = ProviderInvoiceProductItemListResultPtr(new ProviderInvoiceProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // get provider invoice product by invoice id
            queryPtr->prepare(
                    "SELECT provider_invoices_product.product_item_idproduct_item, provider_invoices_product.count, product_item.name, product_item.name_es, product_item.image, product_item.price "
                    "FROM provider_invoices_product "
                    "INNER JOIN product_item ON product_item.idproduct_item = provider_invoices_product.product_item_idproduct_item "
                    "WHERE provider_invoices_product.provider_invoices_idprovider_invoices = :providerinvoicesid"
                    );
            // bind value
            queryPtr->bindValue(":providerinvoicesid", providerInvoiceId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb,
                    QString("getProviderInvoiceProductsByInvoiceId providerInvoiceId %1").arg(providerInvoiceId));
            pListResultPtr->m_error = 1;
        } else {
            pListResultPtr->m_list = ProviderInvoiceProductItemListPtr(new ProviderInvoiceProductItemList);
            while (queryResponse.query->next()) {
                ProviderInvoiceProductItemPtr pProductPtr(new ProviderInvoiceProductItem);
                Uint32 column = 0;
                pProductPtr->m_productId = queryResponse.query->value(column++).toInt();
                pProductPtr->m_count = queryResponse.query->value(column++).toInt();
                pProductPtr->m_productNameEus = queryResponse.query->value(column++).toString();
                pProductPtr->m_productNameEs = queryResponse.query->value(column++).toString();
                pProductPtr->m_productImagePath = queryResponse.query->value(column++).toString();
                pProductPtr->m_productPrice = queryResponse.query->value(column++).toFloat();
                pListResultPtr->m_list->push_back(pProductPtr);
            }
        }
        return pListResultPtr;
    }
    //
    Int32 DAO::getLastUsername()
    {
        Uint32 lastUsername = -1;
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Get last invoice (closed or open)
            queryPtr->prepare(
                    "SELECT username "
                    "FROM member "
                    "ORDER BY username DESC "
                    "LIMIT 1"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kSystemUserId, PenyaManager::LogAction::kDb, QString("getLastUsername"));
        } else if (queryResponse.query->next())
        {
            lastUsername = queryResponse.query->value(0).toInt();;
        }
        return lastUsername;
    }
    //
    QString DAO::getLastExecutedQuery(const QueryPtr& queryPtr)
    {
        QString str = queryPtr->lastQuery();
        QMapIterator<QString, QVariant> it(queryPtr->boundValues());
        while (it.hasNext())
        {
            it.next();
            str.replace(it.key(),it.value().toString());
        }
        return str;
    }
}

