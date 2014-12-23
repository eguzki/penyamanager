//

#include "services.h"
#include "singletons.h"

namespace PenyaManager {

    //
    Services::Services()
    {
    }
    //
    Services::~Services()
    {
    }
    //
    MemberPtr Services::getMemberbyName(const QString &memberName) const
    {
        MemberPtr pMemberPtr = Singletons::m_pDAO->getMemberbyName(memberName);

        if (!pMemberPtr)
        {
            return MemberPtr();
        }

        // member's balance 
        Float balance = Singletons::m_pDAO->getMemberBalance(pMemberPtr->m_id);
        pMemberPtr->m_balance = balance;

        return pMemberPtr;
    }
}
