//

#include "Provider.h"

namespace PenyaManager
{
    //
    Provider::Provider()
    {
    }

    //
    Provider::Provider(Int32 id, const QString &name, const QString &image, const QDate &regDate, const QString &phone)
        :
            m_id(id),
            m_name(name),
            m_image(image),
            m_regDate(regDate),
            m_phone(phone)
    {
    }
    //
    ProviderListResult::ProviderListResult()
        :
            m_error(0)
    {}
    //
    ProviderResult::ProviderResult()
        :
            m_error(0)
    {}
}
