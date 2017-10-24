/********************************************************************************
** Form generated from reading UI file 'memberdashboardwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERDASHBOARDWINDOW_H
#define UI_MEMBERDASHBOARDWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemberDashboardWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *topPanelWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *tableReservationButton;
    QPushButton *invoicesPushButton;
    QPushButton *accountButton;
    QPushButton *depositsButton;
    QPushButton *exitButton;
    QWidget *mainWidget;
    QHBoxLayout *verticalLayout_2;
    QListWidget *familyListWidget;
    QListWidget *productListWidget;
    QWidget *invoiceInfoWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *invoiceWidget;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *invoiceTableWidget;
    QWidget *totalWidget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *totalLabel;
    QLabel *totalDisplayLabel;
    QWidget *invoiceButtonBox;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *invoiceResetButton;
    QPushButton *invoiceCloseButton;

    void setupUi(QWidget *MemberDashboardWindow)
    {
        if (MemberDashboardWindow->objectName().isEmpty())
            MemberDashboardWindow->setObjectName(QStringLiteral("MemberDashboardWindow"));
        MemberDashboardWindow->resize(817, 768);
        MemberDashboardWindow->setWindowTitle(QStringLiteral(""));
        MemberDashboardWindow->setStyleSheet(QLatin1String("QListWidget {\n"
"    alternate-background-color:  rgb(158,158,158);\n"
"    \n"
"    selection-color: green;\n"
"    background: rgb(158,158,158);\n"
"}\n"
"\n"
"\n"
"QTableWidget{\n"
"font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"#productListWidget {\n"
"    alternate-background-color:  rgb(158,158,158);\n"
"    background: rgb(189,189,189);\n"
"}\n"
"\n"
"#familyListWidget {\n"
"    alternate-background-color:  rgb(158,158,158);\n"
"    background: rgb(189,189,189);\n"
"}\n"
"\n"
"#invoiceTableWidget {\n"
"   background: rgb(189,189,189);\n"
"}\n"
"\n"
"PenyaManager--FamilyItemWidget * {\n"
"	font-weight: bold;\n"
"	color: black;\n"
"	font: 20pt \"Calibri\";\n"
"}\n"
"\n"
"PenyaManager--ProductItemWidget * {\n"
"    color: rgb(33,33,33);\n"
"	font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"#totalDisplayLabel {\n"
"font-weight: bold;\n"
"font: 40pt \"Calibri\";\n"
"}\n"
"\n"
"#totalLabel {\n"
"font-weight: bold;\n"
"font: 40pt \"Calibri\";\n"
"}"));
        MemberDashboardWindow->setLocale(QLocale(QLocale::Spanish, QLocale::Spain));
        verticalLayout = new QVBoxLayout(MemberDashboardWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topPanelWidget = new QWidget(MemberDashboardWindow);
        topPanelWidget->setObjectName(QStringLiteral("topPanelWidget"));
        topPanelWidget->setMinimumSize(QSize(0, 150));
        topPanelWidget->setMaximumSize(QSize(16777215, 150));
        horizontalLayout_5 = new QHBoxLayout(topPanelWidget);
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(1, 1, 1, 1);
        tableReservationButton = new QPushButton(topPanelWidget);
        tableReservationButton->setObjectName(QStringLiteral("tableReservationButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableReservationButton->sizePolicy().hasHeightForWidth());
        tableReservationButton->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(tableReservationButton);

        invoicesPushButton = new QPushButton(topPanelWidget);
        invoicesPushButton->setObjectName(QStringLiteral("invoicesPushButton"));
        sizePolicy.setHeightForWidth(invoicesPushButton->sizePolicy().hasHeightForWidth());
        invoicesPushButton->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(invoicesPushButton);

        accountButton = new QPushButton(topPanelWidget);
        accountButton->setObjectName(QStringLiteral("accountButton"));
        sizePolicy.setHeightForWidth(accountButton->sizePolicy().hasHeightForWidth());
        accountButton->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(accountButton);

        depositsButton = new QPushButton(topPanelWidget);
        depositsButton->setObjectName(QStringLiteral("depositsButton"));
        sizePolicy.setHeightForWidth(depositsButton->sizePolicy().hasHeightForWidth());
        depositsButton->setSizePolicy(sizePolicy);
        depositsButton->setMinimumSize(QSize(0, 0));
        depositsButton->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_5->addWidget(depositsButton);

        exitButton = new QPushButton(topPanelWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        sizePolicy.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy);
        exitButton->setMinimumSize(QSize(0, 0));
        exitButton->setMaximumSize(QSize(16777215, 16777215));
        exitButton->setAutoFillBackground(false);

        horizontalLayout_5->addWidget(exitButton);


        verticalLayout->addWidget(topPanelWidget);

        mainWidget = new QWidget(MemberDashboardWindow);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        verticalLayout_2 = new QHBoxLayout(mainWidget);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(4, 4, 4, 4);
        familyListWidget = new QListWidget(mainWidget);
        familyListWidget->setObjectName(QStringLiteral("familyListWidget"));
        familyListWidget->setMinimumSize(QSize(250, 0));
        familyListWidget->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setPointSize(5);
        familyListWidget->setFont(font);
        familyListWidget->setStyleSheet(QStringLiteral("selection-background-color: rgba(229, 92, 92, 122);"));
        familyListWidget->setAlternatingRowColors(true);
        familyListWidget->setMovement(QListView::Static);
        familyListWidget->setFlow(QListView::TopToBottom);
        familyListWidget->setUniformItemSizes(true);
        familyListWidget->setSelectionRectVisible(true);

        verticalLayout_2->addWidget(familyListWidget);

        productListWidget = new QListWidget(mainWidget);
        productListWidget->setObjectName(QStringLiteral("productListWidget"));
        QFont font1;
        font1.setPointSize(7);
        productListWidget->setFont(font1);
        productListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        productListWidget->setDefaultDropAction(Qt::IgnoreAction);
        productListWidget->setAlternatingRowColors(true);
        productListWidget->setMovement(QListView::Static);
        productListWidget->setFlow(QListView::TopToBottom);
        productListWidget->setProperty("isWrapping", QVariant(true));
        productListWidget->setUniformItemSizes(true);

        verticalLayout_2->addWidget(productListWidget);

        invoiceInfoWidget = new QWidget(mainWidget);
        invoiceInfoWidget->setObjectName(QStringLiteral("invoiceInfoWidget"));
        invoiceInfoWidget->setMinimumSize(QSize(0, 0));
        invoiceInfoWidget->setMaximumSize(QSize(490, 16777215));
        verticalLayout_4 = new QVBoxLayout(invoiceInfoWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        invoiceWidget = new QWidget(invoiceInfoWidget);
        invoiceWidget->setObjectName(QStringLiteral("invoiceWidget"));
        invoiceWidget->setMinimumSize(QSize(0, 0));
        invoiceWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_5 = new QVBoxLayout(invoiceWidget);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        invoiceTableWidget = new QTableWidget(invoiceWidget);
        invoiceTableWidget->setObjectName(QStringLiteral("invoiceTableWidget"));
        invoiceTableWidget->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(18);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        invoiceTableWidget->setFont(font2);
        invoiceTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        invoiceTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        invoiceTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        invoiceTableWidget->setProperty("showDropIndicator", QVariant(false));
        invoiceTableWidget->setDragEnabled(false);
        invoiceTableWidget->setDragDropOverwriteMode(false);
        invoiceTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        invoiceTableWidget->setCornerButtonEnabled(false);
        invoiceTableWidget->horizontalHeader()->setStretchLastSection(false);
        invoiceTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(invoiceTableWidget);


        verticalLayout_4->addWidget(invoiceWidget);

        totalWidget = new QWidget(invoiceInfoWidget);
        totalWidget->setObjectName(QStringLiteral("totalWidget"));
        totalWidget->setMinimumSize(QSize(0, 65));
        totalWidget->setMaximumSize(QSize(16777215, 65));
        horizontalLayout_8 = new QHBoxLayout(totalWidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        totalLabel = new QLabel(totalWidget);
        totalLabel->setObjectName(QStringLiteral("totalLabel"));

        horizontalLayout_8->addWidget(totalLabel);

        totalDisplayLabel = new QLabel(totalWidget);
        totalDisplayLabel->setObjectName(QStringLiteral("totalDisplayLabel"));
        totalDisplayLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(totalDisplayLabel);


        verticalLayout_4->addWidget(totalWidget);

        invoiceButtonBox = new QWidget(invoiceInfoWidget);
        invoiceButtonBox->setObjectName(QStringLiteral("invoiceButtonBox"));
        invoiceButtonBox->setMinimumSize(QSize(0, 75));
        invoiceButtonBox->setMaximumSize(QSize(16777215, 75));
        horizontalLayout_9 = new QHBoxLayout(invoiceButtonBox);
        horizontalLayout_9->setSpacing(10);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(1, 1, 1, 1);
        invoiceResetButton = new QPushButton(invoiceButtonBox);
        invoiceResetButton->setObjectName(QStringLiteral("invoiceResetButton"));
        sizePolicy.setHeightForWidth(invoiceResetButton->sizePolicy().hasHeightForWidth());
        invoiceResetButton->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(invoiceResetButton);

        invoiceCloseButton = new QPushButton(invoiceButtonBox);
        invoiceCloseButton->setObjectName(QStringLiteral("invoiceCloseButton"));
        sizePolicy.setHeightForWidth(invoiceCloseButton->sizePolicy().hasHeightForWidth());
        invoiceCloseButton->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(invoiceCloseButton);


        verticalLayout_4->addWidget(invoiceButtonBox);


        verticalLayout_2->addWidget(invoiceInfoWidget);


        verticalLayout->addWidget(mainWidget);


        retranslateUi(MemberDashboardWindow);

        QMetaObject::connectSlotsByName(MemberDashboardWindow);
    } // setupUi

    void retranslateUi(QWidget *MemberDashboardWindow)
    {
        tableReservationButton->setText(QApplication::translate("MemberDashboardWindow", "Reservations", 0));
        invoicesPushButton->setText(QApplication::translate("MemberDashboardWindow", "Invoices", 0));
        accountButton->setText(QApplication::translate("MemberDashboardWindow", "Account", 0));
        depositsButton->setText(QApplication::translate("MemberDashboardWindow", "Deposits", 0));
        exitButton->setText(QApplication::translate("MemberDashboardWindow", "Exit", 0));
        totalLabel->setText(QApplication::translate("MemberDashboardWindow", "Total:", 0));
        totalDisplayLabel->setText(QApplication::translate("MemberDashboardWindow", "TextLabel", 0));
        invoiceResetButton->setText(QApplication::translate("MemberDashboardWindow", "Reset", 0));
        invoiceCloseButton->setText(QApplication::translate("MemberDashboardWindow", "Close", 0));
        Q_UNUSED(MemberDashboardWindow);
    } // retranslateUi

};

namespace Ui {
    class MemberDashboardWindow: public Ui_MemberDashboardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERDASHBOARDWINDOW_H
