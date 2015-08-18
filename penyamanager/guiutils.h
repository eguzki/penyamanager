#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QPixmap>

#include "DataTypes.h"

namespace PenyaManager {
    //
    class GuiUtils
    {
        public:
            // get image
            static QPixmap getImage(const QString& filename);

        private:
            //
            GuiUtils() {}
            //
            ~GuiUtils() {}
    };
}

#endif // GUIUTILS_H