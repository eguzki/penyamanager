//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("updateProvider providerId %1").arg(pProviderPtr->m_id));
        }
        return !queryResponse.error;
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createProvider name %1 image %2 phone %3").arg(pProviderPtr->m_name).arg(pProviderPtr->m_image).arg(pProviderPtr->m_phone));
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };

            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                        QString("createProvider could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                providerId = lastQueryResponse.query->value(0).toUInt();
            }
        }
        return providerId;
    }
}
