//

#include <QObject>

#include "Member.h"

namespace PenyaManager
{
    //
    const Uint32 Member::NORMAL = 0;
    //
    const Uint32 Member::RETIRED = 1;
    //
    const Uint32 Member::HONORARY = 2;
    //
    Member::Member()
    {}
    //
    MemberListStats::MemberListStats()
    {}
    //
    MemberListStats::MemberListStats(Uint32 totalMembers)
        :
            m_totalMembers(totalMembers)
    {}
    //
    MemberResult::MemberResult()
        :
            m_error(0)
    {}
    //
    MemberListResult::MemberListResult()
        :
            m_error(0)
    {}
    //
    MemberListStatsResult::MemberListStatsResult()
        :
            m_error(0)
    {}
    //
    QString GetStringFromMemberType(Uint32 memberType)
    {
        switch (memberType)
        {
            case Member::NORMAL: return QObject::tr("Normal");
            case Member::RETIRED: return QObject::tr("Retired");
            case Member::HONORARY: return QObject::tr("Honorary");
        }
        return "-";
    }
    //
    MemberPtr GetInvalidMember()
    {
        MemberPtr pMemberPtr(new Member);
        // negative ids are not allowed
        pMemberPtr->m_id = -1;
        return pMemberPtr;
    }
}
