#ifndef PROVIDERMANAGERVIEW_H
#define PROVIDERMANAGERVIEW_H

#include <QWidget>
#include <QListWidgetItem>

#include <objs/ProductItem.h>
#include <objs/Provider.h>
#include <commons/IPartner.h>

namespace Ui {
class ProviderManagerView;
}

namespace PenyaManager {
    //
    class ProviderManagerView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit ProviderManagerView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~ProviderManagerView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillProviders();
            //
            void createProviderWidget(ProviderPtr pProviderPtr);
            //
            void fillProductItems(Int32 providerId);
            //
            void createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList);

        private slots:
            //
            void providerItemClicked(QListWidgetItem* item);
            //
            void on_newProviderPushButton_clicked();

    private:
            //
            Ui::ProviderManagerView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };

}

#endif // PROVIDERMANAGERVIEW_H
