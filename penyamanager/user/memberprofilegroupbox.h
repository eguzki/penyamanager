#ifndef MEMBERPROFILEGROUPBOX_H
#define MEMBERPROFILEGROUPBOX_H

#include <QGroupBox>

#include <objs/Member.h>

namespace Ui {
    //
    class MemberProfileGroupBox;
}

namespace PenyaManager {
    //
    class MemberProfileGroupBox : public QGroupBox
    {
        Q_OBJECT

        public:
            //
            explicit MemberProfileGroupBox(QWidget *parent = 0);
            //
            ~MemberProfileGroupBox();
            //
            void init(const MemberPtr &member);
            //
            void retranslate();

        private:
            //
            Ui::MemberProfileGroupBox *ui;
    };

}

#endif // MEMBERPROFILEGROUPBOX_H
