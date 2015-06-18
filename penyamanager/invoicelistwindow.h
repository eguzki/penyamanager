#ifndef INVOICELISTWINDOW_H
#define INVOICELISTWINDOW_H

#include <QWidget>

#include "objs/Invoice.h"
#include "memberprofilegroupbox.h"
#include "IPartner.h"

namespace Ui {
class InvoiceListWindow;
}

namespace PenyaManager {
    //
    class InvoiceListWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit InvoiceListWindow(QWidget *parent = 0);
            //
            ~InvoiceListWindow();
            //
            void init();

        private:
            //
            void fillInvoiceList(InvoiceListPtr pInvoiceListPtr);
            //
            void updateResults();

        private slots:
            //
            void on_searchPushButton_clicked();
            //
            void on_backPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_invoicesTableWidget_cellDoubleClicked(int row, int column);

        private:
            //
            Ui::InvoiceListWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            Uint32                      m_currentPage;
            //
            RowIdMap                    m_rowProductIdMap;
            //
            bool                        m_firstTime;
    };
}

#endif // INVOICELISTWINDOW_H
