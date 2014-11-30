#include <iostream>
#include "ddbbhelper.h"

void initDb(QSqlDatabase& db){
    db.setHostName("192.168.56.2");
    db.setDatabaseName("alegria");
    db.setUserName("user");
    db.setPassword("user");
    db.open();
}
