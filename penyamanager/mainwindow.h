#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>

#include "objs/Member.h"
#include "objs/Invoice.h"
#include "objs/ProductItem.h"
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
        void fillProductItems(Int32 familyId);
        //
        void fillMemberProfile(const MemberPtr &pMemberPtr);
        //
        void createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList);
        //
        void createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList);
        //
        void fillInvoiceData(const InvoicePtr &pInvoicePtr);

    private:
        Ui::MainWindow *ui;

    private slots:
        //
        void quitButtonOnClick();
        //
        void init();
        //
        void familyItemClicked(QListWidgetItem* item);
        //
        void productItemClicked(QListWidgetItem* item);
};
}

#endif // MAINWINDOW_H
