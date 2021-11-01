//
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>

#include <commons/utils.h>
#include <commons/guiutils.h>
#include <commons/singletons.h>
#include <commons/timedmessagebox.h>
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

        Int32 error = processData();
        if (error) {
            return;
        }

        error = fillAlertList();
        if (error) {
            return;
        }

        if (this->ui->alertListWidget->count() > 0) {
            TimedMessageBox::infoMessageBoxTitled(this, tr("There are alerts that require your attention"), [](){});
            // nothing should be added here
            return;
        }
    }
    //
    Int32 AlertsView::processData()
    {
        Int32 error = processDroppedMembers();
        if (error) {
            return error;
        }

        return 0;
    }
    //
    Int32 AlertsView::processDroppedMembers()
    {
        // fetch data
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getOldDroppedMembers(Constants::kAdminMemberDroppedPeriodYears);
        if (pMemberListResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return pMemberListResultPtr->m_error;
        }

        // fill data
        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;

            pMemberPtr->m_imagePath = QString();
            pMemberPtr->m_active = Member::DEAD;
            pMemberPtr->m_lastModified = QDateTime::currentDateTimeUtc();
            pMemberPtr->m_isAdmin = false;
            pMemberPtr->m_birthdate = QDate();
            pMemberPtr->m_address = QString();
            pMemberPtr->m_zipCode = QString();
            pMemberPtr->m_town = QString();
            pMemberPtr->m_state = QString();
            pMemberPtr->m_phone = QString();
            pMemberPtr->m_phone2 = QString();
            pMemberPtr->m_email = QString();
            pMemberPtr->m_bank_account = QString("");
            pMemberPtr->m_notes = QString();
            pMemberPtr->m_idCard = QString();
            pMemberPtr->m_cardNumber = QString();

            // update in ddbb
            bool ok = Singletons::m_pDAO->updateMember(pMemberPtr);
            if (!ok) {
                TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
                return 1;
            }
            Singletons::m_pLogger->Info(Singletons::m_pCurrMember->m_id, PenyaManager::LogAction::kMember,
                    QString("erased %1").arg(pMemberPtr->m_id));
        }

        return 0;
    }
    //
    Int32 AlertsView::fillAlertList()
    {
        Int32 error = fillOldInactiveMembers();
        if (error) {
            return error;
        }

        return 0;
    }
    //
    Int32 AlertsView::fillOldInactiveMembers()
    {
        // fetch data
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getOldInactiveMembers(Constants::kAdminInactivityPeriodMonths);
        if (pMemberListResultPtr->m_error) {
            TimedMessageBox::criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return pMemberListResultPtr->m_error;
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

        return 0;
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
