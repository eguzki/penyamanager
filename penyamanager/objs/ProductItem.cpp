//

#include <QString>

#include "ProductItem.h"

namespace PenyaManager
{
    //
    ProductItem::ProductItem()
    {
    }

    //
    ProductItem::ProductItem(const QString &name, const QString &imagePath)
        :
            m_name(name),
            m_imagePath(imagePath)
    {
    }
}
