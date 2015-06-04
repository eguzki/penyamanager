#ifndef ADMININVOICEDETAILS_H
#define ADMININVOICEDETAILS_H

#include <QWidget>

#include "IPartner.h"

namespace Ui {
class AdminInvoiceDetails;
}

namespace PenyaManager {
    //
    class AdminInvoiceDetails : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminInvoiceDetails(QWidget *parent = 0);
            //
            ~AdminInvoiceDetails();
            //
            void init();

        private:
            Ui::AdminInvoiceDetails *ui;
    };

}

#endif // ADMININVOICEDETAILS_H
