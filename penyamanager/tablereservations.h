#ifndef TABLERESERVATIONS_H
#define TABLERESERVATIONS_H

#include <QWidget>

#include "objs/Member.h"
#include "IPartner.h"

namespace Ui {
class TableReservations;
}

namespace PenyaManager {
    //
    class TableReservations : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit TableReservations(QWidget *parent = 0);
            //
            ~TableReservations();
            //
            void init();

        private:
            //
            void fillMemberProfile(const MemberPtr &);
    
        private slots:
            //
            void on_backButton_clicked();
            //
            void on_lunchButton_clicked();
            //
            void on_dinnerButton_clicked();

    private:
            //
            Ui::TableReservations *ui;
    };

}

#endif // TABLERESERVATIONS_H
