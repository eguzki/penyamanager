#include "utils.h"

namespace PenyaManager {
    // get image
    QPixmap Utils::getImage(const QString& filename) 
    {
        QPixmap image(filename);
        if (image.isNull()) {
            image = QPixmap(":images/no-image.gif");
        }
        return image;
    }
}
