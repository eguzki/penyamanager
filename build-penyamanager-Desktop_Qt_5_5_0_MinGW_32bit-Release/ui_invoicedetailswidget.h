/********************************************************************************
** Form generated from reading UI file 'invoicedetailswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICEDETAILSWIDGET_H
#define UI_INVOICEDETAILSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvoiceDetailsWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *pruductListFrame;
    QVBoxLayout *verticalLayout;
    QFrame *invoiceIdFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *invoiceIdLabel;
    QLabel *invoiceIdValueLabel;
    QFrame *memberIdFrame;
    QHBoxLayout *horizontalLayout_5;
    QLabel *memberIdLabel;
    QLabel *memberIdValueLabel;
    QFrame *invoiceDateFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *invoiceDateLabel;
    QLabel *invoiceDateValueLabel;
    QFrame *invoiceLastModifFrame;
    QHBoxLayout *horizontalLayout_6;
    QLabel *invoiceLastModifLabel;
    QLabel *invoiceLastModifValueLabel;
    QFrame *invoiceTotalFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *invoiceTotalLabel;
    QLabel *invoiceTotalValueLabel;
    QFrame *invoiceInfoFrame;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *productTableWidget;

    void setupUi(QWidget *InvoiceDetailsWidget)
    {
        if (InvoiceDetailsWidget->objectName().isEmpty())
            InvoiceDetailsWidget->setObjectName(QStringLiteral("InvoiceDetailsWidget"));
        InvoiceDetailsWidget->resize(1000, 700);
        InvoiceDetailsWidget->setMinimumSize(QSize(0, 0));
        InvoiceDetailsWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(InvoiceDetailsWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pruductListFrame = new QFrame(InvoiceDetailsWidget);
        pruductListFrame->setObjectName(QStringLiteral("pruductListFrame"));
        pruductListFrame->setFrameShape(QFrame::StyledPanel);
        pruductListFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(pruductListFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        invoiceIdFrame = new QFrame(pruductListFrame);
        invoiceIdFrame->setObjectName(QStringLiteral("invoiceIdFrame"));
        invoiceIdFrame->setFrameShape(QFrame::StyledPanel);
        invoiceIdFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(invoiceIdFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        invoiceIdLabel = new QLabel(invoiceIdFrame);
        invoiceIdLabel->setObjectName(QStringLiteral("invoiceIdLabel"));

        horizontalLayout_2->addWidget(invoiceIdLabel);

        invoiceIdValueLabel = new QLabel(invoiceIdFrame);
        invoiceIdValueLabel->setObjectName(QStringLiteral("invoiceIdValueLabel"));
        invoiceIdValueLabel->setMinimumSize(QSize(200, 0));
        invoiceIdValueLabel->setText(QStringLiteral("1"));

        horizontalLayout_2->addWidget(invoiceIdValueLabel);


        verticalLayout->addWidget(invoiceIdFrame);

        memberIdFrame = new QFrame(pruductListFrame);
        memberIdFrame->setObjectName(QStringLiteral("memberIdFrame"));
        memberIdFrame->setFrameShape(QFrame::StyledPanel);
        memberIdFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(memberIdFrame);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        memberIdLabel = new QLabel(memberIdFrame);
        memberIdLabel->setObjectName(QStringLiteral("memberIdLabel"));

        horizontalLayout_5->addWidget(memberIdLabel);

        memberIdValueLabel = new QLabel(memberIdFrame);
        memberIdValueLabel->setObjectName(QStringLiteral("memberIdValueLabel"));
        memberIdValueLabel->setText(QStringLiteral("1"));

        horizontalLayout_5->addWidget(memberIdValueLabel);


        verticalLayout->addWidget(memberIdFrame);

        invoiceDateFrame = new QFrame(pruductListFrame);
        invoiceDateFrame->setObjectName(QStringLiteral("invoiceDateFrame"));
        invoiceDateFrame->setFrameShape(QFrame::StyledPanel);
        invoiceDateFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(invoiceDateFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        invoiceDateLabel = new QLabel(invoiceDateFrame);
        invoiceDateLabel->setObjectName(QStringLiteral("invoiceDateLabel"));

        horizontalLayout_3->addWidget(invoiceDateLabel);

        invoiceDateValueLabel = new QLabel(invoiceDateFrame);
        invoiceDateValueLabel->setObjectName(QStringLiteral("invoiceDateValueLabel"));
        invoiceDateValueLabel->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(invoiceDateValueLabel);


        verticalLayout->addWidget(invoiceDateFrame);

        invoiceLastModifFrame = new QFrame(pruductListFrame);
        invoiceLastModifFrame->setObjectName(QStringLiteral("invoiceLastModifFrame"));
        invoiceLastModifFrame->setFrameShape(QFrame::StyledPanel);
        invoiceLastModifFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(invoiceLastModifFrame);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        invoiceLastModifLabel = new QLabel(invoiceLastModifFrame);
        invoiceLastModifLabel->setObjectName(QStringLiteral("invoiceLastModifLabel"));

        horizontalLayout_6->addWidget(invoiceLastModifLabel);

        invoiceLastModifValueLabel = new QLabel(invoiceLastModifFrame);
        invoiceLastModifValueLabel->setObjectName(QStringLiteral("invoiceLastModifValueLabel"));
        invoiceLastModifValueLabel->setText(QStringLiteral(""));

        horizontalLayout_6->addWidget(invoiceLastModifValueLabel);


        verticalLayout->addWidget(invoiceLastModifFrame);

        invoiceTotalFrame = new QFrame(pruductListFrame);
        invoiceTotalFrame->setObjectName(QStringLiteral("invoiceTotalFrame"));
        invoiceTotalFrame->setFrameShape(QFrame::StyledPanel);
        invoiceTotalFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(invoiceTotalFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        invoiceTotalLabel = new QLabel(invoiceTotalFrame);
        invoiceTotalLabel->setObjectName(QStringLiteral("invoiceTotalLabel"));

        horizontalLayout_4->addWidget(invoiceTotalLabel);

        invoiceTotalValueLabel = new QLabel(invoiceTotalFrame);
        invoiceTotalValueLabel->setObjectName(QStringLiteral("invoiceTotalValueLabel"));
        invoiceTotalValueLabel->setMinimumSize(QSize(200, 0));
        invoiceTotalValueLabel->setText(QString::fromUtf8("0 \342\202\254"));

        horizontalLayout_4->addWidget(invoiceTotalValueLabel);


        verticalLayout->addWidget(invoiceTotalFrame);


        horizontalLayout->addWidget(pruductListFrame);

        invoiceInfoFrame = new QFrame(InvoiceDetailsWidget);
        invoiceInfoFrame->setObjectName(QStringLiteral("invoiceInfoFrame"));
        invoiceInfoFrame->setFrameShape(QFrame::StyledPanel);
        invoiceInfoFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(invoiceInfoFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        productTableWidget = new QTableWidget(invoiceInfoFrame);
        productTableWidget->setObjectName(QStringLiteral("productTableWidget"));
        productTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        productTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        productTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        productTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(productTableWidget);


        horizontalLayout->addWidget(invoiceInfoFrame);


        retranslateUi(InvoiceDetailsWidget);

        QMetaObject::connectSlotsByName(InvoiceDetailsWidget);
    } // setupUi

    void retranslateUi(QWidget *InvoiceDetailsWidget)
    {
        InvoiceDetailsWidget->setWindowTitle(QApplication::translate("InvoiceDetailsWidget", "Form", 0));
        invoiceIdLabel->setText(QApplication::translate("InvoiceDetailsWidget", "#ref:", 0));
        memberIdLabel->setText(QApplication::translate("InvoiceDetailsWidget", "MemberId:", 0));
        invoiceDateLabel->setText(QApplication::translate("InvoiceDetailsWidget", "Date:", 0));
        invoiceDateValueLabel->setText(QApplication::translate("InvoiceDetailsWidget", "01/05/2015", 0));
        invoiceLastModifLabel->setText(QApplication::translate("InvoiceDetailsWidget", "Last Modified:", 0));
        invoiceTotalLabel->setText(QApplication::translate("InvoiceDetailsWidget", "Total:", 0));
    } // retranslateUi

};

namespace Ui {
    class InvoiceDetailsWidget: public Ui_InvoiceDetailsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEDETAILSWIDGET_H
