//

#include "singletons.h"

namespace PenyaManager {

//
// Initialization
//
DAO *Singletons::m_pDAO = 0;
MemberPtr Singletons::m_pCurrMember;
Services *Singletons::m_pServices = 0;

void Singletons::Create() 
{
    // DAO Acces
    //m_pDAO = new DAO("192.168.56.2", "alegria", "user", "user");
    m_pDAO = new DAO("192.168.1.254", "alegriaurko", "root", "Urko&Eguzki");
    m_pServices = new Services;
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
}

}
