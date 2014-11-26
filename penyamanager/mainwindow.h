#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setParner(QWidget *partner);

private:
    Ui::MainWindow *ui;

private slots:
    void quitButtonOnClick();
};

#endif // MAINWINDOW_H
