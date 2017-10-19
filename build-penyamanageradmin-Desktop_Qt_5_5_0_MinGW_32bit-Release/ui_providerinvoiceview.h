/********************************************************************************
** Form generated from reading UI file 'providerinvoiceview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVIDERINVOICEVIEW_H
#define UI_PROVIDERINVOICEVIEW_H

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

class Ui_ProviderInvoiceView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QWidget *InvoiceIdWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *invoiceIdlabel;
    QLabel *invoiceIdValueLabel;
    QSpacerItem *horizontalSpacer_2;
    QWidget *invoiceTotalWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *invoiceTotalLabel;
    QLabel *invoiceTotalValueLabel;
    QSpacerItem *horizontalSpacer_3;
    QWidget *providerInvoiceDateWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *providerInvoiceDateLabel;
    QLabel *providerInvoiceDateValueLabel;
    QSpacerItem *horizontalSpacer_5;
    QWidget *providerWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *providerImageLabel;
    QLabel *providerNameLabel;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *providerInvoiceTableWidget;

    void setupUi(QWidget *ProviderInvoiceView)
    {
        if (ProviderInvoiceView->objectName().isEmpty())
            ProviderInvoiceView->setObjectName(QStringLiteral("ProviderInvoiceView"));
        ProviderInvoiceView->resize(800, 600);
        ProviderInvoiceView->setMinimumSize(QSize(0, 0));
        ProviderInvoiceView->setMaximumSize(QSize(16777215, 16777215));
        ProviderInvoiceView->setWindowTitle(QStringLiteral(""));
        ProviderInvoiceView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(ProviderInvoiceView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(ProviderInvoiceView);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        InvoiceIdWidget = new QWidget(frame);
        InvoiceIdWidget->setObjectName(QStringLiteral("InvoiceIdWidget"));
        horizontalLayout_2 = new QHBoxLayout(InvoiceIdWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        invoiceIdlabel = new QLabel(InvoiceIdWidget);
        invoiceIdlabel->setObjectName(QStringLiteral("invoiceIdlabel"));

        horizontalLayout_2->addWidget(invoiceIdlabel);

        invoiceIdValueLabel = new QLabel(InvoiceIdWidget);
        invoiceIdValueLabel->setObjectName(QStringLiteral("invoiceIdValueLabel"));
        invoiceIdValueLabel->setText(QStringLiteral("0"));

        horizontalLayout_2->addWidget(invoiceIdValueLabel);

        horizontalSpacer_2 = new QSpacerItem(653, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(InvoiceIdWidget);

        invoiceTotalWidget = new QWidget(frame);
        invoiceTotalWidget->setObjectName(QStringLiteral("invoiceTotalWidget"));
        horizontalLayout_3 = new QHBoxLayout(invoiceTotalWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        invoiceTotalLabel = new QLabel(invoiceTotalWidget);
        invoiceTotalLabel->setObjectName(QStringLiteral("invoiceTotalLabel"));

        horizontalLayout_3->addWidget(invoiceTotalLabel);

        invoiceTotalValueLabel = new QLabel(invoiceTotalWidget);
        invoiceTotalValueLabel->setObjectName(QStringLiteral("invoiceTotalValueLabel"));
        invoiceTotalValueLabel->setText(QStringLiteral("0"));

        horizontalLayout_3->addWidget(invoiceTotalValueLabel);

        horizontalSpacer_3 = new QSpacerItem(681, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(invoiceTotalWidget);

        providerInvoiceDateWidget = new QWidget(frame);
        providerInvoiceDateWidget->setObjectName(QStringLiteral("providerInvoiceDateWidget"));
        horizontalLayout_5 = new QHBoxLayout(providerInvoiceDateWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        providerInvoiceDateLabel = new QLabel(providerInvoiceDateWidget);
        providerInvoiceDateLabel->setObjectName(QStringLiteral("providerInvoiceDateLabel"));

        horizontalLayout_5->addWidget(providerInvoiceDateLabel);

        providerInvoiceDateValueLabel = new QLabel(providerInvoiceDateWidget);
        providerInvoiceDateValueLabel->setObjectName(QStringLiteral("providerInvoiceDateValueLabel"));
        providerInvoiceDateValueLabel->setText(QStringLiteral("TextLabel"));

        horizontalLayout_5->addWidget(providerInvoiceDateValueLabel);

        horizontalSpacer_5 = new QSpacerItem(625, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_2->addWidget(providerInvoiceDateWidget);

        providerWidget = new QWidget(frame);
        providerWidget->setObjectName(QStringLiteral("providerWidget"));
        horizontalLayout_4 = new QHBoxLayout(providerWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        providerImageLabel = new QLabel(providerWidget);
        providerImageLabel->setObjectName(QStringLiteral("providerImageLabel"));
        providerImageLabel->setText(QStringLiteral("ImageLabel"));

        horizontalLayout_4->addWidget(providerImageLabel);

        providerNameLabel = new QLabel(providerWidget);
        providerNameLabel->setObjectName(QStringLiteral("providerNameLabel"));
        providerNameLabel->setText(QStringLiteral("TextLabel"));

        horizontalLayout_4->addWidget(providerNameLabel);

        horizontalSpacer_4 = new QSpacerItem(600, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(providerWidget);

        providerInvoiceTableWidget = new QTableWidget(frame);
        providerInvoiceTableWidget->setObjectName(QStringLiteral("providerInvoiceTableWidget"));

        verticalLayout_2->addWidget(providerInvoiceTableWidget);


        verticalLayout->addWidget(frame);


        retranslateUi(ProviderInvoiceView);

        QMetaObject::connectSlotsByName(ProviderInvoiceView);
    } // setupUi

    void retranslateUi(QWidget *ProviderInvoiceView)
    {
        invoiceIdlabel->setText(QApplication::translate("ProviderInvoiceView", "InvoiceID:", 0));
        invoiceTotalLabel->setText(QApplication::translate("ProviderInvoiceView", "Total:", 0));
        providerInvoiceDateLabel->setText(QApplication::translate("ProviderInvoiceView", "Date:", 0));
        Q_UNUSED(ProviderInvoiceView);
    } // retranslateUi

};

namespace Ui {
    class ProviderInvoiceView: public Ui_ProviderInvoiceView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDERINVOICEVIEW_H
