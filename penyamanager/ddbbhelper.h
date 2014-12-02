#ifndef DDBBHELPER_H
#define DDBBHELPER_H

#include <QtSql>

void initDb(QSqlDatabase &db);

class FamilyItemsSqlQueryModel: public QSqlQueryModel
{
    public:
        //
        virtual ~FamilyItemsSqlQueryModel() {}
        //
        QVariant data(const QModelIndex & item, int role = Qt::DisplayRole) const;
};

#endif // DDBBHELPER
