#ifndef MEMBERDASHBOARDWINDOW_H
#define MEMBERDASHBOARDWINDOW_H

#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>

#include <commons/IPartner.h>
#include <objs/Member.h>
#include <objs/Invoice.h>
#include <objs/ProductItem.h>
#include <objs/ProductFamily.h>
#include "memberprofilegroupbox.h"

namespace Ui {
    class MemberDashboardWindow;
}

namespace PenyaManager {

    //
    class MemberDashboardWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit MemberDashboardWindow(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~MemberDashboardWindow();

        private:
            //
            void translateTable();
            //
            void retranslate();
            //
            void fillFamilyProducts(const ProductFamilyListPtr &pflPtr);
            //
            void fillProductItems(Int32 familyId);
            //
            void createFamilyWidget(const ProductFamilyPtr &pfPtr, QListWidget *pList);
            //
            void createProductItemWidget(const ProductItemPtr &pfPtr, QListWidget *pList);
            //
            void fillInvoiceData(const InvoicePtr &pInvoicePtr);
            //
            void initializeTable();
            //
            void on_productRemoveButton_clicked(int productId, QString productNameEus, QString productNameEs, Float totalPrice);
            //
            void on_productRemove_result(int productId, QMessageBox::StandardButton);
            //
            void onInvoiceReset(QMessageBox::StandardButton);
            //
            void checkCreditLimit();
            //
            void onNumItemSelectedFromInvoice(Int32 productId, QString resultStr);
            //
            void onNumItemSelectedFromProductList(Int32 productId, QString resultStr);

        private:
            //
            Ui::MemberDashboardWindow   *ui;
            //
            Uint32                      m_currentPage;
            //
            RowIdMap                    m_rowProductIdMap;
            //
            MemberProfileGroupBox       *m_pMemberProfileGroupBox;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;

        private slots:
            //
            void init();
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
            //
            void on_tableReservationButton_clicked();
            //
            void on_invoicesPushButton_clicked();
            //
            void on_familyListWidget_itemClicked(QListWidgetItem *item);
            //
            void on_productListWidget_itemClicked(QListWidgetItem *item);
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
    };
}

#endif // MEMBERDASHBOARDWINDOW_H
