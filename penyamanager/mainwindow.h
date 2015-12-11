#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "constants.h"

namespace Ui {
    //
    class MainWindow;
}

namespace PenyaManager {

    //
    class MainWindow : public QWidget
    {
        Q_OBJECT

        public:
            //
            explicit MainWindow(QWidget *parent = NULL);
            //
            ~MainWindow();
            //
            void switchCentralWidget(WindowKey key);
            //
            void init();

        private:
            //
            Ui::MainWindow *ui;
    };

}

#endif // MAINWINDOW_H
