#ifndef INVOICEDETAILSWIDGET_H
#define INVOICEDETAILSWIDGET_H

#include <QWidget>

#include "objs/Invoice.h"
#include "IPartner.h"

namespace Ui {
    //
    class InvoiceDetailsWidget;
}

namespace PenyaManager {
    //
    class InvoiceDetailsWidget : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit InvoiceDetailsWidget(QWidget *parent = 0);
            //
            ~InvoiceDetailsWidget();
            //
            void init();

        private:
            //
            void fillInvoiceData(const InvoicePtr &pInvoicePtr);

        private:
            //
            Ui::InvoiceDetailsWidget *ui;
    };

}

#endif // INVOICEDETAILSWIDGET_H
