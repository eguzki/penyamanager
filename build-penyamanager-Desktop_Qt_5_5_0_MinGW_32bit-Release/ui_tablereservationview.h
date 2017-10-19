/********************************************************************************
** Form generated from reading UI file 'tablereservationview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLERESERVATIONVIEW_H
#define UI_TABLERESERVATIONVIEW_H

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

class Ui_TableReservationView
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *searchWidget;
    QVBoxLayout *verticalLayout_2;
    QCalendarWidget *calendarWidget;
    QPushButton *lunchButton;
    QPushButton *dinnerButton;
    QTableWidget *tableReservationTableWidget;
    QButtonGroup *reservationTypeButtonGroup;

    void setupUi(QWidget *TableReservationView)
    {
        if (TableReservationView->objectName().isEmpty())
            TableReservationView->setObjectName(QStringLiteral("TableReservationView"));
        TableReservationView->resize(1024, 768);
        verticalLayout = new QVBoxLayout(TableReservationView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelWidget = new QWidget(TableReservationView);
        topPanelWidget->setObjectName(QStringLiteral("topPanelWidget"));
        topPanelWidget->setMinimumSize(QSize(0, 150));
        topPanelWidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout = new QHBoxLayout(topPanelWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        backButton = new QPushButton(topPanelWidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(backButton);


        verticalLayout->addWidget(topPanelWidget);

        widget = new QWidget(TableReservationView);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        searchWidget = new QWidget(widget);
        searchWidget->setObjectName(QStringLiteral("searchWidget"));
        searchWidget->setMinimumSize(QSize(0, 0));
        searchWidget->setMaximumSize(QSize(450, 16777215));
        searchWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_2 = new QVBoxLayout(searchWidget);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        calendarWidget = new QCalendarWidget(searchWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(0, 300));
        calendarWidget->setMaximumSize(QSize(16777215, 16777215));
        calendarWidget->setGridVisible(true);
        calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        verticalLayout_2->addWidget(calendarWidget);

        lunchButton = new QPushButton(searchWidget);
        reservationTypeButtonGroup = new QButtonGroup(TableReservationView);
        reservationTypeButtonGroup->setObjectName(QStringLiteral("reservationTypeButtonGroup"));
        reservationTypeButtonGroup->addButton(lunchButton);
        lunchButton->setObjectName(QStringLiteral("lunchButton"));
        sizePolicy.setHeightForWidth(lunchButton->sizePolicy().hasHeightForWidth());
        lunchButton->setSizePolicy(sizePolicy);
        lunchButton->setMinimumSize(QSize(0, 0));
        lunchButton->setMaximumSize(QSize(16777215, 16777215));
        lunchButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(lunchButton);

        dinnerButton = new QPushButton(searchWidget);
        reservationTypeButtonGroup->addButton(dinnerButton);
        dinnerButton->setObjectName(QStringLiteral("dinnerButton"));
        sizePolicy.setHeightForWidth(dinnerButton->sizePolicy().hasHeightForWidth());
        dinnerButton->setSizePolicy(sizePolicy);
        dinnerButton->setMinimumSize(QSize(0, 0));
        dinnerButton->setMaximumSize(QSize(16777215, 16777215));
        dinnerButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(dinnerButton);


        horizontalLayout_2->addWidget(searchWidget);

        tableReservationTableWidget = new QTableWidget(widget);
        tableReservationTableWidget->setObjectName(QStringLiteral("tableReservationTableWidget"));
        tableReservationTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableReservationTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableReservationTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableReservationTableWidget->verticalHeader()->setVisible(false);

        horizontalLayout_2->addWidget(tableReservationTableWidget);


        verticalLayout->addWidget(widget);


        retranslateUi(TableReservationView);

        QMetaObject::connectSlotsByName(TableReservationView);
    } // setupUi

    void retranslateUi(QWidget *TableReservationView)
    {
        TableReservationView->setWindowTitle(QApplication::translate("TableReservationView", "Reservations", 0));
        backButton->setText(QApplication::translate("TableReservationView", "Back", 0));
        lunchButton->setText(QApplication::translate("TableReservationView", "Lunch", 0));
        dinnerButton->setText(QApplication::translate("TableReservationView", "Diner", 0));
    } // retranslateUi

};

namespace Ui {
    class TableReservationView: public Ui_TableReservationView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLERESERVATIONVIEW_H
