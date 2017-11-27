#ifndef INVOICEDETAILSWINDOW_H
#define INVOICEDETAILSWINDOW_H

#include <QWidget>

#include <objs/InvoiceProductItem.h>
#include <commons/IPartner.h>
#include "memberprofilegroupbox.h"

namespace Ui {
class InvoiceDetailsWindow;
}

namespace PenyaManager {
    //
    class InvoiceDetailsWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit InvoiceDetailsWindow(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~InvoiceDetailsWindow();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillInvoiceData(const InvoiceProductItemListResultPtr &pInvoiceProductItemListResultPtr);
            //
            void initializeTable();
            //
            void translateTable();
            //
            void updateResults();

        private slots:
            //
            void on_printButton_clicked();
            //
            void on_newinvoiceButton_clicked();
            //
            void on_tableReservationButton_clicked();
            //
            void on_invoicesPushButton_clicked();
            //
            void on_accountButton_clicked();
            //
            void on_depositsButton_clicked();
            //
            void on_exitButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();

        private:
            //
            Ui::InvoiceDetailsWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            Uint32                      m_currentPage;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // INVOICEDETAILSWINDOW_H
