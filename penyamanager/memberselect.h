#ifndef MEMBERSELECT_H
#define MEMBERSELECT_H

#include <QDialog>

namespace Ui {
class memberselect;
}

class memberselect : public QDialog
{
    Q_OBJECT

public:
    explicit memberselect(QWidget *parent = 0);
    ~memberselect();
    int userid;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::memberselect *ui;
};

#endif // MEMBERSELECT_H
