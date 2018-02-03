#ifndef INVOICEDETAILSWIDGET_H
#define INVOICEDETAILSWIDGET_H

#include <QWidget>

#include <objs/Invoice.h>
#include <commons/IPartner.h>

namespace Ui {
    //
    class InvoiceDetailsView;
}

namespace PenyaManager {
    //
    class InvoiceDetailsView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit InvoiceDetailsView(QWidget *parent = 0);
            //
            ~InvoiceDetailsView();
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

        private:
            //
            Ui::InvoiceDetailsView *ui;
    };

}

#endif // INVOICEDETAILSWIDGET_H
