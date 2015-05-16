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
        for (auto iter = m_partnerMap.begin(), end = m_partnerMap.end(); iter != end; ++iter)
        {
            delete iter->second;
        }
        m_partnerMap.clear();
    }
    //
    IPartner* PartnerFinder::getPartner(Uint32 partnerKey)
    {
        auto partner = m_partnerMap.find(partnerKey);
        if (partner == m_partnerMap.end()) {
            //this should never happen
            abort();
        }
        return partner->second;
    }
    //
    void PartnerFinder::addPartner(Uint32 partnerKey, IPartner *pIPartner)
    {
        m_partnerMap[partnerKey] = pIPartner;
    }
}
