//

#include "ProductFamily.h"

namespace PenyaManager
{
    //
    ProductFamily::ProductFamily()
    {
    }

    //
    ProductFamily::ProductFamily(const QString &name, const QString &imagePath, bool active)
        :
            m_name(name),
            m_imagePath(imagePath),
            m_active(active)
    {
    }
}
