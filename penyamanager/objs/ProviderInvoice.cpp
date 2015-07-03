//

#include "ProviderInvoice.h"

namespace PenyaManager
{
    //
    ProviderInvoice::ProviderInvoice()
    {
    }

    //
    ProviderInvoice::ProviderInvoice(QString id, Float total, const QDate &regDate, Int32 providerid)
        :
            m_id(id),
            m_total(total),
            m_regDate(regDate),
            m_providerid(providerid)
    {
    }
}
