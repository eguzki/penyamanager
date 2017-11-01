#ifndef INVOICELISTWINDOW_H
#define INVOICELISTWINDOW_H

#include <QWidget>

#include <objs/Invoice.h>
#include <commons/IPartner.h>
#include "memberprofilegroupbox.h"

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
            explicit InvoiceListWindow(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~InvoiceListWindow();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void fillInvoiceList(InvoiceListPtr pInvoiceListPtr);
            //
            void initializeTable();
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
            void on_invoicesTableWidget_cellClicked(int row, int column);
            //
            void on_exitButton_2_clicked();

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
            //
            Int32                       m_currentMemberId;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // INVOICELISTWINDOW_H
