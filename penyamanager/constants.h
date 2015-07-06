#ifndef PENYACONSTANTS_H
#define PENYACONSTANTS_H

#include <QString>
#include "DataTypes.h"

namespace PenyaManager {
    //
    enum class WindowKey {
            kLoginWindowKey, kMainWindowKey, kInvoiceWindowKey, kInvoiceListWindoKey, kDepositsWindowKey,
            kAccountViewWindowKey, kTableReservationViewWindowKey, kAdminLoginWindowKey,
            kAdminMemberInfoWindowKey, kAdminSlowPayersWindowKey, kAdminInvoiceListWindowKey,
            kInvoiceDetailsWindowKey, kAdminProviderWindowKey, kAdminNewProviderKey, kStockManagementWindowKey,
            kFamilyItemManagementWindowKey, kAdminProductItemKey, kAdminFamilyViewKey, kProductExpensesViewKey,
            kProviderInvoiceViewKey, kProviderInvoiceListViewKey, kAdminDepositListViewKey
    };
    //
    typedef std::function<void(WindowKey)>	CentralWidgetCallback;

    //
    class Constants
    {
        public:
            // FamilyWidget width
            static const Uint32     kFamilyWidgetWidth;
            // FamilyWidget image width
            static const Uint32     kFamilyImageWidth;
            // FamilyWidget image width
            static const Uint32     kFamilyImageHeigth;
            // image root path
            static const QString    kImageRootPath;
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

        private:
            Constants() {}
    };
}

#endif // PENYACONSTANTS_H
