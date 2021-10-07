//

#include "timeddialog.h"

namespace PenyaManager {
    //
    TimedDialog::TimedDialog(QWidget *parent, QTimer *pInactivityTimer) :
        QDialog(parent)
    {
        Q_UNUSED(pInactivityTimer)
    }
}
