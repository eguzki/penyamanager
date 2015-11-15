penyamanager
============

**penyamanager** project provides a cross-platform system to manage private membership oriented clubs.

# Highlights
* Member login window
* Member invoice window
* Member invoice confirmation window
* Member table reservation window
* Member oven reservation window
* Member fireplace reservation window
* Member deposit window
* Member account view
* Member invoice list window
* Admin login window
* Admin slow payers window
* Admin manage Invoices
* Admin manage Providers
* Admin manage Items
* Admin manage Account
* Admin manage Members
* Configuration Application

# Howto install. Windows deployment
* Network partition for resources
* Mysql driver install
  * Windows mysql plugin
    * Install mysql C connector.
    * Mysql connector arch (x64 or x86) must match compiler arch (x64 or x86)
    * Add to $PATH
* Configure application settings using [configuration application](ConfApp.md)

# Features
* Member login window
  * Active, pwd check
* Member invoice window
  * unfinished invoice is loaded
* Member invoice detail window
  * invoices are always applied to account. No need to verify.
  * items count substracted from stock
  * optionally can be printed
* Member table reservation window
  * members can cancel
  * members can only reserve one table in a given date (date, lunch/dinner)
* Member oven reservation window
  * members can cancel
  * members can only reserve one oven in a given date (date, lunch/dinner)
* Member fireplace reservation window
  * members can cancel
  * members can only reserve one fireplace in a given date (date, lunch/dinner)
* Member deposit window
  * Deposits are applied to balance on creation. Admin has to verify.
  * Deposit ticket is printed
* Member account view
* Member invoice list window
  * invoices can be clicked -> invoice details
* Admin login window
  * Active, admin, pwd check
* Admin slow payers window
  * export to csv
  * reset account
* Invoices
  * List of invoices by date range
    * invoices can be clicked -> invoice details
    * List of invoices by date range for a given member
* Providers
  * Provider List (name , list products).
    * New provider
  * create provider invoice
  * List of provider invoices (no need to give list of products, just invoice number)
    * filter by providerId
* Items
  * Stock management (list products)
    * export to csv
  * List product expenses in date range
    * for a given member optionally
  * Manage product/family
    * products can be created/edited. Price cannot be changed. To change price, inv_prid table should carry price.
    * families can be created/edited.
* Account
  * Verify deposits
    * when cash is unbalanced with total, create account transaction with type (3) DepositFix
  * Total account balance
    * deposits can be edited (????)
  * total deposits, total invoice
    * filter by memberId
* Members
  * Member List paginated
  * member Info (can be edited)
  * Member create
* Configuration Application
  * Resource path and ddbb access via configuration system platform independent. QSettings.
  * Database credentials encrypted using SimpleCrypt library
* Multilanguage
  * Basque
  * Spanish
* Activity logger

# Development

## Howto build
* Install QTCreator [IDE](https://qt-project.org/downloads)
* Clone source code from [here](https://github.com/eguzki/penyamanager)
* Update **crypt key** (15 digits [0-9]) before compilation
* From QTCreator import **penyamanageradmin.pro** file
* From QTCreator import **penyamanagerconf.pro** file
* From QTCreator import **penyamanager.pro** file
* Build: CTRL + SHIFT + B
* Run: CTRL + R

## Developed using:
* Vim 7.4 [customized](https://github.com/eguzki/eguzki-vim-environment)
* QT Creator 3.4.2
* QT 5.5.0
* GCC 4.8.4, 64 bit

## Package deployment for windows 7

### Windows 7 32/64 bits
* Compile using mingw 4.9.2 32bits compiler (currently QT 5.5 only supports mingw 4.9.2 32 bits but not 64 bits)
* Necessary elements:
  * Application main exe (penyamanager.exe)
  * Translation files (e.g. penyamanager_eu.qm). Check doc to know how to generate them out of source code.
  * QT and system shared libreries (dll's)
    * dll path: QT_PATH/5.5/mingw492_32/bin

```Shell
$ ls -R -l
.:
total 19444
-rwxrwxrwx 1 1026 users  119822 dic 21  2014 libgcc_s_dw2-1.dll
-rwxrwxrwx 1 1026 users 1026062 dic 21  2014 libstdc++-6.dll
-rwxrwxrwx 1 1026 users   49152 dic 21  2014 libwinpthread-1.dll
-rwxrwxrwx 1 1026 users      94 nov 15 18:56 penya.bat
-rwxrwxrwx 1 1026 users  599552 nov 15 14:23 penyamanager.exe
drwxrwxrwx 2 1026 users    4096 nov 15 20:04 platforms
-rwxrwxrwx 1 1026 users 5391360 nov 15 14:02 Qt5Core.dll
-rwxrwxrwx 1 1026 users 5334528 oct 12 21:31 Qt5Gui.dll
-rwxrwxrwx 1 1026 users  357888 oct 12 21:42 Qt5PrintSupport.dll
-rwxrwxrwx 1 1026 users  259072 oct 12 21:25 Qt5Sql.dll
-rwxrwxrwx 1 1026 users 6541824 oct 12 21:37 Qt5Widgets.dll

./platforms:
total 1384
-rwxrwxrwx 1 1026 users 1413632 oct 12 21:46 qwindows.dll
```

**penya.bat** file content:

```Shell
SET PATH=%cd%;%PATH%

SET QT_QPA_PLATFORM_PLUGIN_PATH=%cd%\platforms

%cd%\penyamanager.exe
```

## Translations
* Use lupdate to create/update Translation Sources (.ts)
  * lupdate -noobsolete penyamanager.pro penyamanageradmin.pro
  * translation sources are included in git (SCM) sourcecode manager
* Use **linguist** to make translations in translation sources
* Use lrelease to create translation binary (.qm)
  * at release time, do not include qm file in git
  * deploy .qm files in the same path as binary files

