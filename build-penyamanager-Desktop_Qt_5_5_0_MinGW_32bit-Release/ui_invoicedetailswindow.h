/********************************************************************************
** Form generated from reading UI file 'invoicedetailswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICEDETAILSWINDOW_H
#define UI_INVOICEDETAILSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvoiceDetailsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *optionsGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *printButton;
    QPushButton *backPushButton;

    void setupUi(QWidget *InvoiceDetailsWindow)
    {
        if (InvoiceDetailsWindow->objectName().isEmpty())
            InvoiceDetailsWindow->setObjectName(QStringLiteral("InvoiceDetailsWindow"));
        InvoiceDetailsWindow->resize(1024, 768);
        verticalLayout = new QVBoxLayout(InvoiceDetailsWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelWidget = new QWidget(InvoiceDetailsWindow);
        topPanelWidget->setObjectName(QStringLiteral("topPanelWidget"));
        topPanelWidget->setMinimumSize(QSize(0, 150));
        topPanelWidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout = new QHBoxLayout(topPanelWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        optionsGroupBox = new QGroupBox(topPanelWidget);
        optionsGroupBox->setObjectName(QStringLiteral("optionsGroupBox"));
        horizontalLayout_2 = new QHBoxLayout(optionsGroupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        printButton = new QPushButton(optionsGroupBox);
        printButton->setObjectName(QStringLiteral("printButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(printButton->sizePolicy().hasHeightForWidth());
        printButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(printButton);

        backPushButton = new QPushButton(optionsGroupBox);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        sizePolicy.setHeightForWidth(backPushButton->sizePolicy().hasHeightForWidth());
        backPushButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(backPushButton);


        horizontalLayout->addWidget(optionsGroupBox);


        verticalLayout->addWidget(topPanelWidget);


        retranslateUi(InvoiceDetailsWindow);

        QMetaObject::connectSlotsByName(InvoiceDetailsWindow);
    } // setupUi

    void retranslateUi(QWidget *InvoiceDetailsWindow)
    {
        InvoiceDetailsWindow->setWindowTitle(QApplication::translate("InvoiceDetailsWindow", "Invoice Details", 0));
        optionsGroupBox->setTitle(QApplication::translate("InvoiceDetailsWindow", "Options", 0));
        printButton->setText(QApplication::translate("InvoiceDetailsWindow", "Print Invoice", 0));
        backPushButton->setText(QApplication::translate("InvoiceDetailsWindow", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class InvoiceDetailsWindow: public Ui_InvoiceDetailsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEDETAILSWINDOW_H
