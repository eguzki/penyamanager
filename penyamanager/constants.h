#ifndef PENYACONSTANTS_H
#define PENYACONSTANTS_H

#include <QString>
#include "DataTypes.h"

namespace PenyaManager {
    //
    enum class WindowKey {
            kLoginWindowKey, kMainWindowKey, kInvoiceWindowKey, kInvoiceListWindoKey, kDepositsWindowKey,
            kAccountViewWindowKey, kTableReservationViewWindowKey, kAdminLoginWindowKey,
            kMemberListViewWindowKey, kAdminSlowPayersWindowKey, kAdminInvoiceListWindowKey,
            kInvoiceDetailsWindowKey, kAdminProviderWindowKey, kAdminNewProviderKey, kStockManagementWindowKey,
            kFamilyItemManagementWindowKey, kAdminProductItemKey, kAdminFamilyViewKey, kProductExpensesViewKey,
            kProviderInvoiceViewKey, kProviderInvoiceListViewKey, kAdminDepositListViewKey, kAdminAccountBalanceViewKey,
            kMemberViewKey
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
            // Product List page count
            static const Uint32     kProductListPageCount;
            // Crypt key
            static const quint64    kCryptKey;
            // Num languages available
            static const Uint16     kNumLangs;

        private:
            Constants() {}
    };
}

#endif // PENYACONSTANTS_H
