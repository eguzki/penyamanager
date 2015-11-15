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
    Int32 Singletons::m_currentInvoiceId = 0;
    Int32 Singletons::m_currentProductId = 0;
    Int32 Singletons::m_currentFamilyId = 0;
    Int32 Singletons::m_currentMemberId = 0;
    TranslationManager Singletons::m_translationManager;

    void Singletons::Create(QSettings *pSettings)
    {
        m_pSettings = pSettings;
        m_pSettings->beginGroup(Constants::kDatabaseGroupName);
        QString ddbbHost(m_pSettings->value(Constants::kDatabaseHost).toString());
        QString ddbbName(m_pSettings->value(Constants::kDatabaseName).toString());
        QString ddbbUser(m_pSettings->value(Constants::kDatabaseUser).toString());
        QString cryptedDDBBPass(m_pSettings->value(Constants::kDatabasePass).toString());
        m_pSettings->endGroup();

        // DAO Acces
        // decrypt pass
        QString ddbbPass(Utils::decryptToString(cryptedDDBBPass));
        //qDebug() << "host: " << ddbbHost;
        //qDebug() << "name: " << ddbbName;
        //qDebug() << "user: " << ddbbUser;
        //qDebug() << "pass: " << ddbbPass;
        m_pDAO = new DAO(ddbbHost, ddbbName, ddbbUser, ddbbPass);
        //m_pDAO = new DAO("192.168.1.254", "alegria", "root", "Urko&Eguzki");
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
    }
}
