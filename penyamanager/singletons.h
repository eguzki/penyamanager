#ifndef SINGLETONS_H
#define SINGLETONS_H

#include "objs/Member.h"
#include "services.h"
#include "partnerfinder.h"
#include "dao.h"

namespace PenyaManager {

class Singletons
{
    public:
        //
        static void Create();
        //
        static void Destroy();

    public:
        //
        static DAO              *m_pDAO;
        //
        static MemberPtr        m_pCurrMember;
        //
        static Services         *m_pServices;
        //
        static PartnerFinder    *m_pParnetFinder;
        //
        static Int32            m_currentInvoiceId;
        //
        static Int32            m_currentProductId;
};

}

#endif // SINGLETONS_H
