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
    MemberByAdmin::MemberByAdmin(Int32 id, const QString &name, const QString &surname, const QString &image, const QDate &lastmodified, const QDate &reg_date,
                                 bool active, bool &isAdmin, const QDate &birth, const QString &address, Int32 zip_code, const QString &town, const QString &state,
                                 Int32 tel, Int32 tel2, const QString &email, const QString &bank_account, bool postal_send, const QString &notes)
        :

    //MemberByAdmin::MemberByAdmin(Int32 id, const QString &name, const QString &surname, const QString &imagePath, bool active, const QString &bank_account)
    //          :
            m_id(id),
            m_name(name),
            m_surname(surname),
            m_image(image),
            m_lastmodified(lastmodified),
            m_reg_date(reg_date),
            m_active(active),
            m_isAdmin(isAdmin),
            m_birth(birth),
            m_address(address),
            m_zip_code(zip_code),
            m_town(town),
            m_state(state),
            m_tel(tel),
            m_tel2(tel2),
            m_email(email),
            m_bank_account(bank_account),
            m_postal_send(postal_send),
            m_notes(notes),
            m_balance(0.0)


    {
    }
}
