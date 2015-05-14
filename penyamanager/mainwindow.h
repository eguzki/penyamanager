#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
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
        //
        void readNumItems(Int32 productId);

    private:
        //
        Ui::MainWindow *ui;
        //
        typedef std::map<Int32, Int32>          RowProductIdMap;
        RowProductIdMap                         m_rowProductIdMap;

    private slots:
        //
        void init();
        //
        void familyItemClicked(QListWidgetItem* item);
        //
        void productItemClicked(QListWidgetItem* item);
        //
        void on_invoiceCloseButton_clicked();
        //
        void on_invoiceResetButton_clicked();
        //
        void on_exitButton_clicked();
        //
        void on_depositsButton_clicked();
        //
        void on_invoiceTableWidget_cellClicked(int row, int column);
        //
        void on_accountButton_clicked();
        void on_tableReservationButton_clicked();
};
}

#endif // MAINWINDOW_H
