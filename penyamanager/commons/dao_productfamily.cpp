//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createProductFamilyItem familyName %1").arg(pFamilyPtr->m_nameEus));
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };
            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                        QString("createProductFamilyItem could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                familyId = lastQueryResponse.query->value(0).toUInt();
            }
        }

        return familyId;
    }
}
