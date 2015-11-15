#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QSharedPointer>
#include <QDateTime>
#include <QDate>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    class Member
    {
        public:
            //
            Member();
            //
            virtual ~Member(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_name;
            //
            QString             m_surname;
            //
            QString             m_imagePath;
            //
            QDateTime           m_lastModified;
            //
            QDateTime           m_regDate;
            //
            bool                m_active;
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
    };

    //
    typedef QSharedPointer<Member> MemberPtr;
    //
    typedef std::vector<MemberPtr> MemberList;
    //
    typedef QSharedPointer<MemberList> MemberListPtr;

    //
    class MemberListStats
    {
        public:
            //
            MemberListStats();
            //
            virtual ~MemberListStats(){}

        public:
            //
            Uint32              m_totalMembers;
    };

    //
    typedef QSharedPointer<MemberListStats> MemberListStatsPtr;
}

#endif // MEMBER_H
