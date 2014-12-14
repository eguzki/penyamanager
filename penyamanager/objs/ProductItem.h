#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <DataTypes.h>

//
class ProductItem
{
    public:
        //
        ProductItem();
        //
        ProductItem(const QString &name, const QString &imagePath);
        //
        virtual ~ProductItem(){}

    public:
        //
        Int32               m_id;
        //
        QString             m_name;
        //
        QString             m_imagePath;
};

//
typedef std::shared_ptr<ProductItem> ProductItemPtr;
//
typedef std::vector<ProductItemPtr> ProductItemList;
//
typedef std::shared_ptr<ProductItemList> ProductItemListPtr;

#endif // PRODUCTITEM_H
