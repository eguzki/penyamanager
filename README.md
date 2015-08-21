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

# Howto install
* Network partition for resources
* Mysql driver install (TODO)
* Configure application settings using [configuration application](ConfApp.md)

# Features
* Member login window
  * Active, pwd check
* Member invoice window
  * unfinished invoice is loaded
* Member invoice confirmation window
  * invoices are always applied to account. No need to verify.
  * items count substracted from stock
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
* QT Creator 3.0.1
* QT 5.2.1
* GCC 4.8.4, 64 bit

## Translations
* Use lupdate to create/update Translation Sources (.ts)
  * lupdate -noobsolete penyamanager.pro penyamanageradmin.pro
  * translation sources are included in git (SCM) sourcecode manager
* Use **linguist** to make translations in translation sources
* Use lrelease to create translation binary (.qm)
  * at release time, do not include qm file in git
  * deploy .qm files in the same path as binary files
