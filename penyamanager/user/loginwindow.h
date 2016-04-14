#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QTranslator>

#include <commons/IPartner.h>
#include <objs/Member.h>
#include <objs/Invoice.h>

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
            void translateTable();
            //
            void initializeTable();
            //
            void fillLastInvoiceOwnerInfo(const MemberPtr &pLastInvoiceOwnerPtr);
            //
            void fillLastInvoiceInfo(const InvoicePtr &pLastInvoicePtr);
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
            Int32                       m_username;
            //
            QTranslator                 *m_pTranslator;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // LOGINWINDOW_H
