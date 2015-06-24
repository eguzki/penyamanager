#ifndef STOCKMANAGEMENTWINDOW_H
#define STOCKMANAGEMENTWINDOW_H

#include <QWidget>

#include "objs/ProductItem.h"
#include "IPartner.h"

namespace Ui {
    //
    class StockManagementWindow;
}

namespace PenyaManager {
    //
    class StockManagementWindow : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit StockManagementWindow(QWidget *parent = 0);
            //
            ~StockManagementWindow();
            //
            void init();

        private:
            //
            void updateResults();
            //
            void fillProductList(const ProductItemListPtr &pProductItemListPtr);
            //
            void initializeTable();

        private slots:
            //
            void on_csvPushButton_clicked();
            //
            void on_printPushButton_clicked();

            void on_prevPagePushButton_clicked();

            void on_nextPagePushButton_clicked();

        private:
            //
            Ui::StockManagementWindow *ui;
            //
            Uint32                      m_currentPage;

    };
}

#endif // STOCKMANAGEMENTWINDOW_H