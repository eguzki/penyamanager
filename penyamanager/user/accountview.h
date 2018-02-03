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
            void selectionChanged();
            //
            void updateResults();

        private slots:
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_newinvoiceButton_clicked();
            //
            void on_tableReservationButton_clicked();
            //
            void on_invoicesPushButton_clicked();
            //
            void on_depositsButton_clicked();
            //
            void on_exitButton_clicked();
            //
            void on_fromCalendarWidget_selectionChanged();
            //
            void on_toCalendarWidget_selectionChanged();

    private:
            //
            Ui::AccountView *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            Uint32                      m_currentPage;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // ACCOUNTVIEW_H
