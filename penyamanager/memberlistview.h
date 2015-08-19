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
            explicit MemberListView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~MemberListView();
            //
            void init();
            //
            void retranslate();

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
            //
            void on_memberTableWidget_cellDoubleClicked(int row, int column);

        private:
            //
            Ui::MemberListView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            Uint32                      m_currentPage;
            //
            RowIdMap                    m_rowProductIdMap;
    };
}

#endif // MEMBERLISTVIEW_H
