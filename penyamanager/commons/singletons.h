#ifndef SINGLETONS_H
#define SINGLETONS_H

#include <QSettings>
#include <QTimer>

#include "translationmanager.h"
#include "objs/Member.h"
#include "services.h"
#include "partnerfinder.h"
#include "dao.h"
#include "logging.h"

namespace PenyaManager {
    //
    class Singletons
    {
        public:
            //
            static void Create(QSettings *pSettings, PenyaManagerLoggerPtr pLogger, QTimer *pInactivityTimer);
            //
            static void Destroy();


        public:
            //
            static DAO                      *m_pDAO;
            //
            static MemberPtr                m_pCurrMember;
            //
            static Services                 *m_pServices;
            //
            static PartnerFinder            *m_pParnetFinder;
            //
            static QSettings                *m_pSettings;
            //
            static PenyaManagerLoggerPtr    m_pLogger;
            //
            static Int32                    m_currentInvoiceId;
            //
            static Int32                    m_currentProductId;
            //
            static Int32                    m_currentFamilyId;
            //
            static Int32                    m_currentMemberId;
            //
            static Int32                    m_currentProviderId;
            //
            static QString                  m_currentProviderInvoiceId;
            //
            static TranslationManager       *m_pTranslationManager;
            //
            static QTimer                   *m_pInactivityTimer;
            //
            static Float                    m_creditLimit;
    };
}

#endif // SINGLETONS_H
