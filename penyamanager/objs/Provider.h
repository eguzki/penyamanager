#ifndef PROVIDER_H
#define PROVIDER_H

#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    class Provider
    {
        public:
            //
            Provider();
            //
            Provider(Int32 id, const QString &name, const QString &image, const QDate &regDate, const QString &phone);
            //
            virtual ~Provider(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_name;
            //
            QString             m_image;
            //
            QDate               m_regDate;
            //
            QString             m_phone;
            //
            QString             m_notes;
    };

    //
    typedef QSharedPointer<Provider> ProviderPtr;
    //
    class ProviderResult
    {
        public:
            //
            ProviderResult();
            //
            virtual ~ProviderResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProviderPtr             m_provider;
    };
    //
    typedef QSharedPointer<ProviderResult> ProviderResultPtr;
    //
    typedef std::vector<ProviderPtr> ProviderList;
    //
    typedef QSharedPointer<ProviderList> ProviderListPtr;
    //
    class ProviderListResult
    {
        public:
            //
            ProviderListResult();
            //
            virtual ~ProviderListResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProviderListPtr         m_list;
    };
    //
    typedef QSharedPointer<ProviderListResult> ProviderListResultPtr;
}

#endif // PROVIDER_H
