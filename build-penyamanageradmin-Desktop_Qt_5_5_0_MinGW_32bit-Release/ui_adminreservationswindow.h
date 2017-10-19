/********************************************************************************
** Form generated from reading UI file 'adminreservationswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINRESERVATIONSWINDOW_H
#define UI_ADMINRESERVATIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminReservationsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *searchWidget;
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *calendarWidget;
    QSpacerItem *horizontalSpacer;
    QPushButton *lunchButton;
    QPushButton *dinnerButton;
    QTableWidget *tableReservationTableWidget;
    QButtonGroup *reservationTypeButtonGroup;

    void setupUi(QWidget *AdminReservationsWindow)
    {
        if (AdminReservationsWindow->objectName().isEmpty())
            AdminReservationsWindow->setObjectName(QStringLiteral("AdminReservationsWindow"));
        AdminReservationsWindow->resize(1280, 1024);
        AdminReservationsWindow->setMinimumSize(QSize(1280, 1024));
        AdminReservationsWindow->setMaximumSize(QSize(1280, 1024));
        AdminReservationsWindow->setWindowTitle(QStringLiteral("Reservations"));
        AdminReservationsWindow->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(AdminReservationsWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        searchWidget = new QWidget(AdminReservationsWindow);
        searchWidget->setObjectName(QStringLiteral("searchWidget"));
        searchWidget->setMinimumSize(QSize(0, 300));
        searchWidget->setMaximumSize(QSize(16777215, 300));
        horizontalLayout = new QHBoxLayout(searchWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        calendarWidget = new QCalendarWidget(searchWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(0, 0));
        calendarWidget->setMaximumSize(QSize(16777215, 16777215));
        calendarWidget->setGridVisible(true);
        calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout->addWidget(calendarWidget);

        horizontalSpacer = new QSpacerItem(460, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lunchButton = new QPushButton(searchWidget);
        reservationTypeButtonGroup = new QButtonGroup(AdminReservationsWindow);
        reservationTypeButtonGroup->setObjectName(QStringLiteral("reservationTypeButtonGroup"));
        reservationTypeButtonGroup->addButton(lunchButton);
        lunchButton->setObjectName(QStringLiteral("lunchButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lunchButton->sizePolicy().hasHeightForWidth());
        lunchButton->setSizePolicy(sizePolicy);
        lunchButton->setMinimumSize(QSize(150, 0));
        lunchButton->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(lunchButton);

        dinnerButton = new QPushButton(searchWidget);
        reservationTypeButtonGroup->addButton(dinnerButton);
        dinnerButton->setObjectName(QStringLiteral("dinnerButton"));
        sizePolicy.setHeightForWidth(dinnerButton->sizePolicy().hasHeightForWidth());
        dinnerButton->setSizePolicy(sizePolicy);
        dinnerButton->setMinimumSize(QSize(150, 0));
        dinnerButton->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(dinnerButton);


        verticalLayout->addWidget(searchWidget);

        tableReservationTableWidget = new QTableWidget(AdminReservationsWindow);
        tableReservationTableWidget->setObjectName(QStringLiteral("tableReservationTableWidget"));
        tableReservationTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableReservationTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableReservationTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableReservationTableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableReservationTableWidget);


        retranslateUi(AdminReservationsWindow);

        QMetaObject::connectSlotsByName(AdminReservationsWindow);
    } // setupUi

    void retranslateUi(QWidget *AdminReservationsWindow)
    {
        lunchButton->setText(QApplication::translate("AdminReservationsWindow", "Lunch", 0));
        dinnerButton->setText(QApplication::translate("AdminReservationsWindow", "Diner", 0));
        Q_UNUSED(AdminReservationsWindow);
    } // retranslateUi

};

namespace Ui {
    class AdminReservationsWindow: public Ui_AdminReservationsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINRESERVATIONSWINDOW_H
