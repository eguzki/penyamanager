#ifndef NEWPROVIDERINVOICEVIEW_H
#define NEWPROVIDERINVOICEVIEW_H

#include <QWidget>

#include <commons/DataTypes.h>
#include <objs/ProductItem.h>
#include <commons/IPartner.h>

namespace Ui {
    //
    class NewProviderInvoiceView;
}

namespace PenyaManager {
    //
    class NewProviderInvoiceView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit NewProviderInvoiceView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~NewProviderInvoiceView();
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
            Ui::NewProviderInvoiceView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            Int32                       m_currentProviderIndex;
            //
            RowIdMap                    m_rowProviderIdMap;
    };
}

#endif // NEWPROVIDERINVOICEVIEW_H
