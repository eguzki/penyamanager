/********************************************************************************
** Form generated from reading UI file 'familyitemmanagementwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAMILYITEMMANAGEMENTWINDOW_H
#define UI_FAMILYITEMMANAGEMENTWINDOW_H

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

class Ui_FamilyItemManagementWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *newItemPushButton;
    QPushButton *newFamilyPushButton;
    QPushButton *editFamilyPushButton;
    QFrame *bottonFrame;
    QHBoxLayout *horizontalLayout_2;
    QFrame *familyFrame;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *familyListWidget;
    QFrame *productFrame;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *productListWidget;

    void setupUi(QWidget *FamilyItemManagementWindow)
    {
        if (FamilyItemManagementWindow->objectName().isEmpty())
            FamilyItemManagementWindow->setObjectName(QStringLiteral("FamilyItemManagementWindow"));
        FamilyItemManagementWindow->resize(800, 600);
        FamilyItemManagementWindow->setStyleSheet(QLatin1String("#topFrame {\n"
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
"\n"
""));
        verticalLayout = new QVBoxLayout(FamilyItemManagementWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(FamilyItemManagementWindow);
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

        newItemPushButton = new QPushButton(topFrame);
        newItemPushButton->setObjectName(QStringLiteral("newItemPushButton"));

        horizontalLayout->addWidget(newItemPushButton);

        newFamilyPushButton = new QPushButton(topFrame);
        newFamilyPushButton->setObjectName(QStringLiteral("newFamilyPushButton"));

        horizontalLayout->addWidget(newFamilyPushButton);

        editFamilyPushButton = new QPushButton(topFrame);
        editFamilyPushButton->setObjectName(QStringLiteral("editFamilyPushButton"));

        horizontalLayout->addWidget(editFamilyPushButton);


        verticalLayout->addWidget(topFrame);

        bottonFrame = new QFrame(FamilyItemManagementWindow);
        bottonFrame->setObjectName(QStringLiteral("bottonFrame"));
        bottonFrame->setFrameShape(QFrame::StyledPanel);
        bottonFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(bottonFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        familyFrame = new QFrame(bottonFrame);
        familyFrame->setObjectName(QStringLiteral("familyFrame"));
        familyFrame->setMinimumSize(QSize(300, 0));
        familyFrame->setMaximumSize(QSize(300, 16777215));
        familyFrame->setFrameShape(QFrame::StyledPanel);
        familyFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(familyFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        familyListWidget = new QListWidget(familyFrame);
        familyListWidget->setObjectName(QStringLiteral("familyListWidget"));
        familyListWidget->setAlternatingRowColors(true);

        horizontalLayout_3->addWidget(familyListWidget);


        horizontalLayout_2->addWidget(familyFrame);

        productFrame = new QFrame(bottonFrame);
        productFrame->setObjectName(QStringLiteral("productFrame"));
        productFrame->setFrameShape(QFrame::StyledPanel);
        productFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(productFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        productListWidget = new QListWidget(productFrame);
        productListWidget->setObjectName(QStringLiteral("productListWidget"));
        productListWidget->setFlow(QListView::LeftToRight);
        productListWidget->setProperty("isWrapping", QVariant(true));
        productListWidget->setUniformItemSizes(true);

        horizontalLayout_4->addWidget(productListWidget);


        horizontalLayout_2->addWidget(productFrame);


        verticalLayout->addWidget(bottonFrame);


        retranslateUi(FamilyItemManagementWindow);

        QMetaObject::connectSlotsByName(FamilyItemManagementWindow);
    } // setupUi

    void retranslateUi(QWidget *FamilyItemManagementWindow)
    {
        FamilyItemManagementWindow->setWindowTitle(QApplication::translate("FamilyItemManagementWindow", "Form", 0));
        titleLabel->setText(QApplication::translate("FamilyItemManagementWindow", "Product Manager", 0));
        newItemPushButton->setText(QApplication::translate("FamilyItemManagementWindow", "new Item", 0));
        newFamilyPushButton->setText(QApplication::translate("FamilyItemManagementWindow", "new Family", 0));
        editFamilyPushButton->setText(QApplication::translate("FamilyItemManagementWindow", "edit Family", 0));
    } // retranslateUi

};

namespace Ui {
    class FamilyItemManagementWindow: public Ui_FamilyItemManagementWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAMILYITEMMANAGEMENTWINDOW_H
