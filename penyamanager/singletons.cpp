//

#include "singletons.h"

namespace PenyaManager {

//
// Initialization
//
DAO *Singletons::m_pDAO = 0;
MemberPtr Singletons::m_pCurrMember;
Services *Singletons::m_pServices = 0;
PartnerFinder *Singletons::m_pParnetFinder = 0;
Int32 Singletons::m_currentInvoiceId = 0;
Int32 Singletons::m_currentProductId = 0;

void Singletons::Create()
{
    // DAO Acces
    m_pDAO = new DAO("192.168.56.2", "alegria", "user", "user");
    //m_pDAO = new DAO("192.168.1.254", "alegria", "root", "Urko&Eguzki");
    m_pServices = new Services;
    m_pParnetFinder = new PartnerFinder;
}

void Singletons::Destroy()
{
    if (m_pDAO)
    {
        delete m_pDAO;
        m_pDAO = 0;
    }
    if (m_pServices)
    {
        delete m_pServices;
        m_pServices = 0;
    }
    if (m_pParnetFinder)
    {
        delete m_pParnetFinder;
        m_pParnetFinder = 0;
    }
}

}
