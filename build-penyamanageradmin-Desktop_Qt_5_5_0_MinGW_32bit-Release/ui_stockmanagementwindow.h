/********************************************************************************
** Form generated from reading UI file 'stockmanagementwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKMANAGEMENTWINDOW_H
#define UI_STOCKMANAGEMENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StockManagementWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *csvPushButton;
    QFrame *pagingFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *totalProductsLabel;
    QLabel *totalProductsValueLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *prevPagePushButton;
    QLabel *pageInfoLabel;
    QPushButton *nextPagePushButton;
    QFrame *productsFrame;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *productsTableWidget;

    void setupUi(QWidget *StockManagementWindow)
    {
        if (StockManagementWindow->objectName().isEmpty())
            StockManagementWindow->setObjectName(QStringLiteral("StockManagementWindow"));
        StockManagementWindow->resize(1200, 1000);
        StockManagementWindow->setStyleSheet(QLatin1String("#topFrame {\n"
"border: none;\n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"stop: 0 #a6a6a6, stop: 0.08 #7f7f7f,\n"
"stop: 0.39999 #717171, stop: 0.4 #626262,\n"
"stop: 0.9 #4c4c4c, stop: 1 #333333);\n"
"}\n"
"\n"
"#bottomFrame {\n"
"border: none;\n"
"background: white;\n"
"}\n"
"\n"
"#topFrame QLabel {\n"
"color: #fff;\n"
"}\n"
"\n"
"#topFrame QPushButton {\n"
"color: #333;\n"
"border: 2px solid #555;\n"
"border-radius: 11px;\n"
"padding: 5px;\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #888);\n"
"min-width: 80px;\n"
"}\n"
"\n"
"#topFrame QPushButton:hover {\n"
"background: qradialgradient(cx: 0.3, cy: -0.4,\n"
"fx: 0.3, fy: -0.4,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #bbb);\n"
"}\n"
"\n"
"#topFrame QPushButton:pressed {\n"
"background: qradialgradient(cx: 0.4, cy: -0.1,\n"
"fx: 0.4, fy: -0.1,\n"
"radius: 1.35, stop: 0 #fff, stop: 1 #ddd);\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(StockManagementWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(StockManagementWindow);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy);
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(topFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(topFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        csvPushButton = new QPushButton(topFrame);
        csvPushButton->setObjectName(QStringLiteral("csvPushButton"));

        horizontalLayout->addWidget(csvPushButton);


        verticalLayout->addWidget(topFrame);

        pagingFrame = new QFrame(StockManagementWindow);
        pagingFrame->setObjectName(QStringLiteral("pagingFrame"));
        pagingFrame->setFrameShape(QFrame::StyledPanel);
        pagingFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(pagingFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        totalProductsLabel = new QLabel(pagingFrame);
        totalProductsLabel->setObjectName(QStringLiteral("totalProductsLabel"));

        horizontalLayout_3->addWidget(totalProductsLabel);

        totalProductsValueLabel = new QLabel(pagingFrame);
        totalProductsValueLabel->setObjectName(QStringLiteral("totalProductsValueLabel"));
        totalProductsValueLabel->setMinimumSize(QSize(100, 0));
        totalProductsValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(totalProductsValueLabel);

        horizontalSpacer_3 = new QSpacerItem(376, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        prevPagePushButton = new QPushButton(pagingFrame);
        prevPagePushButton->setObjectName(QStringLiteral("prevPagePushButton"));

        horizontalLayout_3->addWidget(prevPagePushButton);

        pageInfoLabel = new QLabel(pagingFrame);
        pageInfoLabel->setObjectName(QStringLiteral("pageInfoLabel"));

        horizontalLayout_3->addWidget(pageInfoLabel);

        nextPagePushButton = new QPushButton(pagingFrame);
        nextPagePushButton->setObjectName(QStringLiteral("nextPagePushButton"));

        horizontalLayout_3->addWidget(nextPagePushButton);


        verticalLayout->addWidget(pagingFrame);

        productsFrame = new QFrame(StockManagementWindow);
        productsFrame->setObjectName(QStringLiteral("productsFrame"));
        productsFrame->setFrameShape(QFrame::StyledPanel);
        productsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(productsFrame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        productsTableWidget = new QTableWidget(productsFrame);
        productsTableWidget->setObjectName(QStringLiteral("productsTableWidget"));
        productsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        productsTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        productsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        productsTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(productsTableWidget);


        verticalLayout->addWidget(productsFrame);


        retranslateUi(StockManagementWindow);

        QMetaObject::connectSlotsByName(StockManagementWindow);
    } // setupUi

    void retranslateUi(QWidget *StockManagementWindow)
    {
        StockManagementWindow->setWindowTitle(QApplication::translate("StockManagementWindow", "Form", 0));
        titleLabel->setText(QApplication::translate("StockManagementWindow", "Stock Manager", 0));
        csvPushButton->setText(QApplication::translate("StockManagementWindow", "export to CSV", 0));
        totalProductsLabel->setText(QApplication::translate("StockManagementWindow", "Total Products:", 0));
        totalProductsValueLabel->setText(QApplication::translate("StockManagementWindow", "0", 0));
        prevPagePushButton->setText(QApplication::translate("StockManagementWindow", "<", 0));
        pageInfoLabel->setText(QApplication::translate("StockManagementWindow", "page X out of Y", 0));
        nextPagePushButton->setText(QApplication::translate("StockManagementWindow", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class StockManagementWindow: public Ui_StockManagementWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKMANAGEMENTWINDOW_H
