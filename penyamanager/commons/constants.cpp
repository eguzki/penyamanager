//

#include <QString>
#include "constants.h"

namespace PenyaManager {
    //
    const QString   Constants::kOrganizationName                = "penyamanager";
    //
    const QString   Constants::kApplicationName                 = "alegria";
    //
    const QString   Constants::kResourcePathKey                 = "resourcepath";
    //
    const QString   Constants::kDatabaseGroupName               = "ddbb";
    //
    const QString   Constants::kDatabaseHost                    = "host";
    //
    const QString   Constants::kLogLevel                        = "loglevel";
    //
    const QString   Constants::kDatabaseName                    = "name";
    //
    const QString   Constants::kDatabaseUser                    = "user";
    //
    const QString   Constants::kDatabasePass                    = "pass";
    //
    const Uint32    Constants::kFamilyWidgetWidth               = 80;
    //
    const Uint32    Constants::kFamilyImageWidth                = 40;
    //
    const Uint32    Constants::kFamilyImageHeigth               = 40;
    //
    const Int32     Constants::kIdRole                          = 101;
    //
    const Uint32    Constants::kMemberImageWidth                = 80;
    //
    const Uint32    Constants::kMemberImageHeigth               = 80;
    //
    const Uint32    Constants::kInvoiceListPageCount            = 10;
    //
    const Uint32    Constants::kAccountListPageCount            = 10;
    //
    const Uint32    Constants::kProductListPageCount            = 25;
    // Put your own key here
    // Must be changed on compile time
    const quint64   Constants::kCryptKey                        = Q_UINT64_C(932833457959459);
    //
    const Uint16    Constants::kNumLangs                        = 2;
    // 1M
    const quint64   Constants::kLogMaxSizeBytes                 = 1048576;
    // 
    const Uint32    Constants::kOpenInvoiceTimeoutH             = 12;
    //
    const Float     Constants::kCreditLimit                     = 100;
}

