#ifndef INVOICEDETAILSWINDOW_H
#define INVOICEDETAILSWINDOW_H

#include <QWidget>

#include "memberprofilegroupbox.h"
#include "invoicedetailswidget.h"
#include "IPartner.h"

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
            explicit InvoiceDetailsWindow(QWidget *parent = 0);
            //
            ~InvoiceDetailsWindow();
            //
            void init();
            //
            void retranslate();

    private slots:
            //
            void on_backPushButton_clicked();

    private:
            //
            Ui::InvoiceDetailsWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            InvoiceDetailsWidget        *m_pInvoiceDetailsWidget;
    };
}

#endif // INVOICEDETAILSWINDOW_H
