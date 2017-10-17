//

#include "ProductFamily.h"

namespace PenyaManager
{
    //
    ProductFamily::ProductFamily()
    {
    }

    //
    ProductFamily::ProductFamily(const QString &name, const QString &imagePath, bool active, const QDateTime &regDate)
        :
            m_name(name),
            m_imagePath(imagePath),
            m_active(active),
            m_regDate(regDate)
    {
    }

    //
    ProductFamilyResult::ProductFamilyResult()
        :
            m_error(0)
    {
    }
    //
    ProductFamilyListResult::ProductFamilyListResult()
        :
            m_error(0)
    {
    }
}
