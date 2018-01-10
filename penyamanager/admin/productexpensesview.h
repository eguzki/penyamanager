#ifndef PRODUCTEXPENSESVIEW_H
#define PRODUCTEXPENSESVIEW_H

#include <QWidget>

#include <objs/InvoiceProductItem.h>
#include <commons/DataTypes.h>
#include <commons/IPartner.h>

namespace Ui {
    //
    class ProductExpensesView;
}

namespace PenyaManager {
    //
    class ProductExpensesView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit ProductExpensesView(QWidget *parent = 0);
            //
            ~ProductExpensesView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillProductList(const InvoiceProductItemListPtr &pInvoiceProductItemListPtr);
            //
            void updateResults();
            //
            void initializeTable();
            //
            void translateTable();
            //
            void onProductExpensesCsvSelected(const QString &fn);

        private slots:
            //
            void on_clearPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();
            //
            void on_searchPushButton_clicked();
            //
            void on_csvPushButton_clicked();

    private:
            //
            Ui::ProductExpensesView *ui;
            //
            Uint32                      m_currentPage;
            //
            bool                        m_firstTime;
    };
}

#endif // PRODUCTEXPENSESVIEW_H
