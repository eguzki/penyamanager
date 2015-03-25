#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "families.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    families *fam;


private slots:
    void pushbutton1_click();
    void on_login_main_clicked();
};

#endif // MAINWINDOW_H
