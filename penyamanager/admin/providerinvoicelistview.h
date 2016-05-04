#ifndef PROVIDERINVOICELISTVIEW_H
#define PROVIDERINVOICELISTVIEW_H

#include <QWidget>

#include <objs/ProviderInvoice.h>
#include <commons/IPartner.h>

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
            explicit ProviderInvoiceListView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~ProviderInvoiceListView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void translateTable();
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

            void on_invoicesTableWidget_cellDoubleClicked(int row, int column);

    private:
            //
            Ui::ProviderInvoiceListView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            Uint32                      m_currentPage;
            //
            bool                        m_firstTime;
            //
            RowIdStrMap                 m_rowProviderInvoiceIdMap;
    };

}

#endif // PROVIDERINVOICELISTVIEW_H
