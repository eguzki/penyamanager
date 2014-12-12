#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>

#include "objs/ProductFamily.h"
#include "IPartner.h"

namespace Ui {
class MainWindow;
}


namespace PenyaManager {

class MainWindow : public IPartner
{
    Q_OBJECT

    public:
        //
        explicit MainWindow(QWidget *parent = 0);
        //
        ~MainWindow();
        //
        void setParner(IPartner *partner);

    private:
        //
        void fillFamilyProducts(const ProductFamilyListPtr &pflPtr);
        //
        void createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList);

    private:
        Ui::MainWindow *ui;

    private slots:
        //
        void quitButtonOnClick();
        //
        void init();
        //
        void familyItemClicked(QListWidgetItem* item);
};
}

#endif // MAINWINDOW_H
