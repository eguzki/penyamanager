/********************************************************************************
** Form generated from reading UI file 'depositwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSITWINDOW_H
#define UI_DEPOSITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DepositWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *confirmButton;
    QWidget *depositWidget;
    QHBoxLayout *horizontalLayout_6;
    QWidget *numPadWidget1;
    QGridLayout *gridLayout;
    QPushButton *pushButton_01;
    QPushButton *pushButton_05;
    QPushButton *pushButton_07;
    QPushButton *pushButton_09;
    QPushButton *pushButton_04;
    QPushButton *pushButton_02;
    QPushButton *pushButton_03;
    QPushButton *pushButton_06;
    QPushButton *pushButton_08;
    QPushButton *pushButton_coma;
    QPushButton *pushButton_00;
    QPushButton *pushButton_C;
    QWidget *numPadDisplayWidget;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *depositLabel;
    QWidget *newBalanceWidget;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLabel *newBalanceLabel;

    void setupUi(QWidget *DepositWindow)
    {
        if (DepositWindow->objectName().isEmpty())
            DepositWindow->setObjectName(QStringLiteral("DepositWindow"));
        DepositWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DepositWindow->sizePolicy().hasHeightForWidth());
        DepositWindow->setSizePolicy(sizePolicy);
        DepositWindow->setStyleSheet(QLatin1String("#newBalanceLabel{\n"
"font: 30pt \"Calibri\";\n"
"}\n"
"\n"
"#depositLabel{\n"
"font: 30pt \"Calibri\";\n"
"}"));
        verticalLayout = new QVBoxLayout(DepositWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelWidget = new QWidget(DepositWindow);
        topPanelWidget->setObjectName(QStringLiteral("topPanelWidget"));
        topPanelWidget->setMinimumSize(QSize(0, 150));
        topPanelWidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout = new QHBoxLayout(topPanelWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        backButton = new QPushButton(topPanelWidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(backButton);

        confirmButton = new QPushButton(topPanelWidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        sizePolicy1.setHeightForWidth(confirmButton->sizePolicy().hasHeightForWidth());
        confirmButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(confirmButton);


        verticalLayout->addWidget(topPanelWidget);

        depositWidget = new QWidget(DepositWindow);
        depositWidget->setObjectName(QStringLiteral("depositWidget"));
        horizontalLayout_6 = new QHBoxLayout(depositWidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        numPadWidget1 = new QWidget(depositWidget);
        numPadWidget1->setObjectName(QStringLiteral("numPadWidget1"));
        numPadWidget1->setMinimumSize(QSize(366, 0));
        numPadWidget1->setMaximumSize(QSize(366, 16777215));
        gridLayout = new QGridLayout(numPadWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_01 = new QPushButton(numPadWidget1);
        pushButton_01->setObjectName(QStringLiteral("pushButton_01"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_01->sizePolicy().hasHeightForWidth());
        pushButton_01->setSizePolicy(sizePolicy2);
        pushButton_01->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_01, 0, 0, 1, 1);

        pushButton_05 = new QPushButton(numPadWidget1);
        pushButton_05->setObjectName(QStringLiteral("pushButton_05"));
        sizePolicy2.setHeightForWidth(pushButton_05->sizePolicy().hasHeightForWidth());
        pushButton_05->setSizePolicy(sizePolicy2);
        pushButton_05->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_05, 1, 1, 1, 1);

        pushButton_07 = new QPushButton(numPadWidget1);
        pushButton_07->setObjectName(QStringLiteral("pushButton_07"));
        sizePolicy2.setHeightForWidth(pushButton_07->sizePolicy().hasHeightForWidth());
        pushButton_07->setSizePolicy(sizePolicy2);
        pushButton_07->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_07, 2, 0, 1, 1);

        pushButton_09 = new QPushButton(numPadWidget1);
        pushButton_09->setObjectName(QStringLiteral("pushButton_09"));
        sizePolicy2.setHeightForWidth(pushButton_09->sizePolicy().hasHeightForWidth());
        pushButton_09->setSizePolicy(sizePolicy2);
        pushButton_09->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_09, 2, 2, 1, 1);

        pushButton_04 = new QPushButton(numPadWidget1);
        pushButton_04->setObjectName(QStringLiteral("pushButton_04"));
        sizePolicy2.setHeightForWidth(pushButton_04->sizePolicy().hasHeightForWidth());
        pushButton_04->setSizePolicy(sizePolicy2);
        pushButton_04->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_04, 1, 0, 1, 1);

        pushButton_02 = new QPushButton(numPadWidget1);
        pushButton_02->setObjectName(QStringLiteral("pushButton_02"));
        sizePolicy2.setHeightForWidth(pushButton_02->sizePolicy().hasHeightForWidth());
        pushButton_02->setSizePolicy(sizePolicy2);
        pushButton_02->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_02, 0, 1, 1, 1);

        pushButton_03 = new QPushButton(numPadWidget1);
        pushButton_03->setObjectName(QStringLiteral("pushButton_03"));
        sizePolicy2.setHeightForWidth(pushButton_03->sizePolicy().hasHeightForWidth());
        pushButton_03->setSizePolicy(sizePolicy2);
        pushButton_03->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_03, 0, 2, 1, 1);

        pushButton_06 = new QPushButton(numPadWidget1);
        pushButton_06->setObjectName(QStringLiteral("pushButton_06"));
        sizePolicy2.setHeightForWidth(pushButton_06->sizePolicy().hasHeightForWidth());
        pushButton_06->setSizePolicy(sizePolicy2);
        pushButton_06->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_06, 1, 2, 1, 1);

        pushButton_08 = new QPushButton(numPadWidget1);
        pushButton_08->setObjectName(QStringLiteral("pushButton_08"));
        sizePolicy2.setHeightForWidth(pushButton_08->sizePolicy().hasHeightForWidth());
        pushButton_08->setSizePolicy(sizePolicy2);
        pushButton_08->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_08, 2, 1, 1, 1);

        pushButton_coma = new QPushButton(numPadWidget1);
        pushButton_coma->setObjectName(QStringLiteral("pushButton_coma"));
        sizePolicy2.setHeightForWidth(pushButton_coma->sizePolicy().hasHeightForWidth());
        pushButton_coma->setSizePolicy(sizePolicy2);
        pushButton_coma->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_coma, 3, 0, 1, 1);

        pushButton_00 = new QPushButton(numPadWidget1);
        pushButton_00->setObjectName(QStringLiteral("pushButton_00"));
        sizePolicy2.setHeightForWidth(pushButton_00->sizePolicy().hasHeightForWidth());
        pushButton_00->setSizePolicy(sizePolicy2);
        pushButton_00->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_00, 3, 1, 1, 1);

        pushButton_C = new QPushButton(numPadWidget1);
        pushButton_C->setObjectName(QStringLiteral("pushButton_C"));
        sizePolicy2.setHeightForWidth(pushButton_C->sizePolicy().hasHeightForWidth());
        pushButton_C->setSizePolicy(sizePolicy2);
        pushButton_C->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(pushButton_C, 3, 2, 1, 1);


        horizontalLayout_6->addWidget(numPadWidget1);

        numPadDisplayWidget = new QWidget(depositWidget);
        numPadDisplayWidget->setObjectName(QStringLiteral("numPadDisplayWidget"));
        horizontalLayout_8 = new QHBoxLayout(numPadDisplayWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        label = new QLabel(numPadDisplayWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_8->addWidget(label);

        depositLabel = new QLabel(numPadDisplayWidget);
        depositLabel->setObjectName(QStringLiteral("depositLabel"));
        depositLabel->setMinimumSize(QSize(120, 0));

        horizontalLayout_8->addWidget(depositLabel);


        horizontalLayout_6->addWidget(numPadDisplayWidget);


        verticalLayout->addWidget(depositWidget);

        newBalanceWidget = new QWidget(DepositWindow);
        newBalanceWidget->setObjectName(QStringLiteral("newBalanceWidget"));
        horizontalLayout_7 = new QHBoxLayout(newBalanceWidget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        label_2 = new QLabel(newBalanceWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_7->addWidget(label_2);

        newBalanceLabel = new QLabel(newBalanceWidget);
        newBalanceLabel->setObjectName(QStringLiteral("newBalanceLabel"));
        newBalanceLabel->setMinimumSize(QSize(120, 0));

        horizontalLayout_7->addWidget(newBalanceLabel);


        verticalLayout->addWidget(newBalanceWidget);


        retranslateUi(DepositWindow);

        QMetaObject::connectSlotsByName(DepositWindow);
    } // setupUi

    void retranslateUi(QWidget *DepositWindow)
    {
        DepositWindow->setWindowTitle(QApplication::translate("DepositWindow", "Form", 0));
        backButton->setText(QApplication::translate("DepositWindow", "Back", 0));
        confirmButton->setText(QApplication::translate("DepositWindow", "Make Deposit", 0));
        pushButton_01->setText(QApplication::translate("DepositWindow", "1", 0));
        pushButton_05->setText(QApplication::translate("DepositWindow", "5", 0));
        pushButton_07->setText(QApplication::translate("DepositWindow", "7", 0));
        pushButton_09->setText(QApplication::translate("DepositWindow", "9", 0));
        pushButton_04->setText(QApplication::translate("DepositWindow", "4", 0));
        pushButton_02->setText(QApplication::translate("DepositWindow", "2", 0));
        pushButton_03->setText(QApplication::translate("DepositWindow", "3", 0));
        pushButton_06->setText(QApplication::translate("DepositWindow", "6", 0));
        pushButton_08->setText(QApplication::translate("DepositWindow", "8", 0));
        pushButton_coma->setText(QApplication::translate("DepositWindow", ",", 0));
        pushButton_00->setText(QApplication::translate("DepositWindow", "0", 0));
        pushButton_C->setText(QApplication::translate("DepositWindow", "C", 0));
        label->setText(QApplication::translate("DepositWindow", "Subtotal", 0));
        depositLabel->setText(QApplication::translate("DepositWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("DepositWindow", "Total", 0));
        newBalanceLabel->setText(QApplication::translate("DepositWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class DepositWindow: public Ui_DepositWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSITWINDOW_H
