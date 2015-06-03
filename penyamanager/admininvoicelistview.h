#ifndef ADMININVOICELISTVIEW_H
#define ADMININVOICELISTVIEW_H

#include <QWidget>

#include "objs/Invoice.h"
#include "DataTypes.h"
#include "IPartner.h"

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
            explicit AdminInvoiceListView(QWidget *parent = 0);
            //
            ~AdminInvoiceListView();
            //
            void init();

        private:
            //
            void fillInvoiceList(InvoiceListPtr pInvoiceListPtr);
            //
            void updateResults();

        private slots:
            //
            void on_clearPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_searchPushButton_clicked();

        private:
            //
            Ui::AdminInvoiceListView *ui;
            //
            Uint32                      m_currentPage;
    };
}

#endif // ADMININVOICELISTVIEW_H
