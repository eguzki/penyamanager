#include "ddbbhelper.h"

void initDb(QSqlDatabase& db){
    db.setHostName("192.168.56.2");
    db.setDatabaseName("alegria");
    db.setUserName("user");
    db.setPassword("user");
    db.open();
}

//
QVariant FamilyItemsSqlQueryModel::data(const QModelIndex & item, int role) const
{
    qDebug() << "data[role]: " << role;
    qDebug() << "data: [" << item.row() << ", " << item.column() << "]";
    if (role == Qt::DecorationRole)
    {
        qDebug() << "data: DecorationRole: column:" << item.column();
        QString imagePath = record(item.row()).value(2).toString(); // column 2 contains image data
        QPixmap pixmap(imagePath.prepend("/home/eguzki/tmp/"));
        return pixmap.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else if (role == Qt::DisplayRole) {
        qDebug() << "data: DisplayRole: column:" << item.column();
        return record(item.row()).value(1).toString();
    }
    return QSqlQueryModel::data(item, role);
}
