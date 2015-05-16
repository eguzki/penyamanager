#ifndef PARTNERFINDER_H
#define PARTNERFINDER_H

#include "DataTypes.h"
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
            IPartner*   getPartner(Uint32 partnerKey);
            //
            void addPartner(Uint32 partnerKey, IPartner *);

        private:
            //
            typedef std::map<Uint32, IPartner*> PartnerMap;
            PartnerMap                              m_partnerMap;
    };
}

#endif // PARTNERFINDER_H
