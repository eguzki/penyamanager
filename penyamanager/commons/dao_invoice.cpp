//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createInvoice could not get last ID created in db"));
            pInvoiceResultPtr->m_error = 1;
        } else if (lastQueryResponse.query->next()) {
            pInvoiceResultPtr->m_pInvoice->m_id = lastQueryResponse.query->value(0).toUInt();
        }
        return pInvoiceResultPtr;
    }
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("updateInvoice invoiceId %1").arg(pInvoicePtr->m_id));
        }
        return !queryResponse.error;
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, QString("getLastInvoiceInfo"));
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, QString("getActiveInvoiceList"));
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
}
