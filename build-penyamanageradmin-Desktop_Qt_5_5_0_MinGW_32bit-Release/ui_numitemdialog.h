/********************************************************************************
** Form generated from reading UI file 'numitemdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMITEMDIALOG_H
#define UI_NUMITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NumItemDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *numDisplayWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *numDisplayLabel;
    QWidget *keypadWidget;
    QGridLayout *gridLayout;
    QToolButton *toolButton_8;
    QToolButton *toolButton_1;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_9;
    QToolButton *toolButton_7;
    QToolButton *toolButton_C;
    QToolButton *toolButton_Done;
    QToolButton *toolButton_0;

    void setupUi(QDialog *NumItemDialog)
    {
        if (NumItemDialog->objectName().isEmpty())
            NumItemDialog->setObjectName(QStringLiteral("NumItemDialog"));
        NumItemDialog->setWindowModality(Qt::WindowModal);
        NumItemDialog->resize(366, 542);
        NumItemDialog->setMinimumSize(QSize(366, 436));
        NumItemDialog->setMaximumSize(QSize(366, 16777215));
        NumItemDialog->setWindowTitle(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/alegrialogo.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        NumItemDialog->setWindowIcon(icon);
        NumItemDialog->setStyleSheet(QLatin1String("#NumItemDialog {\n"
"background: gray;\n"
"}\n"
"\n"
"#numDisplayWidget  *{\n"
"border: 3px solid gray;\n"
"border-radius: 0px;\n"
"background: white;\n"
"font: 75 40pt \"Calibri\";\n"
"color: black;\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QToolButton {\n"
"color: white;\n"
"background-color: rgb(198, 40, 40);\n"
"border-width: 1px;\n"
"border-color: rgb(183, 28, 28);\n"
"border-style: solid;\n"
"border-radius: 0;\n"
"padding: 3px;\n"
"font: 75 40pt \"Calibri\";\n"
"font-weight: bold;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 95px;\n"
"max-width: 95px;\n"
"min-height: 95px;\n"
"max-height: 95px;\n"
"}\n"
"\n"
"QToolButton:pressed {\n"
"background-color: rgb(239,83,80);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        NumItemDialog->setModal(true);
        verticalLayout = new QVBoxLayout(NumItemDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        numDisplayWidget = new QWidget(NumItemDialog);
        numDisplayWidget->setObjectName(QStringLiteral("numDisplayWidget"));
        horizontalLayout = new QHBoxLayout(numDisplayWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        numDisplayLabel = new QLabel(numDisplayWidget);
        numDisplayLabel->setObjectName(QStringLiteral("numDisplayLabel"));
        numDisplayLabel->setMinimumSize(QSize(0, 50));
        numDisplayLabel->setMaximumSize(QSize(16777215, 50));
        numDisplayLabel->setText(QStringLiteral("TextLabel"));
        numDisplayLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(numDisplayLabel);


        verticalLayout->addWidget(numDisplayWidget);

        keypadWidget = new QWidget(NumItemDialog);
        keypadWidget->setObjectName(QStringLiteral("keypadWidget"));
        gridLayout = new QGridLayout(keypadWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        toolButton_8 = new QToolButton(keypadWidget);
        toolButton_8->setObjectName(QStringLiteral("toolButton_8"));
        toolButton_8->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_8, 4, 3, 1, 1);

        toolButton_1 = new QToolButton(keypadWidget);
        toolButton_1->setObjectName(QStringLiteral("toolButton_1"));
        toolButton_1->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_1, 0, 1, 1, 1);

        toolButton_2 = new QToolButton(keypadWidget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_2, 0, 3, 1, 1);

        toolButton_3 = new QToolButton(keypadWidget);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_3, 0, 5, 1, 1);

        toolButton_4 = new QToolButton(keypadWidget);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_4, 2, 1, 1, 1);

        toolButton_5 = new QToolButton(keypadWidget);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        toolButton_5->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_5, 2, 3, 1, 1);

        toolButton_6 = new QToolButton(keypadWidget);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));
        toolButton_6->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_6, 2, 5, 1, 1);

        toolButton_9 = new QToolButton(keypadWidget);
        toolButton_9->setObjectName(QStringLiteral("toolButton_9"));
        toolButton_9->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_9, 4, 5, 1, 1);

        toolButton_7 = new QToolButton(keypadWidget);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));
        toolButton_7->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_7, 4, 1, 1, 1);

        toolButton_C = new QToolButton(keypadWidget);
        toolButton_C->setObjectName(QStringLiteral("toolButton_C"));
        toolButton_C->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_C, 5, 1, 1, 1);

        toolButton_Done = new QToolButton(keypadWidget);
        toolButton_Done->setObjectName(QStringLiteral("toolButton_Done"));
        toolButton_Done->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_Done, 5, 5, 1, 1);

        toolButton_0 = new QToolButton(keypadWidget);
        toolButton_0->setObjectName(QStringLiteral("toolButton_0"));
        toolButton_0->setMinimumSize(QSize(107, 103));

        gridLayout->addWidget(toolButton_0, 5, 3, 1, 1);


        verticalLayout->addWidget(keypadWidget);


        retranslateUi(NumItemDialog);
        QObject::connect(toolButton_Done, SIGNAL(clicked()), NumItemDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(NumItemDialog);
    } // setupUi

    void retranslateUi(QDialog *NumItemDialog)
    {
        toolButton_8->setText(QApplication::translate("NumItemDialog", "8", 0));
        toolButton_1->setText(QApplication::translate("NumItemDialog", "1", 0));
        toolButton_2->setText(QApplication::translate("NumItemDialog", "2", 0));
        toolButton_3->setText(QApplication::translate("NumItemDialog", "3", 0));
        toolButton_4->setText(QApplication::translate("NumItemDialog", "4", 0));
        toolButton_5->setText(QApplication::translate("NumItemDialog", "5", 0));
        toolButton_6->setText(QApplication::translate("NumItemDialog", "6", 0));
        toolButton_9->setText(QApplication::translate("NumItemDialog", "9", 0));
        toolButton_7->setText(QApplication::translate("NumItemDialog", "7", 0));
        toolButton_C->setText(QApplication::translate("NumItemDialog", "C", 0));
        toolButton_Done->setText(QApplication::translate("NumItemDialog", "Ok", 0));
        toolButton_0->setText(QApplication::translate("NumItemDialog", "0", 0));
        Q_UNUSED(NumItemDialog);
    } // retranslateUi

};

namespace Ui {
    class NumItemDialog: public Ui_NumItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMITEMDIALOG_H
