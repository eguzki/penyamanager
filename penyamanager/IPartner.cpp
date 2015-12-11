//

#include "singletons.h"
#include "IPartner.h"

namespace PenyaManager {
    //
    IPartner::IPartner(QWidget *parent)
        :
            QWidget(parent)
    {
        // hide current widget
        hide();
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

