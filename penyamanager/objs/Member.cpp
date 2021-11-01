//

#include <QObject>
#include <QDate>

#include <commons/constants.h>
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
    const Uint32 Member::YOUNG = 3;
    //
    const int Member::INACTIVE = 0;
    //
    const int Member::ACTIVE = 1;
    //
    const int Member::DROPPED = 2;
    //
    const int Member::DEAD = 3;
    //
    Member::Member()
    {}
    //
    bool Member::IsActive()
    {
        return m_active == ACTIVE;
    }
    //
    bool Member::IsInactivityExpired()
    {
        if (!ExpirationDate().isValid()){
            return false;
        }
        return ExpirationDate() <= QDate::currentDate();
    }
    //
    QDate Member::ExpirationDate()
    {
        if (!m_inactiveModificationDate.isValid()){
            return QDate();
        }

        return m_inactiveModificationDate.addMonths(Constants::kAdminInactivityPeriodMonths);
    }
    //
    QDate Member::Turn19Date()
    {
        if (!m_birthdate.isValid()) {
            return QDate();
        }

        return m_birthdate.addYears(19);
    }
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
            case Member::YOUNG: return QObject::tr("Young");
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
