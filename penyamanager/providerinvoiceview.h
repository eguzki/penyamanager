#ifndef PROVIDERINVOICEVIEW_H
#define PROVIDERINVOICEVIEW_H

#include <QWidget>

#include "DataTypes.h"
#include "objs/ProductItem.h"
#include "IPartner.h"

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
            void initialize();
            //
            void createProductItemRow(const ProductItemPtr &pfPtr);

        private slots:
            //
            void on_savePushButton_clicked();
            //
            void on_providerComboBox_activated(int index);

    private:
            //
            Ui::ProviderInvoiceView *ui;
            //
            Int32                       m_currentProviderIndex;
            //
            RowIdMap                    m_rowProviderIdMap;
    };
}

#endif // PROVIDERINVOICEVIEW_H
