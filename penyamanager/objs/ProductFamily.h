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
            virtual ~ProductFamily(){}

        public:
            //
            Int32               m_id;
            //
            QString             m_nameEus;
            //
            QString             m_nameEs;
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
            ProductFamilyPtr        m_family;
    };
    //
    typedef QSharedPointer<ProductFamilyResult> ProductFamilyResultPtr;
    //
    typedef std::vector<ProductFamilyPtr> ProductFamilyList;
    //
    typedef QSharedPointer<ProductFamilyList> ProductFamilyListPtr;
    //
    class ProductFamilyListResult
    {
        public:
            //
            ProductFamilyListResult();
            //
            virtual ~ProductFamilyListResult(){}

        public:
            //
            Int32                   m_error;
            //
            ProductFamilyListPtr    m_list;
    };
    //
    typedef QSharedPointer<ProductFamilyListResult> ProductFamilyListResultPtr;
}

#endif // PRODUCTFAMILY_H
