#ifndef SINGLETONS_H
#define SINGLETONS_H

#include "dao.h"

class Singletons
{
    public:
        //
        static void Create();
        static void Destroy();

    public:
        static DAO *m_pDAO;
};

#endif // SINGLETONS_H
