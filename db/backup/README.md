Database backups
================

Database backup user
-------------------
Assign the following global rights :

* Select
* Reload
* Show Databases
* Lock Tables

Params to configure
-------------------
* ROOTDIR
* DB_USER
* DB_PASSWORD

Cron jobs
---------
* @daily @5AM
```
0 5 * * * root /volume1/backup/daily_db_backup &>/dev/null || /usr/syno/bin/synologset1 sys err 0x11100000 "[BACKUP] could not create daily backup"
```
* @monthly @5AM on 1st day of the month
```
0 5 1 * * root /volume1/backup/monthly_db_backup &>/dev/null || /usr/syno/bin/synologset1 sys err 0x11100000 "[BACKUP] could not create monthly backup"
```

* @yearly @5AM on 1st day of the Feb
```
0 5 1 2 * root /volume1/backup/yearly_db_backup &>/dev/null || /usr/syno/bin/synologset1 sys err 0x11100000 "[BACKUP] could not create yearly backup"
```

Restoring DB
------------
```
mysql -u${user} -p${pass} < backup.sql
```
