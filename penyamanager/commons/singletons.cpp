//

#include "utils.h"
#include "singletons.h"

namespace PenyaManager {

    //
    // Initialization
    //
    DAO *Singletons::m_pDAO = NULL;
    MemberPtr Singletons::m_pCurrMember;
    Services *Singletons::m_pServices = NULL;
    PartnerFinder *Singletons::m_pParnetFinder = NULL;
    QSettings *Singletons::m_pSettings = NULL;
    PenyaManagerLoggerPtr Singletons::m_pLogger;
    Int32 Singletons::m_currentInvoiceId = 0;
    Int32 Singletons::m_currentProductId = 0;
    Int32 Singletons::m_currentFamilyId = 0;
    Int32 Singletons::m_currentMemberId = 0;
    Int32 Singletons::m_currentProviderId = 0;
    QString Singletons::m_currentProviderInvoiceId;
    TranslationManager *Singletons::m_pTranslationManager;
    QTimer *Singletons::m_pInactivityTimer = NULL;
    Float Singletons::m_creditLimit = 0;

    void Singletons::Create(QSettings *pSettings, PenyaManagerLoggerPtr pLogger, QTimer *pInactivityTimer)
    {
        m_pSettings = pSettings;
        m_pLogger = pLogger;
        m_pInactivityTimer = pInactivityTimer;
        m_pSettings->beginGroup(Constants::kDatabaseGroupName);
        QString ddbbHost(m_pSettings->value(Constants::kDatabaseHost).toString());
        QString ddbbName(m_pSettings->value(Constants::kDatabaseName).toString());
        QString ddbbUser(m_pSettings->value(Constants::kDatabaseUser).toString());
        QString cryptedDDBBPass(m_pSettings->value(Constants::kDatabasePass).toString());
        m_pSettings->endGroup();

        // Credit Limit
        bool ok;
        float tmpCreditLimit = m_pSettings->value(Constants::kCreditLimitSettingsKey, Constants::kDefaultCreditLimit).toFloat(&ok);
        if (!ok) {
            m_pLogger->Warn(Constants::kNoUserId, PenyaManager::LogAction::kMain,
                    QString("Credit Limit setting not valid. Fix needed. Value: %1").arg(
                        m_pSettings->value(Constants::kCreditLimitSettingsKey).toString()
                        ));
            tmpCreditLimit = Constants::kDefaultCreditLimit;
        }
        m_creditLimit = tmpCreditLimit;

        // Translation Manager
        m_pTranslationManager = new TranslationManager;

        // DAO Acces
        // decrypt pass
        QString ddbbPass(Utils::decryptToString(cryptedDDBBPass));
        m_pDAO = new DAO(ddbbHost, ddbbName, ddbbUser, ddbbPass);
        m_pServices = new Services;
        m_pParnetFinder = new PartnerFinder;
    }

    void Singletons::Destroy()
    {
        if (m_pDAO)
        {
            delete m_pDAO;
            m_pDAO = 0;
        }
        if (m_pServices)
        {
            delete m_pServices;
            m_pServices = 0;
        }
        if (m_pParnetFinder)
        {
            delete m_pParnetFinder;
            m_pParnetFinder = 0;
        }
        if (m_pTranslationManager)
        {
            delete m_pTranslationManager;
            m_pTranslationManager = 0;
        }
    }
}
