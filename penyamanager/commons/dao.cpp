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
                Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, m_db.lastError().text());
                return queryResponse;
            }
        }
        queryResponse.query = queryFactory();
        // log query only when debug. Generating query string may be expensive.
        if (Singletons::m_pSettings->value(Constants::kDebugConfig).toString() == "1")
        {
            Singletons::m_pLogger->Debug(Constants::kNoUserId, PenyaManager::LogAction::kDb, getLastExecutedQuery(queryResponse.query));
        }
        queryResponse.error = !queryResponse.query->exec();
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, queryResponse.query->lastError().text());
            // in case error can not be recovered, return null
            queryResponse.query.reset();
            // try to handle server timeout connection closes by inactivity
            // QSqlError(2006, "QMYSQL: Unable to execute query", "MySQL server has gone away")
            m_db.close();
            queryResponse.error = !m_db.open();
            if (!queryResponse.error) {
                // when database connection is opened, query has to be re-initialized
                queryResponse.query = queryFactory();
                queryResponse.error = !queryResponse.query->exec();
                if (queryResponse.error) {
                    qDebug() << queryResponse.query->lastError();
                    Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, queryResponse.query->lastError().text());
                    // in case error can not be recovered, return null
                    queryResponse.query.reset();
                }
            } else {
                // database open error
                Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, m_db.lastError().text());
            }
        }
        return queryResponse;
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
