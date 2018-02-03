#ifndef STOCKMANAGEMENTWINDOW_H
#define STOCKMANAGEMENTWINDOW_H

#include <QWidget>

#include <objs/ProductItem.h>
#include <commons/IPartner.h>

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
            //
            void retranslate();

        private:
            //
            void translateTable();
            //
            void updateResults();
            //
            void fillProductList(const StockProductItemListPtr &pStockProductItemListPtr);
            //
            void initializeTable();
            //
            void onStockCsvSelected(const QString &fn);

        private slots:
            //
            void on_csvPushButton_clicked();
            //
            void on_prevPagePushButton_clicked();
            //
            void on_nextPagePushButton_clicked();

        private:
            //
            Ui::StockManagementWindow *ui;
            //
            Uint32                      m_currentPage;

    };
}

#endif // STOCKMANAGEMENTWINDOW_H
