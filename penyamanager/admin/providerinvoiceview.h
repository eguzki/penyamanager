#ifndef PROVIDERINVOICEVIEW_H
#define PROVIDERINVOICEVIEW_H

#include <QWidget>

#include <commons/DataTypes.h>
#include <objs/ProductItem.h>
#include <commons/IPartner.h>

namespace Ui {
    //
    class ProviderInvoiceView;
}

namespace PenyaManager {
    //
    class ProviderInvoiceView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit ProviderInvoiceView(QWidget *parent = 0);
            //
            ~ProviderInvoiceView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void initialize();
            //
            void fillProviderInvoiceProducts(const QString &providerInvoiceId);
            //
            void initializeTable();

    private:
            //
            Ui::ProviderInvoiceView *ui;
    };
}

#endif // PROVIDERINVOICEVIEW_H
