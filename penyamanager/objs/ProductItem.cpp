//

#include <QString>

#include "ProductItem.h"

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
