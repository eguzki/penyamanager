#ifndef PROVIDER_H
#define PROVIDER_H

#include <QString>
#include <QDateTime>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    class Provider
    {
        public:
            //
            Provider();
            //
            Provider(Int32 id, const QString &name, const QString &image, const QDateTime &regDate, const QString &phone);
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
            QDateTime           m_regDate;
            //
            QString             m_phone;
    };

    //
    typedef std::shared_ptr<Provider> ProviderPtr;
    //
    typedef std::vector<ProviderPtr> ProviderList;
    //
    typedef std::shared_ptr<ProviderList> ProviderListPtr;
}

#endif // PROVIDER_H