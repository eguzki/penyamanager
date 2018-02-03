#ifndef IPARNER_H
#define IPARNER_H

#include <QWidget>

#include "constants.h"

namespace PenyaManager {

    //
    class IPartner: public QWidget
    {
        public:
            //
            explicit IPartner(QWidget *parent = NULL);
            //
            virtual ~IPartner(){}
            // called every time window is shown
            virtual void init() = 0;
            //
            virtual void retranslate() = 0;
            //
            virtual void changeEvent(QEvent* event);
    };
}

#endif // IPARNER_H
