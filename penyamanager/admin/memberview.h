#ifndef MEMBERVIEW_H
#define MEMBERVIEW_H

#include <QDate>

#include <commons/IPartner.h>

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
            explicit MemberView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~MemberView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillMemberInfo(Int32 memberId);
            //
            void initialize();
            //
            void onPassGiven(int res, QString passwd);
            //
            void onMemberUpdated();
            //
            void onMemberImageSelected(const QString &fn);

        private slots:
            //
            void on_savePushButton_clicked();
            //
            void on_imagePushButton_clicked();
            //
            void on_changePasswordPushButton_clicked();

        private:
            //
            Ui::MemberView *ui;
            //
            QString                     m_memberImageFilename;
            //
            QDate                       m_minDate;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // MEMBERVIEW_H
