#ifndef MEMBERLISTVIEW_H
#define MEMBERLISTVIEW_H

#include "objs/Member.h"
#include "IPartner.h"

namespace Ui {
    //
    class MemberListView;
}

namespace PenyaManager {
    //
    class MemberListView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit MemberListView(QWidget *parent = 0);
            //
            ~MemberListView();
            //
            void init();

        private:
            //
            void updateResults();
            //
            void fillMemberList(const MemberListPtr &pMemberListPtr);
            //
            void initializeTable();

        private slots:
            //
            void on_newMemberPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();

        private:
            //
            Ui::MemberListView *ui;
            //
            Uint32                      m_currentPage;
    };
}

#endif // MEMBERLISTVIEW_H
