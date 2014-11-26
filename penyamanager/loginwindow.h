#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void setParner(QWidget *partner);

private:
    Ui::LoginWindow *ui;

private slots:

};

#endif // LOGINWINDOW_H
