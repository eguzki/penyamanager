#ifndef IPARNER_H
#define IPARNER_H

#include <QWidget>

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
        //
        virtual void init() = 0;
        //
        virtual void setParner(IPartner *partner) = 0;
};

#endif // IPARNER_H
