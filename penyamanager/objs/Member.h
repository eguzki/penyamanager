#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QDateTime>
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
            Member(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active);
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
            QDateTime           m_regDate;
            //
            QDateTime           m_lastModified;
    };

    //
    typedef std::shared_ptr<Member> MemberPtr;
}

#endif // MEMBER_H
