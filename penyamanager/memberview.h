#ifndef MEMBERVIEW_H
#define MEMBERVIEW_H

#include <QDate>

#include "IPartner.h"

namespace Ui {
    //
    class MemberView;
}

namespace PenyaManager {
    //
    class MemberView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit MemberView(QWidget *parent = 0);
            //
            ~MemberView();
            //
            void init();

        private:
            //
            void fillMemberInfo(Int32 memberId);
            //
            void initialize();

        private slots:
            //
            void on_savePushButton_clicked();
            //
            void on_imagePushButton_clicked();

    private:
            //
            Ui::MemberView *ui;
            //
            QString                     m_memberImageFilename;
            //
            QDate                       m_minDate;
    };
}

#endif // MEMBERVIEW_H
