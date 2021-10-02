//
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/singletons.h>
#include "alertsview.h"
#include "ui_alertsview.h"

namespace PenyaManager {
    //
    AlertsView::AlertsView(QWidget *parent, const CentralWidgetCallback &callback) :
        IPartner(parent),
        ui(new Ui::AlertsView),
        m_switchCentralWidgetCallback(callback)
    {
        ui->setupUi(this);
    }
    //
    AlertsView::~AlertsView()
    {
        delete ui;
    }
    //
    void AlertsView::init()
    {
        this->ui->alertListWidget->clear();

        // fetch data
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getOldInactiveMembers(Constants::kAdminInactivityPeriodMonths);
        if (pMemberListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        // fill data
        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            QPixmap icon = GuiUtils::getImage(":images/icon-inactive.png").scaled(35, 35);
            QString lastRenewalDateLocalized = Singletons::m_pTranslationManager->getLocale().
                toString(pMemberPtr->m_inactiveModificationDate.startOfDay().toLocalTime(), QLocale::NarrowFormat);
            QString message = tr("%1 %2 %3 (%4) has been inactive since %5 and not renewed").
                arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname1).arg(pMemberPtr->m_surname2).
                arg(pMemberPtr->m_username).arg(lastRenewalDateLocalized);
            QListWidgetItem *item = new QListWidgetItem(icon, message);
            item->setData(Constants::kIdRole, pMemberPtr->m_id);
            this->ui->alertListWidget->addItem(item);
        }

        if (pMemberListResultPtr->m_list->size() > 0) {
            Singletons::m_pDialogManager->infoMessageBoxTitled( this,
                    tr("There are alerts that need your attention"), [](){});
            // nothing should be added here
            return;
        }
    }
    //
    void AlertsView::retranslate()
    {
        this->ui->retranslateUi(this);
    }
    //
    void AlertsView::on_alertListWidget_itemClicked(QListWidgetItem *item)
    {
        // use static global variable to pass argument
        Singletons::m_currentMemberId = item->data(Constants::kIdRole).toInt();

        // call member window
        m_switchCentralWidgetCallback(WindowKey::kMemberViewKey);
    }
}
