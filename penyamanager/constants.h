#ifndef PENYACONSTANTS_H
#define PENYACONSTANTS_H

#include <QString>
#include "DataTypes.h"

namespace PenyaManager {
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
            // LoginWindow key
            static const Uint32     kLoginWindowKey;
            // MainWindow key 
            static const Uint32     kMainWindowKey;
            // InvoiceWindow key
            static const Uint32     kInvoiceWindowKey;
            // DepositsWindow key
            static const Uint32     kDepositsWindowKey;

        private:
            Constants() {}
    };
}

#endif // PENYACONSTANTS_H
