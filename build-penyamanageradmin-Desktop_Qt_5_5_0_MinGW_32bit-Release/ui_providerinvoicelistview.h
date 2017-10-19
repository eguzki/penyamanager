/********************************************************************************
** Form generated from reading UI file 'providerinvoicelistview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVIDERINVOICELISTVIEW_H
#define UI_PROVIDERINVOICELISTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
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

class Ui_ProviderInvoiceListView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *searchPushButton;
    QFrame *searchFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *dateFrame;
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *fromCalendarWidget;
    QCalendarWidget *toCalendarWidget;
    QFrame *memberFrame;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *providerComboBox;
    QSpacerItem *horizontalSpacer;
    QFrame *resultsFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *pagingFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *fromDateResultLabel;
    QLabel *fromDateResultValueLabel;
    QLabel *toDateResultLabel;
    QLabel *toDateResultValueLabel;
    QLabel *totalInvoicesLabel;
    QLabel *totalInvoicesValueLabel;
    QLabel *totalCostLabel;
    QLabel *totalCostValueLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *prevPagePushButton;
    QLabel *pageInfoLabel;
    QPushButton *nextPagePushButton;
    QFrame *invoiceFrame;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *invoicesTableWidget;

    void setupUi(QWidget *ProviderInvoiceListView)
    {
        if (ProviderInvoiceListView->objectName().isEmpty())
            ProviderInvoiceListView->setObjectName(QStringLiteral("ProviderInvoiceListView"));
        ProviderInvoiceListView->resize(1200, 1000);
        ProviderInvoiceListView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(ProviderInvoiceListView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(ProviderInvoiceListView);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy);
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(topFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        titleLabel = new QLabel(topFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout_4->addWidget(titleLabel);

        horizontalSpacer_5 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        searchPushButton = new QPushButton(topFrame);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));

        horizontalLayout_4->addWidget(searchPushButton);


        verticalLayout->addWidget(topFrame);

        searchFrame = new QFrame(ProviderInvoiceListView);
        searchFrame->setObjectName(QStringLiteral("searchFrame"));
        sizePolicy.setHeightForWidth(searchFrame->sizePolicy().hasHeightForWidth());
        searchFrame->setSizePolicy(sizePolicy);
        searchFrame->setFrameShape(QFrame::StyledPanel);
        searchFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(searchFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        dateFrame = new QFrame(searchFrame);
        dateFrame->setObjectName(QStringLiteral("dateFrame"));
        dateFrame->setFrameShape(QFrame::StyledPanel);
        dateFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(dateFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fromCalendarWidget = new QCalendarWidget(dateFrame);
        fromCalendarWidget->setObjectName(QStringLiteral("fromCalendarWidget"));
        fromCalendarWidget->setGridVisible(true);
        fromCalendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        fromCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout->addWidget(fromCalendarWidget);

        toCalendarWidget = new QCalendarWidget(dateFrame);
        toCalendarWidget->setObjectName(QStringLiteral("toCalendarWidget"));
        toCalendarWidget->setGridVisible(true);
        toCalendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        toCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout->addWidget(toCalendarWidget);


        verticalLayout_2->addWidget(dateFrame);

        memberFrame = new QFrame(searchFrame);
        memberFrame->setObjectName(QStringLiteral("memberFrame"));
        memberFrame->setFrameShape(QFrame::StyledPanel);
        memberFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(memberFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        providerComboBox = new QComboBox(memberFrame);
        providerComboBox->setObjectName(QStringLiteral("providerComboBox"));

        horizontalLayout_2->addWidget(providerComboBox);

        horizontalSpacer = new QSpacerItem(862, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(memberFrame);


        verticalLayout->addWidget(searchFrame);

        resultsFrame = new QFrame(ProviderInvoiceListView);
        resultsFrame->setObjectName(QStringLiteral("resultsFrame"));
        resultsFrame->setStyleSheet(QStringLiteral(""));
        resultsFrame->setFrameShape(QFrame::StyledPanel);
        resultsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(resultsFrame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pagingFrame = new QFrame(resultsFrame);
        pagingFrame->setObjectName(QStringLiteral("pagingFrame"));
        pagingFrame->setFrameShape(QFrame::StyledPanel);
        pagingFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(pagingFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        fromDateResultLabel = new QLabel(pagingFrame);
        fromDateResultLabel->setObjectName(QStringLiteral("fromDateResultLabel"));

        horizontalLayout_3->addWidget(fromDateResultLabel);

        fromDateResultValueLabel = new QLabel(pagingFrame);
        fromDateResultValueLabel->setObjectName(QStringLiteral("fromDateResultValueLabel"));
        fromDateResultValueLabel->setMinimumSize(QSize(150, 0));
        fromDateResultValueLabel->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_3->addWidget(fromDateResultValueLabel);

        toDateResultLabel = new QLabel(pagingFrame);
        toDateResultLabel->setObjectName(QStringLiteral("toDateResultLabel"));

        horizontalLayout_3->addWidget(toDateResultLabel);

        toDateResultValueLabel = new QLabel(pagingFrame);
        toDateResultValueLabel->setObjectName(QStringLiteral("toDateResultValueLabel"));
        toDateResultValueLabel->setMinimumSize(QSize(150, 0));
        toDateResultValueLabel->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_3->addWidget(toDateResultValueLabel);

        totalInvoicesLabel = new QLabel(pagingFrame);
        totalInvoicesLabel->setObjectName(QStringLiteral("totalInvoicesLabel"));

        horizontalLayout_3->addWidget(totalInvoicesLabel);

        totalInvoicesValueLabel = new QLabel(pagingFrame);
        totalInvoicesValueLabel->setObjectName(QStringLiteral("totalInvoicesValueLabel"));
        totalInvoicesValueLabel->setMinimumSize(QSize(100, 0));
        totalInvoicesValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(totalInvoicesValueLabel);

        totalCostLabel = new QLabel(pagingFrame);
        totalCostLabel->setObjectName(QStringLiteral("totalCostLabel"));

        horizontalLayout_3->addWidget(totalCostLabel);

        totalCostValueLabel = new QLabel(pagingFrame);
        totalCostValueLabel->setObjectName(QStringLiteral("totalCostValueLabel"));
        totalCostValueLabel->setMinimumSize(QSize(100, 0));
        totalCostValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(totalCostValueLabel);

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


        verticalLayout_3->addWidget(pagingFrame);

        invoiceFrame = new QFrame(resultsFrame);
        invoiceFrame->setObjectName(QStringLiteral("invoiceFrame"));
        invoiceFrame->setFrameShape(QFrame::StyledPanel);
        invoiceFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(invoiceFrame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        invoicesTableWidget = new QTableWidget(invoiceFrame);
        invoicesTableWidget->setObjectName(QStringLiteral("invoicesTableWidget"));
        invoicesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        invoicesTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        invoicesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        invoicesTableWidget->horizontalHeader()->setVisible(true);
        invoicesTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(invoicesTableWidget);


        verticalLayout_3->addWidget(invoiceFrame);


        verticalLayout->addWidget(resultsFrame);


        retranslateUi(ProviderInvoiceListView);

        QMetaObject::connectSlotsByName(ProviderInvoiceListView);
    } // setupUi

    void retranslateUi(QWidget *ProviderInvoiceListView)
    {
        ProviderInvoiceListView->setWindowTitle(QApplication::translate("ProviderInvoiceListView", "Form", 0));
        titleLabel->setText(QApplication::translate("ProviderInvoiceListView", "Provider Invoice List", 0));
        searchPushButton->setText(QApplication::translate("ProviderInvoiceListView", "Search", 0));
        fromDateResultLabel->setText(QApplication::translate("ProviderInvoiceListView", "From:", 0));
        fromDateResultValueLabel->setText(QApplication::translate("ProviderInvoiceListView", "10-10-2015", 0));
        toDateResultLabel->setText(QApplication::translate("ProviderInvoiceListView", "To:", 0));
        toDateResultValueLabel->setText(QApplication::translate("ProviderInvoiceListView", "10-10-2015", 0));
        totalInvoicesLabel->setText(QApplication::translate("ProviderInvoiceListView", "Total Invoices:", 0));
        totalInvoicesValueLabel->setText(QApplication::translate("ProviderInvoiceListView", "0", 0));
        totalCostLabel->setText(QApplication::translate("ProviderInvoiceListView", "Total:", 0));
        totalCostValueLabel->setText(QApplication::translate("ProviderInvoiceListView", "0", 0));
        prevPagePushButton->setText(QApplication::translate("ProviderInvoiceListView", "<", 0));
        pageInfoLabel->setText(QApplication::translate("ProviderInvoiceListView", "page X out of Y", 0));
        nextPagePushButton->setText(QApplication::translate("ProviderInvoiceListView", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class ProviderInvoiceListView: public Ui_ProviderInvoiceListView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDERINVOICELISTVIEW_H
