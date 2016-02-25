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
            //
            void on_backPushButton_clicked();

        private:
            //
            void initialize();

        private:
            //
            Ui::AdminNewProvider        *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            QString                     m_providerImageFilename;
    };
}

#endif // ADMINNEWPROVIDER_H