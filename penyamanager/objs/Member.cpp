//

#include "Member.h"

namespace PenyaManager
{
    //
    Member::Member()
    {
    }
    //
    Member::Member(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active, const QString &bank_account)
        :
            m_id(id),
            m_name(name),
            m_surname(surname),
            m_imagePath(imagePath),
            m_balance(0.0),
            m_active(active),
            m_bank_account(bank_account)
    {
    }
    MemberByAdmin::MemberByAdmin()
    {
    }
    //
    MemberByAdmin::MemberByAdmin(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active, const QString &bank_account)
        :
            m_id(id),
            m_name(name),
            m_surname(surname),
            m_imagePath(imagePath),
            m_balance(0.0),
            m_active(active),
            m_bank_account(bank_account)
    {
    }
}
