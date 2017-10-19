/********************************************************************************
** Form generated from reading UI file 'newproviderinvoiceview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROVIDERINVOICEVIEW_H
#define UI_NEWPROVIDERINVOICEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewProviderInvoiceView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *savePushButton;
    QFrame *providerDataFrame;
    QVBoxLayout *verticalLayout_4;
    QWidget *nameFormWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *invoiceabel;
    QLineEdit *invoiceLineEdit;
    QSpacerItem *horizontalSpacer_4;
    QWidget *phoneFormWidget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *totalLabel;
    QDoubleSpinBox *totalDoubleSpinBox;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *providerGroupBox;
    QHBoxLayout *horizontalLayout_8;
    QComboBox *providerComboBox;
    QSpacerItem *horizontalSpacer_7;
    QListWidget *productsListWidget;

    void setupUi(QWidget *NewProviderInvoiceView)
    {
        if (NewProviderInvoiceView->objectName().isEmpty())
            NewProviderInvoiceView->setObjectName(QStringLiteral("NewProviderInvoiceView"));
        NewProviderInvoiceView->resize(800, 600);
        NewProviderInvoiceView->setWindowTitle(QStringLiteral(""));
        NewProviderInvoiceView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(NewProviderInvoiceView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(NewProviderInvoiceView);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy);
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(topFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(topFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        savePushButton = new QPushButton(topFrame);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));

        horizontalLayout->addWidget(savePushButton);


        verticalLayout->addWidget(topFrame);

        providerDataFrame = new QFrame(NewProviderInvoiceView);
        providerDataFrame->setObjectName(QStringLiteral("providerDataFrame"));
        providerDataFrame->setFrameShape(QFrame::StyledPanel);
        providerDataFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(providerDataFrame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        nameFormWidget = new QWidget(providerDataFrame);
        nameFormWidget->setObjectName(QStringLiteral("nameFormWidget"));
        horizontalLayout_5 = new QHBoxLayout(nameFormWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        invoiceabel = new QLabel(nameFormWidget);
        invoiceabel->setObjectName(QStringLiteral("invoiceabel"));

        horizontalLayout_5->addWidget(invoiceabel);

        invoiceLineEdit = new QLineEdit(nameFormWidget);
        invoiceLineEdit->setObjectName(QStringLiteral("invoiceLineEdit"));

        horizontalLayout_5->addWidget(invoiceLineEdit);

        horizontalSpacer_4 = new QSpacerItem(332, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(nameFormWidget);

        phoneFormWidget = new QWidget(providerDataFrame);
        phoneFormWidget->setObjectName(QStringLiteral("phoneFormWidget"));
        horizontalLayout_7 = new QHBoxLayout(phoneFormWidget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        totalLabel = new QLabel(phoneFormWidget);
        totalLabel->setObjectName(QStringLiteral("totalLabel"));

        horizontalLayout_7->addWidget(totalLabel);

        totalDoubleSpinBox = new QDoubleSpinBox(phoneFormWidget);
        totalDoubleSpinBox->setObjectName(QStringLiteral("totalDoubleSpinBox"));
        totalDoubleSpinBox->setMaximum(1e+06);

        horizontalLayout_7->addWidget(totalDoubleSpinBox);

        horizontalSpacer_5 = new QSpacerItem(330, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout_4->addWidget(phoneFormWidget);

        providerGroupBox = new QGroupBox(providerDataFrame);
        providerGroupBox->setObjectName(QStringLiteral("providerGroupBox"));
        horizontalLayout_8 = new QHBoxLayout(providerGroupBox);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        providerComboBox = new QComboBox(providerGroupBox);
        providerComboBox->setObjectName(QStringLiteral("providerComboBox"));

        horizontalLayout_8->addWidget(providerComboBox);

        horizontalSpacer_7 = new QSpacerItem(662, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_4->addWidget(providerGroupBox);

        productsListWidget = new QListWidget(providerDataFrame);
        productsListWidget->setObjectName(QStringLiteral("productsListWidget"));
        productsListWidget->setSelectionMode(QAbstractItemView::NoSelection);

        verticalLayout_4->addWidget(productsListWidget);


        verticalLayout->addWidget(providerDataFrame);


        retranslateUi(NewProviderInvoiceView);

        QMetaObject::connectSlotsByName(NewProviderInvoiceView);
    } // setupUi

    void retranslateUi(QWidget *NewProviderInvoiceView)
    {
        titleLabel->setText(QApplication::translate("NewProviderInvoiceView", "New Provider Invoice", 0));
        savePushButton->setText(QApplication::translate("NewProviderInvoiceView", "Save", 0));
        invoiceabel->setText(QApplication::translate("NewProviderInvoiceView", "InvoiceID:", 0));
        totalLabel->setText(QApplication::translate("NewProviderInvoiceView", "Total", 0));
        providerGroupBox->setTitle(QApplication::translate("NewProviderInvoiceView", "Provider", 0));
        Q_UNUSED(NewProviderInvoiceView);
    } // retranslateUi

};

namespace Ui {
    class NewProviderInvoiceView: public Ui_NewProviderInvoiceView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROVIDERINVOICEVIEW_H
