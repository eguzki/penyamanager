#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QSharedPointer>
#include <QDateTime>
#include <QDate>
#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    QString GetStringFromMemberType(Uint32 memberType);
    //
    class Member
    {
        public:
            // Member Type
            //
            static const Uint32 NORMAL;
            //
            static const Uint32 RETIRED;
            //
            static const Uint32 HONORARY;
            //
            static const Uint32 YOUNG;
            //
            static const Uint32 KID;

            // Member State
            //
            static const int INACTIVE;
            //
            static const int ACTIVE;
            //
            static const int DROPPED;
            //
            static const int DEAD;
            //
            Member();
            //
            virtual ~Member(){}
            //
            bool IsActive();
            //
            bool IsInactivityExpired();
            //
            QDate ExpirationDate();
            //
            QDate Turn19Date();

        public:
            //
            Int32               m_id;
            //
            Int32               m_username;
            //
            QString             m_name;
            //
            QString             m_surname1;
            //
            QString             m_surname2;
            //
            QString             m_imagePath;
            //
            QDateTime           m_lastModified;
            //
            QDateTime           m_regDate;
            //
            int                 m_active;
            //
            bool                m_isAdmin;
            //
            QDate               m_birthdate;
            //
            QString             m_address;
            //
            QString             m_zipCode;
            //
            QString             m_town;
            //
            QString             m_state;
            //
            QString             m_phone;
            //
            QString             m_phone2;
            //
            QString             m_email;
            //
            QString             m_bank_account;
            //
            bool                m_postalSend;
            //
            QString             m_notes;
            //
            QString             m_pwd;
            //
            QDateTime           m_lastLogin;
            //
            Float               m_balance;
            //
            QString             m_idCard;
            //
            QString             m_cardNumber;
            //
            Uint32              m_memberType;
            //
            QDate               m_inactiveStartDate;
            //
            QDate               m_inactiveModificationDate;
    };

    //
    typedef QSharedPointer<Member> MemberPtr;
    //
    MemberPtr GetInvalidMember();

    //
    class MemberResult
    {
        public:
            //
            MemberResult();
            //
            virtual ~MemberResult(){}

        public:
            //
            Int32              m_error;
            //
            MemberPtr          m_member;
    };
    //
    typedef QSharedPointer<MemberResult> MemberResultPtr;

    //
    typedef std::vector<MemberPtr> MemberList;
    //
    typedef QSharedPointer<MemberList> MemberListPtr;
    //
    class MemberListResult
    {
        public:
            //
            MemberListResult();
            //
            virtual ~MemberListResult(){}

        public:
            //
            Int32              m_error;
            //
            MemberListPtr      m_list;
    };
    //
    typedef QSharedPointer<MemberListResult> MemberListResultPtr;

    //
    class MemberListStats
    {
        public:
            //
            MemberListStats();
            //
            MemberListStats(Uint32 totalMembers);
            //
            virtual ~MemberListStats(){}

        public:
            //
            Uint32              m_totalMembers;
    };

    //
    typedef QSharedPointer<MemberListStats> MemberListStatsPtr;
    //
    class MemberListStatsResult
    {
        public:
            //
            MemberListStatsResult();
            //
            virtual ~MemberListStatsResult(){}

        public:
            //
            Int32              m_error;
            //
            MemberListStatsPtr m_stats;
    };
    //
    typedef QSharedPointer<MemberListStatsResult> MemberListStatsResultPtr;
}

#endif // MEMBER_H
