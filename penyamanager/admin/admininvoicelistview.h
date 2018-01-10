#ifndef ADMININVOICELISTVIEW_H
#define ADMININVOICELISTVIEW_H

#include <QWidget>

#include <objs/Invoice.h>
#include <commons/DataTypes.h>
#include <commons/IPartner.h>

namespace Ui {
class AdminInvoiceListView;
}

namespace PenyaManager {
    //
    class AdminInvoiceListView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminInvoiceListView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~AdminInvoiceListView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillInvoiceList(InvoiceListPtr pInvoiceListPtr);
            //
            void updateResults();
            //
            void initializeTable();
            //
            void translateTable();

        private slots:
            //
            void on_clearPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_searchPushButton_clicked();
            //
            void on_invoicesTableWidget_cellDoubleClicked(int row, int column);

    private:
            //
            Ui::AdminInvoiceListView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            Uint32                      m_currentPage;
            //
            RowIdMap                    m_rowProductIdMap;
            //
            bool                        m_firstTime;
    };
}

#endif // ADMININVOICELISTVIEW_H
