#ifndef PRODUCTFAMILY_H
#define PRODUCTFAMILY_H

#include <QString>

#include <DataTypes.h>

namespace PenyaManager
{
    //
    class ProductFamily
    {
        public:
            //
            ProductFamily();
            //
            ProductFamily(const QString &name, const QString &imagePath, bool active);
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
    };

    //
    typedef std::shared_ptr<ProductFamily> ProductFamilyPtr;
    //
    typedef std::vector<ProductFamilyPtr> ProductFamilyList;
    //
    typedef std::shared_ptr<ProductFamilyList> ProductFamilyListPtr;
}

#endif // PRODUCTFAMILY_H
