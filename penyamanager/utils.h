#ifndef UTILS_H
#define UTILS_H

#include "DataTypes.h"
#include <QPixmap>

namespace PenyaManager {
    //
    class Utils
    {
        public:
            // get image
            static QPixmap getImage(const QString& filename);

        private:
            //
            Utils() {}
            //
            ~Utils() {}
    };
}

#endif // PENYACONSTANTS_H
