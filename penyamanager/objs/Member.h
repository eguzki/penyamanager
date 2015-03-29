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
            Member(Int32 id, const QString &name, const QString &surename, const QString &imagePath, bool active);
            //
            virtual ~Member(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_name;
            //
            QString             m_surename;
            //
            QString             m_imagePath;
            //
            Float               m_balance;
            //
            bool                m_active;
    };

    //
    typedef std::shared_ptr<Member> MemberPtr;
}

#endif // MEMBER_H
