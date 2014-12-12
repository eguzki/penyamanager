//

#include "singletons.h"

namespace PenyaManager {

DAO *Singletons::m_pDAO = 0;

void Singletons::Create() {
    // DAO Acces
    m_pDAO = new DAO("192.168.56.2", "alegria", "user", "user");
}

void Singletons::Destroy() {
    if (m_pDAO)
    {
        delete m_pDAO;
        m_pDAO = 0;
    }
}

}
