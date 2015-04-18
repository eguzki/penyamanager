#ifndef ADMON_SCREEN_H
#define ADMON_SCREEN_H

#include "IPartner.h"
#include "objs/Member.h"

namespace Ui {
class admon_screen;
}


namespace PenyaManager {

class admon_screen : public IPartner
{
    Q_OBJECT

public:
    explicit admon_screen(QWidget *parent = 0);
    ~admon_screen();

    void setParner(IPartner *partner);
    void init();

private slots:
    void on_pushButton_clicked();

private:
    Ui::admon_screen *ui;
    void fillMemberProfile(const MemberByAdminPtr &pMemberPtr);

};
}

#endif // ADMON_SCREEN_H
