#ifndef PROVIDERMANAGERVIEW_H
#define PROVIDERMANAGERVIEW_H

#include <QWidget>
#include <QListWidgetItem>

#include "objs/ProductItem.h"
#include "objs/Provider.h"
#include "IPartner.h"

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
            explicit ProviderManagerView(QWidget *parent = 0);
            //
            ~ProviderManagerView();
            //
            void init();

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

        private:
            //
            Ui::ProviderManagerView *ui;
    };

}

#endif // PROVIDERMANAGERVIEW_H
