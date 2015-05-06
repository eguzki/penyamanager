#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>

#include "objs/Member.h"
#include "IPartner.h"

namespace Ui {
class AccountView;
}

namespace PenyaManager {
    //
    class AccountView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AccountView(QWidget *parent = 0);
            //
            ~AccountView();
            //
            void init();

        private:
            //
            void fillMemberProfile(const MemberPtr &pMemberPtr);

        private slots:
            //
            void on_fromCalendarWidget_clicked(const QDate &date);
            //
            void on_toCalendarWidget_clicked(const QDate &date);
            //
            void on_backPushButton_clicked();

        private:
            //
            Ui::AccountView *ui;
    };
}

#endif // ACCOUNTVIEW_H
