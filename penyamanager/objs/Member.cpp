//

#include "Member.h"

namespace PenyaManager
{
    //
    Member::Member()
    {
    }
    //
    Member::Member(Int32 id, const QString &name, const QString &surename, const QString &imagePath, InvoicePtr currInvoice)
        :
            m_id(id),
            m_name(name),
            m_surename(surename),
            m_imagePath(imagePath),
            m_currInvoce(currInvoice),
            m_balance(0.0)
    {
    }
}
