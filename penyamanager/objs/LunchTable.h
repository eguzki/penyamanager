#ifndef LUNCHTABLE_H
#define LUNCHTABLE_H

#include <QString>
#include <QDateTime>
#include <DataTypes.h>

namespace PenyaManager
{
    //
    class LunchTable
    {
        public:
            //
            LunchTable();
            //
            LunchTable(Int32 idTable, const QString &tableName, Uint16 guestNum);
            //
            virtual ~LunchTable(){}

        public:
            //
            Int32               m_idTable;
            //
            QString             m_tableName;
            //
            Uint16              m_guestNum;
    };

    //
    typedef std::shared_ptr<LunchTable> LunchTablePtr;
    //
    typedef std::vector<LunchTablePtr> LunchTableList;
    //
    typedef std::shared_ptr<LunchTableList> LunchTableListPtr;
}

#endif // LUNCHTABLE_H
