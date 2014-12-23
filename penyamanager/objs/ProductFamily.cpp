//

#include <QString>

#include "ProductFamily.h"

namespace PenyaManager
{
    //
    ProductFamily::ProductFamily()
    {
    }

    //
    ProductFamily::ProductFamily(const QString &name, const QString &imagePath)
        :
            m_name(name),
            m_imagePath(imagePath)
    {
    }
}
