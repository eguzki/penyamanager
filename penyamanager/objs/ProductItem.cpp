//

#include "ProductItem.h"

namespace PenyaManager
{
    //
    ProductItem::ProductItem()
    {
    }

    //
    ProductItem::ProductItem(const QString &name, const QString &imagePath, bool active, const QDateTime &regDate, Int32 familyId, Float price, Int32 providerId, Int32 stock)
        :
            m_name(name),
            m_imagePath(imagePath),
            m_active(active),
            m_regDate(regDate),
            m_familyId(familyId),
            m_price(price),
            m_providerId(providerId),
            m_stock(stock)
    {
    }
    //
    ProductListStats::ProductListStats()
    {
    }
    //
    ProductListStats::ProductListStats(Uint32 totalNumProducts)
        :
            m_totalNumProducts(totalNumProducts)
    {
    }
    //
    ProductItemResult::ProductItemResult()
        :
            m_error(0)
    {
    }
}
