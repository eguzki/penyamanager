#ifndef PROVIDERINVOICELISTVIEW_H
#define PROVIDERINVOICELISTVIEW_H

#include <QWidget>

#include "objs/ProviderInvoice.h"
#include "IPartner.h"

namespace Ui {
    //
    class ProviderInvoiceListView;
}

namespace PenyaManager {
    //
    class ProviderInvoiceListView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit ProviderInvoiceListView(QWidget *parent = 0);
            //
            ~ProviderInvoiceListView();
            //
            void init();

        private:
            //
            void fillInvoiceList(ProviderInvoiceListPtr pProviderInvoiceListPtr);
            //
            void updateResults();
            //
            void initialize();
            //
            void initializeTable();

        private slots:
            //
            void on_searchPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();

    private:
            //
            Ui::ProviderInvoiceListView *ui;
            //
            Uint32                      m_currentPage;
            //
            bool                        m_firstTime;
    };

}

#endif // PROVIDERINVOICELISTVIEW_H
