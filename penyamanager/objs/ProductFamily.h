#ifndef PRODUCTFAMILY_H
#define PRODUCTFAMILY_H

#include <QString>
#include <QDateTime>
#include <QSharedPointer>

#include <commons/DataTypes.h>

namespace PenyaManager
{
    //
    class ProductFamily
    {
        public:
            //
            ProductFamily();
            //
            ProductFamily(const QString &name, const QString &imagePath, bool active, const QDateTime &regDate);
            //
            virtual ~ProductFamily(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_name;
            //
            QString             m_imagePath;
            //
            bool                m_active;
            //
            QDateTime           m_regDate;
    };

    //
    typedef QSharedPointer<ProductFamily> ProductFamilyPtr;
    //
    typedef std::vector<ProductFamilyPtr> ProductFamilyList;
    //
    typedef QSharedPointer<ProductFamilyList> ProductFamilyListPtr;
    //
    class ProductFamilyResult
    {
        public:
            //
            ProductFamilyResult();
            //
            virtual ~ProductFamilyResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProductFamilyListPtr    m_list;
    };
    //
    typedef QSharedPointer<ProductFamilyResult> ProductFamilyResultPtr;
}

#endif // PRODUCTFAMILY_H
