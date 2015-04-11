#ifndef IPARNER_H
#define IPARNER_H

#include <QWidget>

namespace PenyaManager {

    //
    class IPartner: public QWidget
    {
        public:
            //
            explicit IPartner(QWidget *parent = 0)
                :
                    QWidget(parent)
        {
        }
            //
            virtual ~IPartner(){}
            // called every time window is shown
            virtual void init() = 0;
    };
}

#endif // IPARNER_H
