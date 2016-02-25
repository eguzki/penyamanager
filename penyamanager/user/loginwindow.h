#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QTranslator>

#include <commons/IPartner.h>

namespace Ui {
    //
    class LoginWindow;
}

namespace PenyaManager {

    //
    class LoginWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit LoginWindow(QWidget *parent, QTranslator *pTranslator, const CentralWidgetCallback &callback);
            //
            ~LoginWindow();
            //
            void retranslate();

        private slots:
            //
            void init();
            //
            void on_loginPushButton_clicked();
            //
            void on_languagePushButton_clicked();

        private:
            //
            Ui::LoginWindow             *ui;
            //
            QString                     m_password;
            //
            Int32                       m_memberId;
            //
            QTranslator                 *m_pTranslator;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // LOGINWINDOW_H
