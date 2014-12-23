#ifndef SERVICES_H
#define SERVICES_H

#include "objs/Member.h"

namespace PenyaManager {

    //
    class Services
    {
        public:
            //
            Services();
            //
            virtual ~Services();
            //
            MemberPtr getMemberbyName(const QString &memberLoginName) const;

        private:
    };
}

#endif
