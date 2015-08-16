//

#include "guiutils.h"

namespace PenyaManager {
    // get image
    QPixmap GuiUtils::getImage(const QString& filename)
    {
        QPixmap image(filename);
        if (image.isNull()) {
            image = QPixmap(":images/no-image.gif");
        }
        return image;
    }
}
