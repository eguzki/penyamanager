//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("increaseProductInvoice invoice %1 product %2 count %3").arg(invoiceId).arg(productId).arg(count));
        } else {
            numRowsAffected = queryResponse.query->numRowsAffected();
        }
        return numRowsAffected;
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
}
