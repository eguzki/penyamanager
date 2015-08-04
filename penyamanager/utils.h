#ifndef UTILS_H
#define UTILS_H

#include <QPixmap>

#include "DataTypes.h"
#include "constants.h"

namespace PenyaManager {
    //
    class Utils
    {
        public:
            // get image
            static QPixmap getImage(const QString& filename);
            // file name
            static QString newImageName(const QString& prefix, const QString& filename);
            //
            static QString hashSHA256asHex(const QString& plainText);

        private:
            //
            Utils() {}
            //
            ~Utils() {}
    };
}

#endif // PENYACONSTANTS_H
