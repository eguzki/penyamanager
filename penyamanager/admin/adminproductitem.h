#ifndef ADMINPRODUCTITEM_H
#define ADMINPRODUCTITEM_H

#include <commons/IPartner.h>

namespace Ui {
class AdminProductItem;
}

namespace PenyaManager {
    //
    class AdminProductItem : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminProductItem(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~AdminProductItem();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillProductInfo(Int32 productId);
            //
            void initialize();
            //
            void onProductImageSelected(const QString &fn);
            //
            void onProductItemUpdated();

        private slots:
            //
            void on_savePushButton_clicked();
            //
            void on_imagePushButton_clicked();

    private:
            //
            Ui::AdminProductItem *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            QString                     m_productImageFilename;
    };
}

#endif // ADMINPRODUCTITEM_H
