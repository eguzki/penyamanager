#ifndef MEMBERVIEW_H
#define MEMBERVIEW_H

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

        private:
            //
            Ui::MemberView *ui;
            //
            QString                     m_memberImageFilename;
    };
}

#endif // MEMBERVIEW_H
