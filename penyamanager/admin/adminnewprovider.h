#ifndef ADMINNEWPROVIDER_H
#define ADMINNEWPROVIDER_H

#include <QWidget>
#include <QPixmap>

#include <commons/constants.h>
#include <commons/utils.h>
#include <commons/IPartner.h>

namespace Ui {
    //
    class AdminNewProvider;
}

namespace PenyaManager {
    //
    class AdminNewProvider : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminNewProvider(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~AdminNewProvider();
            //
            void init();
            //
            void retranslate();

        private slots:
            //
            void on_imagePushButton_clicked();
            //
            void on_savePushButton_clicked();

        private:
            //
            void initialize();
            //
            void fillProviderInfo(Int32 providerId);
            //
            void onProviderUpdated();
            //
            void onProviderImageSelected(const QString &fn);

        private:
            //
            Ui::AdminNewProvider        *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            // only set when user selects image to be uploaded
            QString                     m_providerImageFilename;
    };
}

#endif // ADMINNEWPROVIDER_H
