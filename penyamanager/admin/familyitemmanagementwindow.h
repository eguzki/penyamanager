#ifndef FAMILYITEMMANAGEMENTWINDOW_H
#define FAMILYITEMMANAGEMENTWINDOW_H

#include <QListWidget>
#include <objs/ProductItem.h>
#include <objs/ProductFamily.h>
#include <commons/IPartner.h>

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
            explicit FamilyItemManagementWindow(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~FamilyItemManagementWindow();
            //
            void init();
            //
            void retranslate();

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
            //
            void on_editFamilyPushButton_clicked();

    private:
            //
            Ui::FamilyItemManagementWindow *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
    };
}

#endif // FAMILYITEMMANAGEMENTWINDOW_H
