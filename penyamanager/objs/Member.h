#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
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
            MemberByAdmin(Int32 id, const QString &name, const QString &surname, const QString &image, const QDate &lastmodified, const QDate &reg_date, bool active, bool &isAdmin,
                          const QDate &birth, const QString &address, Int32 zip_code, const QString &town, const QString &state, Int32 tel, Int32 tel2, const QString &email,
                           const QString &bank_account, bool postal_send, const QString &notes);
            //MemberByAdmin(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active, const QString &bank_account);
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
            QString             m_image;
            //
            QDate               m_lastmodified;
            //
            QDate               m_reg_date;
            //
            bool                m_active;
            //
            bool                m_isAdmin;
            //
            QDate               m_birth;
            //
            QString             m_address;
            //
            Int32               m_zip_code;
            //
            QString             m_town;
            //
            QString             m_state;
            //
            Int32               m_tel;
            //
            Int32               m_tel2;
            //
            QString             m_email;
            //
            QString             m_bank_account;
            //
            bool               m_postal_send;
            //
            QString             m_notes;
            //
            Float               m_balance;
            //

    };

    typedef std::shared_ptr<MemberByAdmin> MemberByAdminPtr;
}

#endif // MEMBER_H
