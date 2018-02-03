#ifndef ACCOUNTBALANCEVIEW_H
#define ACCOUNTBALANCEVIEW_H

#include <QWidget>
#include <objs/Transaction.h>
#include <commons/IPartner.h>

namespace Ui {
    //
    class AccountBalanceView;
}

namespace PenyaManager {
    //
    class AccountBalanceView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AccountBalanceView(QWidget *parent = 0);
            //
            ~AccountBalanceView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void initializeTable();
            //
            void fillTransactionList(TransactionListPtr pTransactionListPtr);
            //
            void updateResults();

        private slots:
            //
            void on_searchPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_clearPushButton_clicked();

        private:
            //
            Ui::AccountBalanceView *ui;
            //
            Uint32                      m_currentPage;
            //
            bool                        m_firstTime;
    };
}

#endif // ACCOUNTBALANCEVIEW_H
