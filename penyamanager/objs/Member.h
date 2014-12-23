#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <DataTypes.h>
#include "Invoice.h"

namespace PenyaManager
{
    //
    class Member
    {
        public:
            //
            Member();
            //
            Member(Int32 id, const QString &name, const QString &surename, const QString &imagePath, InvoicePtr currInvoice);
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
            InvoicePtr          m_currInvoce;
            //
            Float               m_balance;
    };

    //
    typedef std::shared_ptr<Member> MemberPtr;
}

#endif // MEMBER_H
