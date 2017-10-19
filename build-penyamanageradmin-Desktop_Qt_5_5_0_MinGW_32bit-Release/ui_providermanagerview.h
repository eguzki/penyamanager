/********************************************************************************
** Form generated from reading UI file 'providermanagerview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVIDERMANAGERVIEW_H
#define UI_PROVIDERMANAGERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProviderManagerView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *newProviderPushButton;
    QFrame *bottonFrame;
    QHBoxLayout *horizontalLayout_2;
    QFrame *providersFrame;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *providersListWidget;
    QFrame *productsFrame;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *productsListWidget;

    void setupUi(QWidget *ProviderManagerView)
    {
        if (ProviderManagerView->objectName().isEmpty())
            ProviderManagerView->setObjectName(QStringLiteral("ProviderManagerView"));
        ProviderManagerView->resize(1200, 1000);
        ProviderManagerView->setStyleSheet(QLatin1String("#topFrame {\n"
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
"}"));
        verticalLayout = new QVBoxLayout(ProviderManagerView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(ProviderManagerView);
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

        newProviderPushButton = new QPushButton(topFrame);
        newProviderPushButton->setObjectName(QStringLiteral("newProviderPushButton"));

        horizontalLayout->addWidget(newProviderPushButton);


        verticalLayout->addWidget(topFrame);

        bottonFrame = new QFrame(ProviderManagerView);
        bottonFrame->setObjectName(QStringLiteral("bottonFrame"));
        bottonFrame->setFrameShape(QFrame::StyledPanel);
        bottonFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(bottonFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        providersFrame = new QFrame(bottonFrame);
        providersFrame->setObjectName(QStringLiteral("providersFrame"));
        providersFrame->setMinimumSize(QSize(300, 0));
        providersFrame->setMaximumSize(QSize(300, 16777215));
        providersFrame->setFrameShape(QFrame::StyledPanel);
        providersFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(providersFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        providersListWidget = new QListWidget(providersFrame);
        providersListWidget->setObjectName(QStringLiteral("providersListWidget"));

        horizontalLayout_3->addWidget(providersListWidget);


        horizontalLayout_2->addWidget(providersFrame);

        productsFrame = new QFrame(bottonFrame);
        productsFrame->setObjectName(QStringLiteral("productsFrame"));
        productsFrame->setFrameShape(QFrame::StyledPanel);
        productsFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(productsFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        productsListWidget = new QListWidget(productsFrame);
        productsListWidget->setObjectName(QStringLiteral("productsListWidget"));
        productsListWidget->setFlow(QListView::LeftToRight);
        productsListWidget->setProperty("isWrapping", QVariant(true));
        productsListWidget->setUniformItemSizes(true);

        horizontalLayout_4->addWidget(productsListWidget);


        horizontalLayout_2->addWidget(productsFrame);


        verticalLayout->addWidget(bottonFrame);


        retranslateUi(ProviderManagerView);

        QMetaObject::connectSlotsByName(ProviderManagerView);
    } // setupUi

    void retranslateUi(QWidget *ProviderManagerView)
    {
        ProviderManagerView->setWindowTitle(QApplication::translate("ProviderManagerView", "Form", 0));
        titleLabel->setText(QApplication::translate("ProviderManagerView", "Provider Manager", 0));
        newProviderPushButton->setText(QApplication::translate("ProviderManagerView", "new provider", 0));
    } // retranslateUi

};

namespace Ui {
    class ProviderManagerView: public Ui_ProviderManagerView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDERMANAGERVIEW_H
