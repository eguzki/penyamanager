#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>

#include <objs/Transaction.h>
#include <commons/IPartner.h>
#include "memberprofilegroupbox.h"

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
            void fillAccountData(TransactionListResultPtr pTransactionListResultPtr);
            //
            void initializeTable();
            //
            void updateResults();

        private slots:
            //
            void on_backPushButton_clicked();
            //
            void on_searchButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();

        private:
            //
            Ui::AccountView *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            Uint32                      m_currentPage;
            //
            bool                        m_firstTime;
            //
            Int32                       m_currentMemberId;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // ACCOUNTVIEW_H
