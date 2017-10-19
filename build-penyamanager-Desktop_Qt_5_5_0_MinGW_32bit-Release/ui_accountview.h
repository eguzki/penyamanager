/********************************************************************************
** Form generated from reading UI file 'accountview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTVIEW_H
#define UI_ACCOUNTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountView
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelwidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *backPushButton;
    QPushButton *searchButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *calendarWidget;
    QVBoxLayout *verticalLayout_2;
    QCalendarWidget *fromCalendarWidget;
    QCalendarWidget *toCalendarWidget;
    QTableWidget *accountTableWidget;

    void setupUi(QWidget *AccountView)
    {
        if (AccountView->objectName().isEmpty())
            AccountView->setObjectName(QStringLiteral("AccountView"));
        AccountView->resize(1024, 768);
        verticalLayout = new QVBoxLayout(AccountView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelwidget = new QWidget(AccountView);
        topPanelwidget->setObjectName(QStringLiteral("topPanelwidget"));
        topPanelwidget->setMinimumSize(QSize(0, 150));
        topPanelwidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout_4 = new QHBoxLayout(topPanelwidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        backPushButton = new QPushButton(topPanelwidget);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(backPushButton->sizePolicy().hasHeightForWidth());
        backPushButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(backPushButton);

        searchButton = new QPushButton(topPanelwidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        sizePolicy.setHeightForWidth(searchButton->sizePolicy().hasHeightForWidth());
        searchButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(searchButton);


        verticalLayout->addWidget(topPanelwidget);

        widget = new QWidget(AccountView);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        calendarWidget = new QWidget(widget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMaximumSize(QSize(450, 16777215));
        verticalLayout_2 = new QVBoxLayout(calendarWidget);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        fromCalendarWidget = new QCalendarWidget(calendarWidget);
        fromCalendarWidget->setObjectName(QStringLiteral("fromCalendarWidget"));
        fromCalendarWidget->setMinimumSize(QSize(450, 0));
        fromCalendarWidget->setMaximumSize(QSize(400, 16777215));
        fromCalendarWidget->setGridVisible(true);
        fromCalendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        fromCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        fromCalendarWidget->setDateEditEnabled(false);

        verticalLayout_2->addWidget(fromCalendarWidget);

        toCalendarWidget = new QCalendarWidget(calendarWidget);
        toCalendarWidget->setObjectName(QStringLiteral("toCalendarWidget"));
        toCalendarWidget->setMinimumSize(QSize(450, 0));
        toCalendarWidget->setMaximumSize(QSize(400, 16777215));
        toCalendarWidget->setGridVisible(true);
        toCalendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        toCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        toCalendarWidget->setDateEditEnabled(false);

        verticalLayout_2->addWidget(toCalendarWidget);


        horizontalLayout->addWidget(calendarWidget);

        accountTableWidget = new QTableWidget(widget);
        accountTableWidget->setObjectName(QStringLiteral("accountTableWidget"));
        accountTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        accountTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        accountTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        accountTableWidget->verticalHeader()->setVisible(false);
        accountTableWidget->verticalHeader()->setDefaultSectionSize(50);
        accountTableWidget->verticalHeader()->setMinimumSectionSize(50);

        horizontalLayout->addWidget(accountTableWidget);


        verticalLayout->addWidget(widget);


        retranslateUi(AccountView);

        QMetaObject::connectSlotsByName(AccountView);
    } // setupUi

    void retranslateUi(QWidget *AccountView)
    {
        AccountView->setWindowTitle(QApplication::translate("AccountView", "Account View", 0));
        backPushButton->setText(QApplication::translate("AccountView", "Back", 0));
        searchButton->setText(QApplication::translate("AccountView", "Search", 0));
    } // retranslateUi

};

namespace Ui {
    class AccountView: public Ui_AccountView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTVIEW_H
