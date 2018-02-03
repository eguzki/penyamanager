#ifndef MEMBERLISTVIEW_H
#define MEMBERLISTVIEW_H

#include <objs/Member.h>
#include <commons/IPartner.h>

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
            void translateTable();
            //
            void updateResults();
            //
            void fillMemberList(const MemberListPtr &pMemberListPtr);
            //
            void initializeTable();
            //
            void onMemberListCsvSelected(const QString &fn);

        private slots:
            //
            void on_newMemberPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_memberTableWidget_cellDoubleClicked(int row, int column);
            //
            void on_csvPushButton_clicked();
            //
            void on_filterPostalUsersCheckBox_clicked();
            //
            void on_printPostalMembersPushButton_clicked();
            //
            void on_prev10PagePushButton_clicked();
            //
            void on_next10PagePushButton_clicked();
            //
            void on_pageNumberSpinBox_valueChanged(int page);

    private:
            //
            Ui::MemberListView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            RowIdMap                    m_rowProductIdMap;
    };
}

#endif // MEMBERLISTVIEW_H
