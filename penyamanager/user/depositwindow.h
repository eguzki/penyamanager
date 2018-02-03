#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QWidget>
#include <QMessageBox>

#include <commons/IPartner.h>
#include <objs/Member.h>
#include <objs/Deposit.h>
#include "memberprofilegroupbox.h"

namespace Ui {
class DepositWindow;
}

namespace PenyaManager {
    //
    class DepositWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit DepositWindow(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~DepositWindow();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void updateNewBalanceLabel(double deposit);
            //
            void printDeposit(const MemberPtr &pMemberPtr, const DepositPtr &pDepositPtr);
            //
            QString renderDepositTemplate(const QString &depositTemplate, const MemberPtr &pMemberPtr, const DepositPtr &pDepositPtr);
            //
            void onDepositConfirmed(QMessageBox::StandardButton answerButton);
            //
            void onDepositCreated();

        private slots:
            //
            void on_confirmButton_clicked();
            //
            void onPushButton_number_clicked(Uint32 num);
            //
            void on_pushButton_coma_clicked();
            //
            void on_pushButton_C_clicked();

            void on_newinvoiceButton_clicked();

            void on_tableReservationButton_clicked();

            void on_invoicesPushButton_clicked();

            void on_accountButton_clicked();

            void on_exitButton_clicked();

    private:
            //
            Ui::DepositWindow *ui;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            double                      m_depositValue;
            //
            Uint8                       m_decimalPosition;
    };
}

#endif // DEPOSITWINDOW_H
