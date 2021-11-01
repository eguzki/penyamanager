//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createProviderInvoice providerId %1").arg(pProviderInvoicePtr->m_id));
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
}
