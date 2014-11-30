#ifndef SINGLETONS_H
#define SINGLETONS_H

#include <QtSql>

class Singletons
{
    public:
        //
        static void Create();
        static void Destroy();

    public:
        static QSqlDatabase m_db;
};

#endif // SINGLETONS_H
