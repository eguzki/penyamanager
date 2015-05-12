//

#include <QDebug>

#include "constants.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "invoicewindow.h"
#include "depositwindow.h"
#include "accountview.h"
#include "tablereservations.h"
#include "partnerfinder.h"

namespace PenyaManager {

    //
    PartnerFinder::PartnerFinder()
    {
        // Load windows
        m_partnerMap[Constants::kLoginWindowKey] = new LoginWindow;
        m_partnerMap[Constants::kMainWindowKey] = new MainWindow;
        m_partnerMap[Constants::kInvoiceWindowKey] = new InvoiceWindow;
        m_partnerMap[Constants::kDepositsWindowKey] = new DepositWindow;
        m_partnerMap[Constants::kAccountViewWindowKey] = new AccountView;
        m_partnerMap[Constants::kTableReservationViewWindowKey] = new TableReservations;
    }
    //
    PartnerFinder::~PartnerFinder()
    {
        for (auto iter = m_partnerMap.begin(), end = m_partnerMap.end(); iter != end; ++iter)
        {
            delete iter->second;
        }
        m_partnerMap.clear();
    }
    //
    IPartner* PartnerFinder::getPartner(Uint32 partnerKey)
    {
        auto partner = m_partnerMap.find(partnerKey);
        if (partner == m_partnerMap.end()) {
            //this should never happen
            abort();
        }
        return partner->second;
    }
}
