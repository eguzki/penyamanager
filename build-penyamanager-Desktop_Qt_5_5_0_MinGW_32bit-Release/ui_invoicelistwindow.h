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
    QFrame *resultsFrame;
    QVBoxLayout *verticalLayout_4;
    QFrame *pagingFrame;
    QHBoxLayout *horizontalLayout_9;
    QLabel *fromDateResultLabel;
    QLabel *fromDateResultValueLabel;
    QLabel *toDateResultLabel;
    QLabel *toDateResultValueLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *totalInvoicesLabel;
    QLabel *totalInvoicesValueLabel;
    QLabel *totalCountLabel;
    QLabel *totalCountValueLabel;
    QPushButton *prevPagePushButton;
    QLabel *pageInfoLabel;
    QPushButton *nextPagePushButton;
    QTableWidget *invoicesTableWidget;
    QWidget *searchWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *InvoiceListWindow)
    {
        if (InvoiceListWindow->objectName().isEmpty())
            InvoiceListWindow->setObjectName(QStringLiteral("InvoiceListWindow"));
        InvoiceListWindow->resize(1024, 768);
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
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        calendarWidget = new QWidget(resultWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(400, 0));
        verticalLayout_2 = new QVBoxLayout(calendarWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
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

        resultsFrame = new QFrame(resultWidget);
        resultsFrame->setObjectName(QStringLiteral("resultsFrame"));
        resultsFrame->setFrameShape(QFrame::StyledPanel);
        resultsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(resultsFrame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pagingFrame = new QFrame(resultsFrame);
        pagingFrame->setObjectName(QStringLiteral("pagingFrame"));
        pagingFrame->setFrameShape(QFrame::StyledPanel);
        pagingFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(pagingFrame);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        fromDateResultLabel = new QLabel(pagingFrame);
        fromDateResultLabel->setObjectName(QStringLiteral("fromDateResultLabel"));

        horizontalLayout_9->addWidget(fromDateResultLabel);

        fromDateResultValueLabel = new QLabel(pagingFrame);
        fromDateResultValueLabel->setObjectName(QStringLiteral("fromDateResultValueLabel"));
        fromDateResultValueLabel->setMinimumSize(QSize(200, 0));
        fromDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_9->addWidget(fromDateResultValueLabel);

        toDateResultLabel = new QLabel(pagingFrame);
        toDateResultLabel->setObjectName(QStringLiteral("toDateResultLabel"));

        horizontalLayout_9->addWidget(toDateResultLabel);

        toDateResultValueLabel = new QLabel(pagingFrame);
        toDateResultValueLabel->setObjectName(QStringLiteral("toDateResultValueLabel"));
        toDateResultValueLabel->setMinimumSize(QSize(200, 0));
        toDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_9->addWidget(toDateResultValueLabel);

        horizontalSpacer_2 = new QSpacerItem(846, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        totalInvoicesLabel = new QLabel(pagingFrame);
        totalInvoicesLabel->setObjectName(QStringLiteral("totalInvoicesLabel"));

        horizontalLayout_9->addWidget(totalInvoicesLabel);

        totalInvoicesValueLabel = new QLabel(pagingFrame);
        totalInvoicesValueLabel->setObjectName(QStringLiteral("totalInvoicesValueLabel"));
        totalInvoicesValueLabel->setMinimumSize(QSize(100, 0));
        totalInvoicesValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_9->addWidget(totalInvoicesValueLabel);

        totalCountLabel = new QLabel(pagingFrame);
        totalCountLabel->setObjectName(QStringLiteral("totalCountLabel"));

        horizontalLayout_9->addWidget(totalCountLabel);

        totalCountValueLabel = new QLabel(pagingFrame);
        totalCountValueLabel->setObjectName(QStringLiteral("totalCountValueLabel"));
        totalCountValueLabel->setMinimumSize(QSize(100, 0));
        totalCountValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_9->addWidget(totalCountValueLabel);

        prevPagePushButton = new QPushButton(pagingFrame);
        prevPagePushButton->setObjectName(QStringLiteral("prevPagePushButton"));

        horizontalLayout_9->addWidget(prevPagePushButton);

        pageInfoLabel = new QLabel(pagingFrame);
        pageInfoLabel->setObjectName(QStringLiteral("pageInfoLabel"));
        pageInfoLabel->setText(QStringLiteral("X / Y"));

        horizontalLayout_9->addWidget(pageInfoLabel);

        nextPagePushButton = new QPushButton(pagingFrame);
        nextPagePushButton->setObjectName(QStringLiteral("nextPagePushButton"));

        horizontalLayout_9->addWidget(nextPagePushButton);


        verticalLayout_4->addWidget(pagingFrame);

        invoicesTableWidget = new QTableWidget(resultsFrame);
        invoicesTableWidget->setObjectName(QStringLiteral("invoicesTableWidget"));
        invoicesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        invoicesTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        invoicesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        invoicesTableWidget->verticalHeader()->setVisible(false);
        invoicesTableWidget->verticalHeader()->setDefaultSectionSize(50);
        invoicesTableWidget->verticalHeader()->setMinimumSectionSize(50);

        verticalLayout_4->addWidget(invoicesTableWidget);


        horizontalLayout_4->addWidget(resultsFrame);


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
        fromDateResultLabel->setText(QApplication::translate("InvoiceListWindow", "From:", 0));
        fromDateResultValueLabel->setText(QApplication::translate("InvoiceListWindow", "10-10-2015", 0));
        toDateResultLabel->setText(QApplication::translate("InvoiceListWindow", "To:", 0));
        toDateResultValueLabel->setText(QApplication::translate("InvoiceListWindow", "10-10-2015", 0));
        totalInvoicesLabel->setText(QApplication::translate("InvoiceListWindow", "Total Invoices:", 0));
        totalInvoicesValueLabel->setText(QApplication::translate("InvoiceListWindow", "0", 0));
        totalCountLabel->setText(QApplication::translate("InvoiceListWindow", "Total:", 0));
        totalCountValueLabel->setText(QApplication::translate("InvoiceListWindow", "0 \342\202\254", 0));
        prevPagePushButton->setText(QApplication::translate("InvoiceListWindow", "<", 0));
        nextPagePushButton->setText(QApplication::translate("InvoiceListWindow", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class InvoiceListWindow: public Ui_InvoiceListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICELISTWINDOW_H
