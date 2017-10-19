/********************************************************************************
** Form generated from reading UI file 'invoicewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICEWINDOW_H
#define UI_INVOICEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvoiceWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backPushButton;
    QPushButton *confirmPushButton;
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout_6;
    QTableWidget *invoiceProductTableWidget;
    QGroupBox *invoiceInfoGroupBox;
    QVBoxLayout *verticalLayout_3;
    QWidget *invoiceInfoIDWidget;
    QHBoxLayout *horizontalLayout_11;
    QLabel *invoiceIdLabel;
    QLabel *invoiceIdInfoLabel;
    QWidget *invoiceDateInfoWidget;
    QHBoxLayout *horizontalLayout_12;
    QLabel *invoiceDateInfoLabelLabel;
    QLabel *invoiceDateInfoLabel;
    QWidget *invoiceTotalWidget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *invoiceTotalLabel;
    QLabel *invoiceTotalInfoLabel;
    QWidget *newBalanceWidget;
    QHBoxLayout *horizontalLayout_10;
    QLabel *newBalanceLabel;
    QLabel *newBalanceInfoLabel;

    void setupUi(QWidget *InvoiceWindow)
    {
        if (InvoiceWindow->objectName().isEmpty())
            InvoiceWindow->setObjectName(QStringLiteral("InvoiceWindow"));
        InvoiceWindow->resize(1024, 768);
        verticalLayout = new QVBoxLayout(InvoiceWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelWidget = new QWidget(InvoiceWindow);
        topPanelWidget->setObjectName(QStringLiteral("topPanelWidget"));
        topPanelWidget->setMinimumSize(QSize(0, 150));
        topPanelWidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout = new QHBoxLayout(topPanelWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        backPushButton = new QPushButton(topPanelWidget);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(backPushButton->sizePolicy().hasHeightForWidth());
        backPushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(backPushButton);

        confirmPushButton = new QPushButton(topPanelWidget);
        confirmPushButton->setObjectName(QStringLiteral("confirmPushButton"));
        sizePolicy.setHeightForWidth(confirmPushButton->sizePolicy().hasHeightForWidth());
        confirmPushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(confirmPushButton);


        verticalLayout->addWidget(topPanelWidget);

        mainWidget = new QWidget(InvoiceWindow);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        horizontalLayout_6 = new QHBoxLayout(mainWidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        invoiceProductTableWidget = new QTableWidget(mainWidget);
        invoiceProductTableWidget->setObjectName(QStringLiteral("invoiceProductTableWidget"));
        invoiceProductTableWidget->setMinimumSize(QSize(650, 0));
        invoiceProductTableWidget->setMaximumSize(QSize(650, 16777215));
        invoiceProductTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        invoiceProductTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        invoiceProductTableWidget->verticalHeader()->setVisible(false);

        horizontalLayout_6->addWidget(invoiceProductTableWidget);

        invoiceInfoGroupBox = new QGroupBox(mainWidget);
        invoiceInfoGroupBox->setObjectName(QStringLiteral("invoiceInfoGroupBox"));
        verticalLayout_3 = new QVBoxLayout(invoiceInfoGroupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        invoiceInfoIDWidget = new QWidget(invoiceInfoGroupBox);
        invoiceInfoIDWidget->setObjectName(QStringLiteral("invoiceInfoIDWidget"));
        horizontalLayout_11 = new QHBoxLayout(invoiceInfoIDWidget);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        invoiceIdLabel = new QLabel(invoiceInfoIDWidget);
        invoiceIdLabel->setObjectName(QStringLiteral("invoiceIdLabel"));

        horizontalLayout_11->addWidget(invoiceIdLabel);

        invoiceIdInfoLabel = new QLabel(invoiceInfoIDWidget);
        invoiceIdInfoLabel->setObjectName(QStringLiteral("invoiceIdInfoLabel"));

        horizontalLayout_11->addWidget(invoiceIdInfoLabel);


        verticalLayout_3->addWidget(invoiceInfoIDWidget);

        invoiceDateInfoWidget = new QWidget(invoiceInfoGroupBox);
        invoiceDateInfoWidget->setObjectName(QStringLiteral("invoiceDateInfoWidget"));
        horizontalLayout_12 = new QHBoxLayout(invoiceDateInfoWidget);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        invoiceDateInfoLabelLabel = new QLabel(invoiceDateInfoWidget);
        invoiceDateInfoLabelLabel->setObjectName(QStringLiteral("invoiceDateInfoLabelLabel"));

        horizontalLayout_12->addWidget(invoiceDateInfoLabelLabel);

        invoiceDateInfoLabel = new QLabel(invoiceDateInfoWidget);
        invoiceDateInfoLabel->setObjectName(QStringLiteral("invoiceDateInfoLabel"));

        horizontalLayout_12->addWidget(invoiceDateInfoLabel);


        verticalLayout_3->addWidget(invoiceDateInfoWidget);

        invoiceTotalWidget = new QWidget(invoiceInfoGroupBox);
        invoiceTotalWidget->setObjectName(QStringLiteral("invoiceTotalWidget"));
        horizontalLayout_8 = new QHBoxLayout(invoiceTotalWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        invoiceTotalLabel = new QLabel(invoiceTotalWidget);
        invoiceTotalLabel->setObjectName(QStringLiteral("invoiceTotalLabel"));

        horizontalLayout_8->addWidget(invoiceTotalLabel);

        invoiceTotalInfoLabel = new QLabel(invoiceTotalWidget);
        invoiceTotalInfoLabel->setObjectName(QStringLiteral("invoiceTotalInfoLabel"));

        horizontalLayout_8->addWidget(invoiceTotalInfoLabel);


        verticalLayout_3->addWidget(invoiceTotalWidget);

        newBalanceWidget = new QWidget(invoiceInfoGroupBox);
        newBalanceWidget->setObjectName(QStringLiteral("newBalanceWidget"));
        horizontalLayout_10 = new QHBoxLayout(newBalanceWidget);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        newBalanceLabel = new QLabel(newBalanceWidget);
        newBalanceLabel->setObjectName(QStringLiteral("newBalanceLabel"));

        horizontalLayout_10->addWidget(newBalanceLabel);

        newBalanceInfoLabel = new QLabel(newBalanceWidget);
        newBalanceInfoLabel->setObjectName(QStringLiteral("newBalanceInfoLabel"));

        horizontalLayout_10->addWidget(newBalanceInfoLabel);


        verticalLayout_3->addWidget(newBalanceWidget);


        horizontalLayout_6->addWidget(invoiceInfoGroupBox);


        verticalLayout->addWidget(mainWidget);


        retranslateUi(InvoiceWindow);

        QMetaObject::connectSlotsByName(InvoiceWindow);
    } // setupUi

    void retranslateUi(QWidget *InvoiceWindow)
    {
        InvoiceWindow->setWindowTitle(QApplication::translate("InvoiceWindow", "Invoice Window", 0));
        backPushButton->setText(QApplication::translate("InvoiceWindow", "Back", 0));
        confirmPushButton->setText(QApplication::translate("InvoiceWindow", "Confirm", 0));
        invoiceInfoGroupBox->setTitle(QApplication::translate("InvoiceWindow", "Invoice Information", 0));
        invoiceIdLabel->setText(QApplication::translate("InvoiceWindow", "ID:", 0));
        invoiceIdInfoLabel->setText(QApplication::translate("InvoiceWindow", "TextLabel", 0));
        invoiceDateInfoLabelLabel->setText(QApplication::translate("InvoiceWindow", "Date:", 0));
        invoiceDateInfoLabel->setText(QApplication::translate("InvoiceWindow", "TextLabel", 0));
        invoiceTotalLabel->setText(QApplication::translate("InvoiceWindow", "Total invoice:", 0));
        invoiceTotalInfoLabel->setText(QApplication::translate("InvoiceWindow", "TextLabel", 0));
        newBalanceLabel->setText(QApplication::translate("InvoiceWindow", "New Balance:", 0));
        newBalanceInfoLabel->setText(QApplication::translate("InvoiceWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class InvoiceWindow: public Ui_InvoiceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEWINDOW_H
