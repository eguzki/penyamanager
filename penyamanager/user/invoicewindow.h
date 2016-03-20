#ifndef INVOICEWINDOW_H
#define INVOICEWINDOW_H

#include <objs/Member.h>
#include <objs/Invoice.h>
#include <commons/IPartner.h>
#include "memberprofilegroupbox.h"

namespace Ui {
    class InvoiceWindow;
}

namespace PenyaManager {
    //
    class InvoiceWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit InvoiceWindow(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~InvoiceWindow();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillInvoiceData(const MemberPtr &pMemberPtr, const InvoicePtr &pInvoicePtr);
            //
            void initializeTable();
            //
            void translateTable();

        private slots:
            //
            void on_backPushButton_clicked();
            //
            void on_confirmPushButton_clicked();
            //
            void on_printPushButton_clicked();

        private:
            //
            Ui::InvoiceWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };

}

#endif // INVOICEWINDOW_H
