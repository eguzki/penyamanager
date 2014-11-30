#include <iostream>

#include "ddbbhelper.h"
#include "singletons.h"

QSqlDatabase    Singletons::m_db = QSqlDatabase::addDatabase("QMYSQL");

void Singletons::Create() {
    initDb(m_db);
}

void Singletons::Destroy() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}
