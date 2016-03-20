#ifndef INVOICEDETAILSWINDOW_H
#define INVOICEDETAILSWINDOW_H

#include <QWidget>

#include <commons/IPartner.h>
#include <commons/invoicedetailswidget.h>
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

        private slots:
            //
            void on_backPushButton_clicked();
            //
            void on_printButton_clicked();

        private:
            //
            Ui::InvoiceDetailsWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            InvoiceDetailsWidget        *m_pInvoiceDetailsWidget;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // INVOICEDETAILSWINDOW_H
