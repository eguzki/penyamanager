//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
    ProductItemListResultPtr DAO::getProductsFromProvider(Int32 providerId)
    {
        ProductItemListResultPtr pIListResultPtr(new ProductItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // ProductItems by provider
            queryPtr->prepare("SELECT idproduct_item, name, name_es, image, reg_date, "
                    "idproduct_family, price "
                    "FROM product_item "
                    "WHERE active=:activemember AND idprovider=:providerId");
            // bind value
            queryPtr->bindValue(":activemember", Member::ACTIVE);
            queryPtr->bindValue(":providerId", providerId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, QString("getAllStockProductsList"));
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createProductItem productItemName %1").arg(pProductPtr->m_nameEus));
            return -1;
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };

            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createProductItem could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                itemId = lastQueryResponse.query->value(0).toUInt();
            }
        }

        return itemId;
    }
}
