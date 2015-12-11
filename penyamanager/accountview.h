#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>

#include "memberprofilegroupbox.h"
#include "IPartner.h"

namespace Ui {
class AccountView;
}

namespace PenyaManager {
    //
    class AccountView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AccountView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~AccountView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void fillAccountData(Int32 memberId, const QDate &fromDate, const QDate &toDate);
            //
            void initializeTable();

        private slots:
            //
            void on_backPushButton_clicked();
            //
            void on_searchButton_clicked();

        private:
            //
            Ui::AccountView *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // ACCOUNTVIEW_H
