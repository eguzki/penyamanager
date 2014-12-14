#ifndef PENYACONSTANTS_H
#define PENYACONSTANTS_H

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

        private:
            Constants() {}
    };
}

#endif // PENYACONSTANTS_H
