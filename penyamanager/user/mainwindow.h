#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTranslator>
#include <QTimer>

#include <commons/constants.h>

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
            explicit MainWindow(QWidget *parent, QTranslator *pTranslator, QTimer *pInactivityTimer);
            //
            ~MainWindow();
            //
            void switchCentralWidget(WindowKey key);
            //
            void init();
        protected:
            //
            void paintEvent(QPaintEvent *);

        private:
            //
            Ui::MainWindow *ui;
    };

}

#endif // MAINWINDOW_H
