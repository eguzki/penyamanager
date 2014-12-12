#ifndef PENYACONSTANTS_H
#define PENYACONSTANTS_H

#include "DataTypes.h"

namespace PenyaManager {
    //
    class Constants
    {
        public:
            // FamilyWidget image width
            static const Uint32     kFamilyImageWidth;
            // FamilyWidget image width
            static const Uint32     kFamilyImageHeigth;
            // image root path
            static const QString    kImageRootPath;

        private:
            Constants() {}
    };
}

#endif // PENYACONSTANTS_H
