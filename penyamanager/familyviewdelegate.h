#ifndef FAMILYVIEWDELEGATE_H
#define FAMILYVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

//
class FamilyViewDelegate : public QStyledItemDelegate{
    public:
        //
        FamilyViewDelegate();
        
        //
        virtual ~FamilyViewDelegate();

        //
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

        //
        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // FAMILYVIEWDELEGATE_H
