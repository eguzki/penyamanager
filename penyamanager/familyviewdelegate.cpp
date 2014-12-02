//

#include <QFont>
#include <QDebug>
#include <QApplication>
#include <QPainter>
#include "familyviewdelegate.h"

//
FamilyViewDelegate::FamilyViewDelegate()
{
}

//
FamilyViewDelegate::~FamilyViewDelegate()
{
}

//alocate each item size in listview.
QSize FamilyViewDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    //QSize result = QStyledItemDelegate::sizeHint(option, index);
    //return result;
    return(QSize(150+150, 100));
}

//
void FamilyViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "familyviewdelegate paint: [" << index.row() << ", " << index.column() << "]";
    qDebug() << "familyviewdelegate state: " << ((option.state & QStyle::State_Selected) > 0);
    qDebug() << "familyviewdelegate valid index: " << index.isValid();
    QStyledItemDelegate::paint(painter,option,index);

    painter->save();

    QString familyName = index.model()->data(index.model()->index(index.row(), 1)).toString();
    qDebug() << "familyviewdelegate name: " << familyName;
    QString imagePath = index.model()->data(index.model()->index(index.row(), 2)).toString();
    qDebug() << "familyviewdelegate: " << imagePath;

    QFont font = QApplication::font();
    font.setBold(true);
    QFontMetrics fm(font);
    QRect imageRect = option.rect;
    QRect textRect = option.rect;

    QPixmap pixmap(imagePath.prepend("/home/eguzki/tmp/"));

    // scale image to 150x100
    QPixmap resizedPixmap = pixmap.scaled(QSize(145, 95), Qt::KeepAspectRatio);

    imageRect.setRight(resizedPixmap.width());
    imageRect.setBottom(resizedPixmap.height());
    textRect.setLeft(imageRect.right() + 5);
    textRect.setBottom(resizedPixmap.height());
    textRect.setTop(imageRect.top() + 10);

    painter->drawPixmap(imageRect, resizedPixmap);

    painter->setFont(font);
    painter->drawText(textRect, familyName);

    painter->restore();
}
