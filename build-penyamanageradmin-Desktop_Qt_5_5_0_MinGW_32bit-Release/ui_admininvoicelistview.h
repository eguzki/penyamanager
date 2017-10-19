/********************************************************************************
** Form generated from reading UI file 'admininvoicelistview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMININVOICELISTVIEW_H
#define UI_ADMININVOICELISTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminInvoiceListView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_6;
    QLabel *memberIdLabel;
    QLineEdit *memberIdLineEdit;
    QPushButton *clearPushButton;
    QPushButton *searchPushButton;
    QFrame *searchFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *dateFrame;
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *fromCalendarWidget;
    QCalendarWidget *toCalendarWidget;
    QFrame *resultsFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *pagingFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *fromDateResultLabel;
    QLabel *fromDateResultValueLabel;
    QSpacerItem *horizontalSpacer_4;
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
    QFrame *invoiceFrame;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *invoicesTableWidget;

    void setupUi(QWidget *AdminInvoiceListView)
    {
        if (AdminInvoiceListView->objectName().isEmpty())
            AdminInvoiceListView->setObjectName(QStringLiteral("AdminInvoiceListView"));
        AdminInvoiceListView->resize(1200, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AdminInvoiceListView->sizePolicy().hasHeightForWidth());
        AdminInvoiceListView->setSizePolicy(sizePolicy);
        AdminInvoiceListView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(AdminInvoiceListView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(AdminInvoiceListView);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        sizePolicy.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy);
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(topFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        titleLabel = new QLabel(topFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout_4->addWidget(titleLabel);

        horizontalSpacer_6 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        memberIdLabel = new QLabel(topFrame);
        memberIdLabel->setObjectName(QStringLiteral("memberIdLabel"));

        horizontalLayout_4->addWidget(memberIdLabel);

        memberIdLineEdit = new QLineEdit(topFrame);
        memberIdLineEdit->setObjectName(QStringLiteral("memberIdLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(memberIdLineEdit->sizePolicy().hasHeightForWidth());
        memberIdLineEdit->setSizePolicy(sizePolicy1);
        memberIdLineEdit->setMinimumSize(QSize(100, 0));
        memberIdLineEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(memberIdLineEdit);

        clearPushButton = new QPushButton(topFrame);
        clearPushButton->setObjectName(QStringLiteral("clearPushButton"));

        horizontalLayout_4->addWidget(clearPushButton);

        searchPushButton = new QPushButton(topFrame);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));

        horizontalLayout_4->addWidget(searchPushButton);


        verticalLayout->addWidget(topFrame);

        searchFrame = new QFrame(AdminInvoiceListView);
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


        verticalLayout->addWidget(searchFrame);

        resultsFrame = new QFrame(AdminInvoiceListView);
        resultsFrame->setObjectName(QStringLiteral("resultsFrame"));
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
        fromDateResultLabel->setMinimumSize(QSize(50, 0));
        fromDateResultLabel->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(fromDateResultLabel);

        fromDateResultValueLabel = new QLabel(pagingFrame);
        fromDateResultValueLabel->setObjectName(QStringLiteral("fromDateResultValueLabel"));
        fromDateResultValueLabel->setMinimumSize(QSize(100, 0));
        fromDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(fromDateResultValueLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        toDateResultLabel = new QLabel(pagingFrame);
        toDateResultLabel->setObjectName(QStringLiteral("toDateResultLabel"));
        toDateResultLabel->setMinimumSize(QSize(50, 0));
        toDateResultLabel->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(toDateResultLabel);

        toDateResultValueLabel = new QLabel(pagingFrame);
        toDateResultValueLabel->setObjectName(QStringLiteral("toDateResultValueLabel"));
        toDateResultValueLabel->setMinimumSize(QSize(100, 0));
        toDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(toDateResultValueLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        totalInvoicesLabel = new QLabel(pagingFrame);
        totalInvoicesLabel->setObjectName(QStringLiteral("totalInvoicesLabel"));

        horizontalLayout_3->addWidget(totalInvoicesLabel);

        totalInvoicesValueLabel = new QLabel(pagingFrame);
        totalInvoicesValueLabel->setObjectName(QStringLiteral("totalInvoicesValueLabel"));
        totalInvoicesValueLabel->setMinimumSize(QSize(50, 0));
        totalInvoicesValueLabel->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(totalInvoicesValueLabel);

        totalCountLabel = new QLabel(pagingFrame);
        totalCountLabel->setObjectName(QStringLiteral("totalCountLabel"));

        horizontalLayout_3->addWidget(totalCountLabel);

        totalCountValueLabel = new QLabel(pagingFrame);
        totalCountValueLabel->setObjectName(QStringLiteral("totalCountValueLabel"));
        totalCountValueLabel->setMinimumSize(QSize(100, 0));
        totalCountValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(totalCountValueLabel);

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
        invoicesTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        invoicesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        invoicesTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(invoicesTableWidget);


        verticalLayout_3->addWidget(invoiceFrame);


        verticalLayout->addWidget(resultsFrame);


        retranslateUi(AdminInvoiceListView);

        QMetaObject::connectSlotsByName(AdminInvoiceListView);
    } // setupUi

    void retranslateUi(QWidget *AdminInvoiceListView)
    {
        AdminInvoiceListView->setWindowTitle(QApplication::translate("AdminInvoiceListView", "Form", 0));
        titleLabel->setText(QApplication::translate("AdminInvoiceListView", "Invoice List", 0));
        memberIdLabel->setText(QApplication::translate("AdminInvoiceListView", "Username", 0));
        clearPushButton->setText(QApplication::translate("AdminInvoiceListView", "clear", 0));
        searchPushButton->setText(QApplication::translate("AdminInvoiceListView", "Search", 0));
        fromDateResultLabel->setText(QApplication::translate("AdminInvoiceListView", "From:", 0));
        fromDateResultValueLabel->setText(QApplication::translate("AdminInvoiceListView", "10-10-2015", 0));
        toDateResultLabel->setText(QApplication::translate("AdminInvoiceListView", "To:", 0));
        toDateResultValueLabel->setText(QApplication::translate("AdminInvoiceListView", "10-10-2015", 0));
        totalInvoicesLabel->setText(QApplication::translate("AdminInvoiceListView", "Total Invoices:", 0));
        totalInvoicesValueLabel->setText(QApplication::translate("AdminInvoiceListView", "0", 0));
        totalCountLabel->setText(QApplication::translate("AdminInvoiceListView", "Total:", 0));
        totalCountValueLabel->setText(QApplication::translate("AdminInvoiceListView", "0 \342\202\254", 0));
        prevPagePushButton->setText(QApplication::translate("AdminInvoiceListView", "<", 0));
        pageInfoLabel->setText(QApplication::translate("AdminInvoiceListView", "page X out of Y", 0));
        nextPagePushButton->setText(QApplication::translate("AdminInvoiceListView", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminInvoiceListView: public Ui_AdminInvoiceListView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMININVOICELISTVIEW_H
