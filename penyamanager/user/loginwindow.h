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
            explicit LoginWindow(QWidget *parent, QTranslator *pTranslator, QTimer *pInactivityTimer, const CentralWidgetCallback &callback);
            //
            ~LoginWindow();
            //
            void retranslate();

        private:
            //
            void init();
            //
            void translateTable();
            //
            void initializeTable();
            //
            void initializeLang();
            //
            void fillLastInvoiceOwnerInfo(const MemberPtr &pLastInvoiceOwnerPtr);
            //
            void fillLastInvoiceInfo(const InvoicePtr &pLastInvoicePtr);

        private slots:
            //
            void on_loginPushButton_clicked();
            //
            void on_languagePushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void onInactivityTimeout();

        private:
            //
            Ui::LoginWindow             *ui;
            //
            Uint32                      m_currentPage;
            //
            QString                     m_password;
            //
            Int32                       m_username;
            //
            QTranslator                 *m_pTranslator;
            //
            QTimer                      *m_pInactivityTimer;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // LOGINWINDOW_H
