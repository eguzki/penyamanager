#ifndef INVOICEDETAILSWINDOW_H
#define INVOICEDETAILSWINDOW_H

#include <QWidget>

#include <objs/Invoice.h>
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
            void fillInvoiceData(const InvoicePtr &pInvoicePtr);
            //
            void initializeTable();
            //
            void translateTable();

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

        private:
            //
            Ui::InvoiceDetailsWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // INVOICEDETAILSWINDOW_H
