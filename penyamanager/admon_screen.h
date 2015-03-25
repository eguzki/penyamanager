#ifndef ADMON_SCREEN_H
#define ADMON_SCREEN_H

#include <QMainWindow>

namespace Ui {
class admon_screen;
}

class admon_screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit admon_screen(QWidget *parent = 0);
    ~admon_screen();

private:
    Ui::admon_screen *ui;
};

#endif // ADMON_SCREEN_H
