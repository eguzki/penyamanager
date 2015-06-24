#ifndef FAMILYITEMMANAGEMENTWINDOW_H
#define FAMILYITEMMANAGEMENTWINDOW_H

#include <QListWidget>
#include "objs/ProductItem.h"
#include "objs/ProductFamily.h"
#include "IPartner.h"

namespace Ui {
class FamilyItemManagementWindow;
}

namespace PenyaManager {
    //
    class FamilyItemManagementWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit FamilyItemManagementWindow(QWidget *parent = 0);
            //
            ~FamilyItemManagementWindow();
            //
            void init();

        private:
            //
            void fillFamilyProducts(const ProductFamilyListPtr &pflPtr);
            //
            void createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList);
            //
            void fillProductItems(Int32 familyId);
            //
            void createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList);

        private slots:
            //
            void on_newItemPushButton_clicked();
            //
            void on_newFamilyPushButton_clicked();
            //
            void familyItemClicked(QListWidgetItem* item);
            //
            void productItemClicked(QListWidgetItem* item);

        private:
            //
            Ui::FamilyItemManagementWindow *ui;
    };
}

#endif // FAMILYITEMMANAGEMENTWINDOW_H
