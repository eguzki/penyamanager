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
            void selectionChanged();
            //
            void updateResults();

        private slots:
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_invoicesTableWidget_cellPressed(int row, int column);
            //
            void on_newinvoiceButton_clicked();
            //
            void on_tableReservationButton_clicked();
            //
            void on_depositsButton_clicked();
            //
            void on_accountButton_clicked();
            //
            void on_exitButton_clicked();
            //
            void on_fromCalendarWidget_selectionChanged();
            //
            void on_toCalendarWidget_selectionChanged();

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
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // INVOICELISTWINDOW_H
