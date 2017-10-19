/********************************************************************************
** Form generated from reading UI file 'depositlistview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSITLISTVIEW_H
#define UI_DEPOSITLISTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DepositListView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *depositTableWidget;

    void setupUi(QWidget *DepositListView)
    {
        if (DepositListView->objectName().isEmpty())
            DepositListView->setObjectName(QStringLiteral("DepositListView"));
        DepositListView->resize(800, 600);
        DepositListView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(DepositListView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(DepositListView);
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


        verticalLayout->addWidget(topFrame);

        depositTableWidget = new QTableWidget(DepositListView);
        depositTableWidget->setObjectName(QStringLiteral("depositTableWidget"));
        depositTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        depositTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        depositTableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(depositTableWidget);


        retranslateUi(DepositListView);

        QMetaObject::connectSlotsByName(DepositListView);
    } // setupUi

    void retranslateUi(QWidget *DepositListView)
    {
        DepositListView->setWindowTitle(QApplication::translate("DepositListView", "Form", 0));
        titleLabel->setText(QApplication::translate("DepositListView", "Deposit List", 0));
    } // retranslateUi

};

namespace Ui {
    class DepositListView: public Ui_DepositListView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSITLISTVIEW_H
