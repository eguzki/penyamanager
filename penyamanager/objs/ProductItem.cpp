//

#include "ProductItem.h"

namespace PenyaManager
{
    //
    ProductItem::ProductItem()
    {
    }

    //
    ProductItem::ProductItem(const QString &name, const QString &imagePath, bool active, const QDateTime &regDate, Int32 familyId, Float price)
        :
            m_name(name),
            m_imagePath(imagePath),
            m_active(active),
            m_regDate(regDate),
            m_familyId(familyId),
            m_price(price)
    {
    }
}
