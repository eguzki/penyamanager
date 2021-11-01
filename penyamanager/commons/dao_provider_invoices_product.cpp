//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createProviderInvoiceProduct providerInvoiceId %1 productId %2 count %3").arg(invoiceId).arg(productId).arg(count));
        }
        return !queryResponse.error;
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
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
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
}
