#ifndef FAMILIES_H
#define FAMILIES_H

#include <QMainWindow>

namespace Ui {
class families;
}

class families : public QMainWindow
{
    Q_OBJECT

public:
    explicit families(QWidget *parent = 0);
    ~families();

private:
    Ui::families *ui;
};

#endif // FAMILIES_H
