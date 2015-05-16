//

#include "LunchTable.h"

namespace PenyaManager
{
    //
    LunchTable::LunchTable()
    {
    }

    //
    LunchTable::LunchTable(Int32 idTable, const QString &tableName, Uint16 guestNum)
        :
            m_idTable(idTable),
            m_tableName(tableName),
            m_guestNum(guestNum)
    {
    }
}
