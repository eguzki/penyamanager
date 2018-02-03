#ifndef PENYACONSTANTS_H
#define PENYACONSTANTS_H

#include <QString>
#include "DataTypes.h"

namespace PenyaManager {
    //
    enum class WindowKey {
            kLoginWindowKey, kMemberDashboardWindowKey, kInvoiceWindowKey, kInvoiceListWindoKey, kDepositsWindowKey,
            kAccountViewWindowKey, kTableReservationViewWindowKey, kAdminLoginWindowKey,
            kMemberListViewWindowKey, kAdminSlowPayersWindowKey, kAdminInvoiceListWindowKey,
            kInvoiceDetailsWindowKey, kAdminProviderWindowKey, kAdminNewProviderKey, kStockManagementWindowKey,
            kFamilyItemManagementWindowKey, kAdminProductItemKey, kAdminFamilyViewKey, kProductExpensesViewKey,
            kProviderInvoiceViewKey, kProviderInvoiceListViewKey, kAdminDepositListViewKey, kAdminAccountBalanceViewKey,
            kMemberViewKey, kAdminReservationViewKey, kNewProviderInvoiceViewKey
    };
    //
    typedef std::function<void(WindowKey)>  CentralWidgetCallback;

    //
    class Constants
    {
        public:
            // Config settings org
            static const QString    kOrganizationName;
            // Config settings app
            static const QString    kApplicationName;
            // Config settings resource path key
            static const QString    kResourcePathKey;
            // Config settings ddbb group name
            static const QString    kDatabaseGroupName;
            // Config settings ddbb host
            static const QString    kDatabaseHost;
            // Config settings ddbb name
            static const QString    kDatabaseName;
            // Config settings ddbb username
            static const QString    kDatabaseUser;
            // Config settings ddbb pass
            static const QString    kDatabasePass;
            // Config settings syslogserver
            static const QString    kSyslogServer;
            // Config settings debug
            static const QString    kDebugConfig;
            // FamilyWidget width
            static const Uint32     kFamilyWidgetWidth;
            // FamilyWidget image width
            static const Uint32     kFamilyImageWidth;
            // FamilyWidget image width
            static const Uint32     kFamilyImageHeigth;
            // id role
            static const Int32      kIdRole;
            // Member image width
            static const Uint32     kMemberImageWidth;
            // Member image width
            static const Uint32     kMemberImageHeigth;
            // Invoice List page count
            static const Uint32     kInvoiceListPageCount;
            // Admin invoice List page count
            static const Uint32     kAdminInvoiceListPageCount;
            // Account List page count
            static const Uint32     kAccountListPageCount;
            // Admin account List page count
            static const Uint32     kAdminAccountListPageCount;
            // Admin Product List page count
            static const Uint32     kAdminProductListPageCount;
            // Crypt key
            static const quint64    kCryptKey;
            // Num languages available
            static const Uint16     kNumLangs;
            // Log file max size in bytes
            static const quint64    kLogMaxSizeBytes;
            // Open invoice timeout in hours
            static const Uint32     kOpenInvoiceTimeoutH;
            // Credit limit
            static const Float      kCreditLimit;
            // Dashboard product item list
            static const Uint32     kDashboardProductListPageCount;
            // LoginWindow product item list
            static const Uint32     kLoginWindowProductListPageCount;
            // InvoiceWindow product item list
            static const Uint32     kInvoiceWindowProductListPageCount;
            // InvoiceDetailsWindow product item list
            static const Uint32     kInvoiceDetailsWindowProductListPageCount;
            // Reservation item list
            static const Uint32     kReservationListPageCount;
            //
            static const Uint32     kSystemUserId;
            //
            static const Uint32     kInactivityTimeoutSec;
            //
            static const Uint32     kAdminInactivityTimeoutSec;

        private:
            Constants() {}
    };
}

#endif // PENYACONSTANTS_H
