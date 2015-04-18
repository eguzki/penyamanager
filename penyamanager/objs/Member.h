#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
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
            Member(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active, const QString &bank_account);
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
            Float               m_balance;
            //
            bool                m_active;
            //
            QString             m_bank_account;

    };

    //
    typedef std::shared_ptr<Member> MemberPtr;

    class MemberByAdmin
    {
        public:
            //
            MemberByAdmin();
            //
            MemberByAdmin(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active, const QString &bank_account);
            //
            virtual ~MemberByAdmin(){}

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
            Float               m_balance;
            //
            bool                m_active;
            //
            QString             m_bank_account;

    };

    typedef std::shared_ptr<MemberByAdmin> MemberByAdminPtr;
}

#endif // MEMBER_H
