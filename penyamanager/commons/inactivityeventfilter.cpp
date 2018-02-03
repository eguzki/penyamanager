//

#include <QEvent>

#include "inactivityeventfilter.h"

namespace PenyaManager {
    //
    InactivityEventFilter::InactivityEventFilter(QTimer *pInactivityTimer) :
        m_pInactivityTimer(pInactivityTimer)
    {
    }
    //
    InactivityEventFilter::~InactivityEventFilter()
    {
    }
    //
    bool InactivityEventFilter::eventFilter(QObject *obj, QEvent *ev)
    {
        if(ev->type() == QEvent::MouseButtonPress) {
            if (m_pInactivityTimer->isActive()) {
                // reset timer
                m_pInactivityTimer->start();
            }
        }
        return QObject::eventFilter(obj, ev);
    }
}
