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
    const QString   Constants::kSyslogServer                    = "syslogserver";
    //
    const QString   Constants::kDebugConfig                     = "debug";
    //
    const QString   Constants::kDatabaseName                    = "name";
    //
    const QString   Constants::kDatabaseUser                    = "user";
    //
    const QString   Constants::kDatabasePass                    = "pass";
    //
    const Uint32    Constants::kFamilyWidgetWidth               = 80;
    //
    const Uint32    Constants::kFamilyImageWidth                = 60;
    //
    const Uint32    Constants::kFamilyImageHeigth               = 60;
    //
    const Int32     Constants::kIdRole                          = 101;
    //
    const Uint32    Constants::kMemberImageWidth                = 80;
    //
    const Uint32    Constants::kMemberImageHeigth               = 80;
    //
    const Uint32    Constants::kInvoiceListPageCount            = 14;
    //
    const Uint32    Constants::kAdminInvoiceListPageCount       = 15;
    //
    const Uint32    Constants::kAccountListPageCount            = 15;
    //
    const Uint32    Constants::kAdminAccountListPageCount       = 15;
    //
    const Uint32    Constants::kAdminProductListPageCount       = 25;
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
    const Float     Constants::kCreditLimit                     = -60;
    //
    const Uint32    Constants::kDashboardProductListPageCount   = 17;
    //
    const Uint32    Constants::kLoginWindowProductListPageCount = 6;
    //
    const Uint32    Constants::kInvoiceWindowProductListPageCount = 14;
    //
    const Uint32    Constants::kInvoiceDetailsWindowProductListPageCount = 17;
    //
    const Uint32    Constants::kReservationListPageCount        = 18;
    //
    const Uint32    Constants::kSystemUserId                    = 0;
    //
    const Uint32    Constants::kInactivityTimeoutSec            = 180;
    //
    const Uint32    Constants::kAdminInactivityTimeoutSec       = 300;
}

