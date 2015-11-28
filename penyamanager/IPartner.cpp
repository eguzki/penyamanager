//

#include "singletons.h"
#include "IPartner.h"

namespace PenyaManager {
    //
    void IPartner::switchWindow(WindowKey key)
    {
        // hide current window
        hide();
        // call next window
        IPartner* pPartner = Singletons::m_pParnetFinder->getPartner(key);
        pPartner->init();

    }
    //
    void IPartner::changeEvent(QEvent* event)
    {
        if (event->type() == QEvent::LanguageChange)
        {
            // retranslate designer form
            this->retranslate();
        }
        QWidget::changeEvent(event);
    }
}

