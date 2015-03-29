//

#include "Member.h"

namespace PenyaManager
{
    //
    Member::Member()
    {
    }
    //
    Member::Member(Int32 id, const QString &name, const QString &surename, const QString &imagePath, bool active)
        :
            m_id(id),
            m_name(name),
            m_surename(surename),
            m_imagePath(imagePath),
            m_balance(0.0),
            m_active(active)
    {
    }
}
