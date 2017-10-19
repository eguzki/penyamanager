/********************************************************************************
** Form generated from reading UI file 'accountbalanceview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTBALANCEVIEW_H
#define UI_ACCOUNTBALANCEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
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

class Ui_AccountBalanceView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *searchPushButton;
    QFrame *searchFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *dateFrame;
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *fromCalendarWidget;
    QCalendarWidget *toCalendarWidget;
    QFrame *memberFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *memberIdLabel;
    QLineEdit *memberIdLineEdit;
    QPushButton *clearPushButton;
    QSpacerItem *horizontalSpacer;
    QFrame *resultsFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *pagingFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *fromDateResultLabel;
    QLabel *fromDateResultValueLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *toDateResultLabel;
    QLabel *toDateResultValueLabel;
    QSpacerItem *horizontalSpacer_3;
    QLabel *memberIdResLabel;
    QLabel *memberIdResValueLabel;
    QSpacerItem *horizontalSpacer_9;
    QLabel *totalRowsLabel;
    QLabel *totalRowsValueLabel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *prevPagePushButton;
    QLabel *pageInfoLabel;
    QPushButton *nextPagePushButton;
    QFrame *transactionsFrame;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *transactionsTableWidget;
    QGroupBox *totalsGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *totalDepositsLabel;
    QLabel *totalDepositsValueLabel;
    QSpacerItem *horizontalSpacer_7;
    QLabel *totalInvoicesLabel;
    QLabel *totalInvoicesValueLabel;
    QSpacerItem *horizontalSpacer_8;
    QLabel *totalBankChargesLabel;
    QLabel *totalBankChargesValueLabel;

    void setupUi(QWidget *AccountBalanceView)
    {
        if (AccountBalanceView->objectName().isEmpty())
            AccountBalanceView->setObjectName(QStringLiteral("AccountBalanceView"));
        AccountBalanceView->resize(1200, 1000);
        AccountBalanceView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(AccountBalanceView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(AccountBalanceView);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy);
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(topFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        titleLabel = new QLabel(topFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout_3->addWidget(titleLabel);

        horizontalSpacer_2 = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        searchPushButton = new QPushButton(topFrame);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));

        horizontalLayout_3->addWidget(searchPushButton);


        verticalLayout->addWidget(topFrame);

        searchFrame = new QFrame(AccountBalanceView);
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
        memberIdLabel = new QLabel(memberFrame);
        memberIdLabel->setObjectName(QStringLiteral("memberIdLabel"));

        horizontalLayout_2->addWidget(memberIdLabel);

        memberIdLineEdit = new QLineEdit(memberFrame);
        memberIdLineEdit->setObjectName(QStringLiteral("memberIdLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(memberIdLineEdit->sizePolicy().hasHeightForWidth());
        memberIdLineEdit->setSizePolicy(sizePolicy1);
        memberIdLineEdit->setMinimumSize(QSize(100, 0));
        memberIdLineEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(memberIdLineEdit);

        clearPushButton = new QPushButton(memberFrame);
        clearPushButton->setObjectName(QStringLiteral("clearPushButton"));

        horizontalLayout_2->addWidget(clearPushButton);

        horizontalSpacer = new QSpacerItem(862, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(memberFrame);


        verticalLayout->addWidget(searchFrame);

        resultsFrame = new QFrame(AccountBalanceView);
        resultsFrame->setObjectName(QStringLiteral("resultsFrame"));
        resultsFrame->setFrameShape(QFrame::StyledPanel);
        resultsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(resultsFrame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pagingFrame = new QFrame(resultsFrame);
        pagingFrame->setObjectName(QStringLiteral("pagingFrame"));
        pagingFrame->setFrameShape(QFrame::StyledPanel);
        pagingFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(pagingFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        fromDateResultLabel = new QLabel(pagingFrame);
        fromDateResultLabel->setObjectName(QStringLiteral("fromDateResultLabel"));

        horizontalLayout_4->addWidget(fromDateResultLabel);

        fromDateResultValueLabel = new QLabel(pagingFrame);
        fromDateResultValueLabel->setObjectName(QStringLiteral("fromDateResultValueLabel"));
        fromDateResultValueLabel->setMinimumSize(QSize(100, 0));
        fromDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(fromDateResultValueLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        toDateResultLabel = new QLabel(pagingFrame);
        toDateResultLabel->setObjectName(QStringLiteral("toDateResultLabel"));

        horizontalLayout_4->addWidget(toDateResultLabel);

        toDateResultValueLabel = new QLabel(pagingFrame);
        toDateResultValueLabel->setObjectName(QStringLiteral("toDateResultValueLabel"));
        toDateResultValueLabel->setMinimumSize(QSize(100, 0));
        toDateResultValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(toDateResultValueLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        memberIdResLabel = new QLabel(pagingFrame);
        memberIdResLabel->setObjectName(QStringLiteral("memberIdResLabel"));

        horizontalLayout_4->addWidget(memberIdResLabel);

        memberIdResValueLabel = new QLabel(pagingFrame);
        memberIdResValueLabel->setObjectName(QStringLiteral("memberIdResValueLabel"));
        memberIdResValueLabel->setMinimumSize(QSize(100, 0));
        memberIdResValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(memberIdResValueLabel);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        totalRowsLabel = new QLabel(pagingFrame);
        totalRowsLabel->setObjectName(QStringLiteral("totalRowsLabel"));

        horizontalLayout_4->addWidget(totalRowsLabel);

        totalRowsValueLabel = new QLabel(pagingFrame);
        totalRowsValueLabel->setObjectName(QStringLiteral("totalRowsValueLabel"));
        totalRowsValueLabel->setMinimumSize(QSize(100, 0));
        totalRowsValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(totalRowsValueLabel);

        horizontalSpacer_6 = new QSpacerItem(376, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        prevPagePushButton = new QPushButton(pagingFrame);
        prevPagePushButton->setObjectName(QStringLiteral("prevPagePushButton"));

        horizontalLayout_4->addWidget(prevPagePushButton);

        pageInfoLabel = new QLabel(pagingFrame);
        pageInfoLabel->setObjectName(QStringLiteral("pageInfoLabel"));

        horizontalLayout_4->addWidget(pageInfoLabel);

        nextPagePushButton = new QPushButton(pagingFrame);
        nextPagePushButton->setObjectName(QStringLiteral("nextPagePushButton"));

        horizontalLayout_4->addWidget(nextPagePushButton);


        verticalLayout_3->addWidget(pagingFrame);

        transactionsFrame = new QFrame(resultsFrame);
        transactionsFrame->setObjectName(QStringLiteral("transactionsFrame"));
        transactionsFrame->setFrameShape(QFrame::StyledPanel);
        transactionsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(transactionsFrame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        transactionsTableWidget = new QTableWidget(transactionsFrame);
        transactionsTableWidget->setObjectName(QStringLiteral("transactionsTableWidget"));
        transactionsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        transactionsTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        transactionsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        transactionsTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(transactionsTableWidget);


        verticalLayout_3->addWidget(transactionsFrame);

        totalsGroupBox = new QGroupBox(resultsFrame);
        totalsGroupBox->setObjectName(QStringLiteral("totalsGroupBox"));
        horizontalLayout_5 = new QHBoxLayout(totalsGroupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        totalDepositsLabel = new QLabel(totalsGroupBox);
        totalDepositsLabel->setObjectName(QStringLiteral("totalDepositsLabel"));

        horizontalLayout_5->addWidget(totalDepositsLabel);

        totalDepositsValueLabel = new QLabel(totalsGroupBox);
        totalDepositsValueLabel->setObjectName(QStringLiteral("totalDepositsValueLabel"));
        totalDepositsValueLabel->setMinimumSize(QSize(100, 0));
        totalDepositsValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(totalDepositsValueLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        totalInvoicesLabel = new QLabel(totalsGroupBox);
        totalInvoicesLabel->setObjectName(QStringLiteral("totalInvoicesLabel"));

        horizontalLayout_5->addWidget(totalInvoicesLabel);

        totalInvoicesValueLabel = new QLabel(totalsGroupBox);
        totalInvoicesValueLabel->setObjectName(QStringLiteral("totalInvoicesValueLabel"));
        totalInvoicesValueLabel->setMinimumSize(QSize(100, 0));
        totalInvoicesValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(totalInvoicesValueLabel);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        totalBankChargesLabel = new QLabel(totalsGroupBox);
        totalBankChargesLabel->setObjectName(QStringLiteral("totalBankChargesLabel"));

        horizontalLayout_5->addWidget(totalBankChargesLabel);

        totalBankChargesValueLabel = new QLabel(totalsGroupBox);
        totalBankChargesValueLabel->setObjectName(QStringLiteral("totalBankChargesValueLabel"));
        totalBankChargesValueLabel->setMinimumSize(QSize(100, 0));
        totalBankChargesValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(totalBankChargesValueLabel);


        verticalLayout_3->addWidget(totalsGroupBox);


        verticalLayout->addWidget(resultsFrame);


        retranslateUi(AccountBalanceView);

        QMetaObject::connectSlotsByName(AccountBalanceView);
    } // setupUi

    void retranslateUi(QWidget *AccountBalanceView)
    {
        AccountBalanceView->setWindowTitle(QApplication::translate("AccountBalanceView", "Form", 0));
        titleLabel->setText(QApplication::translate("AccountBalanceView", "Total Account Balance", 0));
        searchPushButton->setText(QApplication::translate("AccountBalanceView", "Search", 0));
        memberIdLabel->setText(QApplication::translate("AccountBalanceView", "Username", 0));
        clearPushButton->setText(QApplication::translate("AccountBalanceView", "clear", 0));
        fromDateResultLabel->setText(QApplication::translate("AccountBalanceView", "From:", 0));
        fromDateResultValueLabel->setText(QApplication::translate("AccountBalanceView", "10-10-2015", 0));
        toDateResultLabel->setText(QApplication::translate("AccountBalanceView", "To:", 0));
        toDateResultValueLabel->setText(QApplication::translate("AccountBalanceView", "10-10-2015", 0));
        memberIdResLabel->setText(QApplication::translate("AccountBalanceView", "Username", 0));
        memberIdResValueLabel->setText(QApplication::translate("AccountBalanceView", "0", 0));
        totalRowsLabel->setText(QApplication::translate("AccountBalanceView", "Rows:", 0));
        totalRowsValueLabel->setText(QApplication::translate("AccountBalanceView", "0", 0));
        prevPagePushButton->setText(QApplication::translate("AccountBalanceView", "<", 0));
        pageInfoLabel->setText(QApplication::translate("AccountBalanceView", "page X out of Y", 0));
        nextPagePushButton->setText(QApplication::translate("AccountBalanceView", ">", 0));
        totalsGroupBox->setTitle(QApplication::translate("AccountBalanceView", "Totals", 0));
        totalDepositsLabel->setText(QApplication::translate("AccountBalanceView", "Deposits: ", 0));
        totalDepositsValueLabel->setText(QApplication::translate("AccountBalanceView", "0 \342\202\254", 0));
        totalInvoicesLabel->setText(QApplication::translate("AccountBalanceView", "Invoices:", 0));
        totalInvoicesValueLabel->setText(QApplication::translate("AccountBalanceView", "0 \342\202\254", 0));
        totalBankChargesLabel->setText(QApplication::translate("AccountBalanceView", "Banc Account:", 0));
        totalBankChargesValueLabel->setText(QApplication::translate("AccountBalanceView", "0 \342\202\254", 0));
    } // retranslateUi

};

namespace Ui {
    class AccountBalanceView: public Ui_AccountBalanceView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTBALANCEVIEW_H
