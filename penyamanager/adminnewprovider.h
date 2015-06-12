#ifndef ADMINNEWPROVIDER_H
#define ADMINNEWPROVIDER_H

#include <QWidget>
#include <QPixmap>

#include "constants.h"
#include "utils.h"
#include "IPartner.h"

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
            Ui::AdminNewProvider *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // ADMINNEWPROVIDER_H
