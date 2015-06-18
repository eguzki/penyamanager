#ifndef INVOICEWINDOW_H
#define INVOICEWINDOW_H

#include "objs/Member.h"
#include "objs/Invoice.h"
#include "memberprofilegroupbox.h"
#include "IPartner.h"

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
            explicit InvoiceWindow(QWidget *parent = 0);
            //
            ~InvoiceWindow();
            //
            void init();

        private:
            //
            void fillInvoiceData(const MemberPtr &pMemberPtr, const InvoicePtr &pInvoicePtr);

        private slots:
            //
            void on_backPushButton_clicked();
            //
            void on_confirmPushButton_clicked();
            //
            void on_cashRadioButton_toggled(bool cashButtonChecked);

    private:
            //
            Ui::InvoiceWindow *ui;
            //
            Float               m_cachedInvoiceTotal;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
    };

}

#endif // INVOICEWINDOW_H
