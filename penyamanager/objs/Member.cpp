//

#include "Member.h"

namespace PenyaManager
{
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
}
