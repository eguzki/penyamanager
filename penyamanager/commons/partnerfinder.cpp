//

#include <QDebug>

#include "partnerfinder.h"

namespace PenyaManager {
    //
    PartnerFinder::PartnerFinder()
    {
    }
    //
    PartnerFinder::~PartnerFinder()
    {
        m_partnerMap.clear();
    }
    //
    IPartner* PartnerFinder::getPartner(WindowKey partnerKey)
    {
        auto partner = m_partnerMap.find(partnerKey);
        if (partner == m_partnerMap.end()) {
            //this should never happen
            abort();
        }
        return partner->second;
    }
    //
    void PartnerFinder::addPartner(WindowKey partnerKey, IPartner *pIPartner)
    {
        m_partnerMap[partnerKey] = pIPartner;
    }
}
