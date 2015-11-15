#ifndef PARTNERFINDER_H
#define PARTNERFINDER_H

#include "DataTypes.h"
#include "constants.h"
#include "IPartner.h"

namespace PenyaManager {

    //
    class PartnerFinder
    {
        public:
            //
            PartnerFinder();
            //
            virtual ~PartnerFinder();
            //
            IPartner*   getPartner(WindowKey partnerKey);
            //
            void addPartner(WindowKey partnerKey, IPartner *);

        private:
            //
            typedef std::map<WindowKey, IPartner*> PartnerMap;
            PartnerMap                              m_partnerMap;
    };
}

#endif // PARTNERFINDER_H
