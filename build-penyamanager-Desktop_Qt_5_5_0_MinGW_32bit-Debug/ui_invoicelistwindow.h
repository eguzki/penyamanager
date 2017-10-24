/********************************************************************************
** Form generated from reading UI file 'invoicelistwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICELISTWINDOW_H
#define UI_INVOICELISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvoiceListWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *backPushButton;
    QPushButton *searchPushButton;
    QWidget *resultWidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *calendarWidget;
    QVBoxLayout *verticalLayout_2;
    QCalendarWidget *fromCalendarWidget;
    QCalendarWidget *toCalendarWidget;
    QSpacerItem *horizontalSpacer;
    QWidget *pagingWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *pageInfoLabel;
    QLabel *totalCountValueLabel;
    QLabel *totalCountLabel;
    QLabel *totalInvoicesValueLabel;
    QLabel *totalInvoicesLabel;
    QLabel *toDateResultValueLabel;
    QLabel *toDateResultLabel;
    QLabel *fromDateResultValueLabel;
    QLabel *fromDateResultLabel;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *prevPagePushButton;
    QPushButton *nextPagePushButton;
    QWidget *resultsWidget;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *invoicesTableWidget;
    QWidget *searchWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *InvoiceListWindow)
    {
        if (InvoiceListWindow->objectName().isEmpty())
            InvoiceListWindow->setObjectName(QStringLiteral("InvoiceListWindow"));
        InvoiceListWindow->resize(1463, 768);
        InvoiceListWindow->setStyleSheet(QLatin1String("QCalendarWidget QToolButton {\n"
"  	height: 30px;\n"
"  	width: 120px;\n"
"  	color: black;\n"
"	font-weight: bold;\n"
"	font: 20pt \"Calibri\";\n"
"  	icon-size: 30px, 56px;\n"
"  	background-color: rgb(158,158,158);\n"
"  }\n"
"  QCalendarWidget QMenu {\n"
"  	width: 150px;\n"
"  	left: 20px;\n"
"  	color: white;\n"
"  	font-size: 18px;\n"
"  	background-color: rgb(100, 100, 100);\n"
"  }\n"
"  QCalendarWidget QSpinBox { \n"
"  	width: 150px; \n"
"  	font-size:24px; \n"
"  	color: white; \n"
"  	background-color: rgb(158,158,158); \n"
"  	selection-background-color: rgb(136, 136, 136);\n"
"  	selection-color: rgb(255, 255, 255);\n"
"  }\n"
"  QCalendarWidget QSpinBox::up-button { subcontrol-origin: border;  subcontrol-position: top right;  width:65px; }\n"
"  QCalendarWidget QSpinBox::down-button {subcontrol-origin: border; subcontrol-position: bottom right;  width:65px;}\n"
"  QCalendarWidget QSpinBox::up-arrow { width:10px;  height:10px; }\n"
"  QCalendarWidget QSpinBox::down-arrow { width:10px;  height:1"
                        "0px; }\n"
"   \n"
"  /* header row */\n"
"  QCalendarWidget QWidget { alternate-background-color: rgb(117,117,117); }\n"
"   \n"
"  /* normal days */\n"
"  QCalendarWidget QAbstractItemView:enabled \n"
"  {\n"
"  	color: black;\n"
"	font-weight: bold;\n"
"	font: 20pt \"Calibri\";  \n"
"  	background-color: rgb(189,189,189);  \n"
"  	selection-background-color:  rgb(198,40,40); \n"
"  	selection-color: white; \n"
"  }\n"
"   \n"
"  /* days in other months */\n"
"  /* navigation bar */\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{ \n"
"background-color: rgb(158,158,158); \n"
"}\n"
"\n"
"QCalendarWidget QAbstractItemView:disabled \n"
"{ \n"
"color: rgb(158,158,158); \n"
"}"));
        verticalLayout = new QVBoxLayout(InvoiceListWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelWidget = new QWidget(InvoiceListWindow);
        topPanelWidget->setObjectName(QStringLiteral("topPanelWidget"));
        topPanelWidget->setMinimumSize(QSize(0, 150));
        topPanelWidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout_3 = new QHBoxLayout(topPanelWidget);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 1, 1, 1);
        backPushButton = new QPushButton(topPanelWidget);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(backPushButton->sizePolicy().hasHeightForWidth());
        backPushButton->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(backPushButton);

        searchPushButton = new QPushButton(topPanelWidget);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));
        sizePolicy.setHeightForWidth(searchPushButton->sizePolicy().hasHeightForWidth());
        searchPushButton->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(searchPushButton);


        verticalLayout->addWidget(topPanelWidget);

        resultWidget = new QWidget(InvoiceListWindow);
        resultWidget->setObjectName(QStringLiteral("resultWidget"));
        horizontalLayout_4 = new QHBoxLayout(resultWidget);
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        calendarWidget = new QWidget(resultWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(600, 0));
        verticalLayout_2 = new QVBoxLayout(calendarWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        fromCalendarWidget = new QCalendarWidget(calendarWidget);
        fromCalendarWidget->setObjectName(QStringLiteral("fromCalendarWidget"));
        fromCalendarWidget->setGridVisible(true);
        fromCalendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        fromCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        verticalLayout_2->addWidget(fromCalendarWidget);

        toCalendarWidget = new QCalendarWidget(calendarWidget);
        toCalendarWidget->setObjectName(QStringLiteral("toCalendarWidget"));
        toCalendarWidget->setGridVisible(true);
        toCalendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        toCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        verticalLayout_2->addWidget(toCalendarWidget);


        horizontalLayout_4->addWidget(calendarWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pagingWidget = new QWidget(resultWidget);
        pagingWidget->setObjectName(QStringLiteral("pagingWidget"));
        pagingWidget->setMaximumSize(QSize(150, 16777215));
        verticalLayout_3 = new QVBoxLayout(pagingWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pageInfoLabel = new QLabel(pagingWidget);
        pageInfoLabel->setObjectName(QStringLiteral("pageInfoLabel"));
        pageInfoLabel->setText(QStringLiteral("X / Y"));

        verticalLayout_3->addWidget(pageInfoLabel);

        totalCountValueLabel = new QLabel(pagingWidget);
        totalCountValueLabel->setObjectName(QStringLiteral("totalCountValueLabel"));
        totalCountValueLabel->setMinimumSize(QSize(100, 0));
        totalCountValueLabel->setMaximumSize(QSize(100, 16777215));

        verticalLayout_3->addWidget(totalCountValueLabel);

        totalCountLabel = new QLabel(pagingWidget);
        totalCountLabel->setObjectName(QStringLiteral("totalCountLabel"));

        verticalLayout_3->addWidget(totalCountLabel);

        totalInvoicesValueLabel = new QLabel(pagingWidget);
        totalInvoicesValueLabel->setObjectName(QStringLiteral("totalInvoicesValueLabel"));
        totalInvoicesValueLabel->setMinimumSize(QSize(100, 0));
        totalInvoicesValueLabel->setMaximumSize(QSize(100, 16777215));

        verticalLayout_3->addWidget(totalInvoicesValueLabel);

        totalInvoicesLabel = new QLabel(pagingWidget);
        totalInvoicesLabel->setObjectName(QStringLiteral("totalInvoicesLabel"));

        verticalLayout_3->addWidget(totalInvoicesLabel);

        toDateResultValueLabel = new QLabel(pagingWidget);
        toDateResultValueLabel->setObjectName(QStringLiteral("toDateResultValueLabel"));
        toDateResultValueLabel->setMinimumSize(QSize(200, 0));
        toDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        verticalLayout_3->addWidget(toDateResultValueLabel);

        toDateResultLabel = new QLabel(pagingWidget);
        toDateResultLabel->setObjectName(QStringLiteral("toDateResultLabel"));

        verticalLayout_3->addWidget(toDateResultLabel);

        fromDateResultValueLabel = new QLabel(pagingWidget);
        fromDateResultValueLabel->setObjectName(QStringLiteral("fromDateResultValueLabel"));
        fromDateResultValueLabel->setMinimumSize(QSize(200, 0));
        fromDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        verticalLayout_3->addWidget(fromDateResultValueLabel);

        fromDateResultLabel = new QLabel(pagingWidget);
        fromDateResultLabel->setObjectName(QStringLiteral("fromDateResultLabel"));

        verticalLayout_3->addWidget(fromDateResultLabel);

        horizontalWidget = new QWidget(pagingWidget);
        horizontalWidget->setObjectName(QStringLiteral("horizontalWidget"));
        horizontalLayout_2 = new QHBoxLayout(horizontalWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        prevPagePushButton = new QPushButton(horizontalWidget);
        prevPagePushButton->setObjectName(QStringLiteral("prevPagePushButton"));

        horizontalLayout_2->addWidget(prevPagePushButton);

        nextPagePushButton = new QPushButton(horizontalWidget);
        nextPagePushButton->setObjectName(QStringLiteral("nextPagePushButton"));

        horizontalLayout_2->addWidget(nextPagePushButton);


        verticalLayout_3->addWidget(horizontalWidget);


        horizontalLayout_4->addWidget(pagingWidget);

        resultsWidget = new QWidget(resultWidget);
        resultsWidget->setObjectName(QStringLiteral("resultsWidget"));
        resultsWidget->setMinimumSize(QSize(490, 0));
        resultsWidget->setMaximumSize(QSize(490, 16777215));
        verticalLayout_4 = new QVBoxLayout(resultsWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        invoicesTableWidget = new QTableWidget(resultsWidget);
        invoicesTableWidget->setObjectName(QStringLiteral("invoicesTableWidget"));
        invoicesTableWidget->setMinimumSize(QSize(0, 0));
        invoicesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        invoicesTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        invoicesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        invoicesTableWidget->verticalHeader()->setVisible(false);
        invoicesTableWidget->verticalHeader()->setDefaultSectionSize(50);
        invoicesTableWidget->verticalHeader()->setMinimumSectionSize(50);

        verticalLayout_4->addWidget(invoicesTableWidget);


        horizontalLayout_4->addWidget(resultsWidget);


        verticalLayout->addWidget(resultWidget);

        searchWidget = new QWidget(InvoiceListWindow);
        searchWidget->setObjectName(QStringLiteral("searchWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(searchWidget->sizePolicy().hasHeightForWidth());
        searchWidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(searchWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);

        verticalLayout->addWidget(searchWidget);


        retranslateUi(InvoiceListWindow);

        QMetaObject::connectSlotsByName(InvoiceListWindow);
    } // setupUi

    void retranslateUi(QWidget *InvoiceListWindow)
    {
        InvoiceListWindow->setWindowTitle(QApplication::translate("InvoiceListWindow", "Invoice List", 0));
        backPushButton->setText(QApplication::translate("InvoiceListWindow", "Back", 0));
        searchPushButton->setText(QApplication::translate("InvoiceListWindow", "Search", 0));
        totalCountValueLabel->setText(QApplication::translate("InvoiceListWindow", "0 \342\202\254", 0));
        totalCountLabel->setText(QApplication::translate("InvoiceListWindow", "Total:", 0));
        totalInvoicesValueLabel->setText(QApplication::translate("InvoiceListWindow", "0", 0));
        totalInvoicesLabel->setText(QApplication::translate("InvoiceListWindow", "Total Invoices:", 0));
        toDateResultValueLabel->setText(QApplication::translate("InvoiceListWindow", "10-10-2015", 0));
        toDateResultLabel->setText(QApplication::translate("InvoiceListWindow", "To:", 0));
        fromDateResultValueLabel->setText(QApplication::translate("InvoiceListWindow", "10-10-2015", 0));
        fromDateResultLabel->setText(QApplication::translate("InvoiceListWindow", "From:", 0));
        prevPagePushButton->setText(QApplication::translate("InvoiceListWindow", "<", 0));
        nextPagePushButton->setText(QApplication::translate("InvoiceListWindow", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class InvoiceListWindow: public Ui_InvoiceListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICELISTWINDOW_H
