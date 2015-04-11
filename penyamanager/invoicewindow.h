#ifndef INVOICEWINDOW_H
#define INVOICEWINDOW_H

#include "IPartner.h"

namespace Ui {
    class InvoiceWindow;
}

namespace PenyaManager {

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
            Ui::InvoiceWindow *ui;
    };

}

#endif // INVOICEWINDOW_H
