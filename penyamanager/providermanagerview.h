#ifndef PROVIDERMANAGERVIEW_H
#define PROVIDERMANAGERVIEW_H

#include <QWidget>

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

        private:
            //
            Ui::ProviderManagerView *ui;
    };

}

#endif // PROVIDERMANAGERVIEW_H
