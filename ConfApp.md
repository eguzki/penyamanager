Configuration Application
-------------------------

Configure client application

* Database access
* Resource path
* Syslog server
* Debug mode (localhost file logging)
* Credit limit

By default, database connection parameters will be checked opening connection.
If database connection cannot be stablished, configuration will fail and exit. 

Parameter checking can be disabled with `--force` option.

# Usage

```
Usage: dist/penyamanagerconf [options]
penyamanager configuration application

Options:
  -h, --help                   Displays this help.
  -v, --version                Displays version information.
  -r, --path <resourcepath>    Resource path
  --host <host>                Database host. IP or hostname
  -n, --name <name>            Database name
  -u, --user <user>            Database username
  -p, --password <password>    Database password
  --syslog <syslog>            Syslog Server host. IP or hostname. Default
                               database host.
  --debug                      Debug mode
  --force                      Disable parameter checks
  --creditlimit <creditlimit>  Credit Limit. Default: -60.00 €
```

# example

```
$ penyamanagerconf -r "C:\\somepath\\somepath" --host 192.168.100.2 -n artzara -u someusername -p somepassword --syslog 192.168.1.2 --debug --creditlimit 1000
Successful
```
