#ifndef ADMINLOGINWINDOW_H
#define ADMINLOGINWINDOW_H

#include <QTranslator>

#include <commons/IPartner.h>
#include "adminmainwindow.h"

namespace Ui {
    //
    class AdminLoginWindow;
}

namespace PenyaManager {

    //
    class AdminLoginWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminLoginWindow(QWidget *parent, AdminMainWindow *pAdminMainWindow, QTranslator *pTranslator);
            //
            ~AdminLoginWindow();
            //
            void retranslate();

        private:
            //
            void initializeLang();

        private:
            //
            AdminMainWindow *m_pAdminMainWindow;
            //
            Ui::AdminLoginWindow *ui;
            //
            QTranslator     *m_pTranslator;

        private slots:
            //
            void init();
            //
            void on_loginButton_clicked();
            void on_languagePushButton_clicked();
    };

}
#endif // ADMINLOGINWINDOW_H
