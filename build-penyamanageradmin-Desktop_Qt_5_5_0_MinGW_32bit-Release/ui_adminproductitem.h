/********************************************************************************
** Form generated from reading UI file 'adminproductitem.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPRODUCTITEM_H
#define UI_ADMINPRODUCTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminProductItem
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *savePushButton;
    QWidget *nameFormWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *imageFormGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *imagePushButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *imageLabel;
    QWidget *activeWidget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *activeCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QWidget *priceWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *priceLabel;
    QDoubleSpinBox *priceDoubleSpinBox;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *providerGroupBox;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *providerComboBox;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *familyGroupBox;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *familyComboBox;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AdminProductItem)
    {
        if (AdminProductItem->objectName().isEmpty())
            AdminProductItem->setObjectName(QStringLiteral("AdminProductItem"));
        AdminProductItem->resize(800, 600);
        AdminProductItem->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(AdminProductItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(AdminProductItem);
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

        nameFormWidget = new QWidget(AdminProductItem);
        nameFormWidget->setObjectName(QStringLiteral("nameFormWidget"));
        horizontalLayout_3 = new QHBoxLayout(nameFormWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        nameLabel = new QLabel(nameFormWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout_3->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(nameFormWidget);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        horizontalLayout_3->addWidget(nameLineEdit);

        horizontalSpacer_2 = new QSpacerItem(332, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(nameFormWidget);

        imageFormGroupBox = new QGroupBox(AdminProductItem);
        imageFormGroupBox->setObjectName(QStringLiteral("imageFormGroupBox"));
        horizontalLayout_5 = new QHBoxLayout(imageFormGroupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        imagePushButton = new QPushButton(imageFormGroupBox);
        imagePushButton->setObjectName(QStringLiteral("imagePushButton"));

        horizontalLayout_5->addWidget(imagePushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        imageLabel = new QLabel(imageFormGroupBox);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        horizontalLayout_5->addWidget(imageLabel);


        verticalLayout->addWidget(imageFormGroupBox);

        activeWidget = new QWidget(AdminProductItem);
        activeWidget->setObjectName(QStringLiteral("activeWidget"));
        horizontalLayout_2 = new QHBoxLayout(activeWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        activeCheckBox = new QCheckBox(activeWidget);
        activeCheckBox->setObjectName(QStringLiteral("activeCheckBox"));

        horizontalLayout_2->addWidget(activeCheckBox);

        horizontalSpacer_3 = new QSpacerItem(682, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(activeWidget);

        priceWidget = new QWidget(AdminProductItem);
        priceWidget->setObjectName(QStringLiteral("priceWidget"));
        horizontalLayout_4 = new QHBoxLayout(priceWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        priceLabel = new QLabel(priceWidget);
        priceLabel->setObjectName(QStringLiteral("priceLabel"));

        horizontalLayout_4->addWidget(priceLabel);

        priceDoubleSpinBox = new QDoubleSpinBox(priceWidget);
        priceDoubleSpinBox->setObjectName(QStringLiteral("priceDoubleSpinBox"));

        horizontalLayout_4->addWidget(priceDoubleSpinBox);

        horizontalSpacer_5 = new QSpacerItem(354, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(priceWidget);

        providerGroupBox = new QGroupBox(AdminProductItem);
        providerGroupBox->setObjectName(QStringLiteral("providerGroupBox"));
        horizontalLayout_6 = new QHBoxLayout(providerGroupBox);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        providerComboBox = new QComboBox(providerGroupBox);
        providerComboBox->setObjectName(QStringLiteral("providerComboBox"));

        horizontalLayout_6->addWidget(providerComboBox);

        horizontalSpacer_6 = new QSpacerItem(662, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addWidget(providerGroupBox);

        familyGroupBox = new QGroupBox(AdminProductItem);
        familyGroupBox->setObjectName(QStringLiteral("familyGroupBox"));
        horizontalLayout_7 = new QHBoxLayout(familyGroupBox);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        familyComboBox = new QComboBox(familyGroupBox);
        familyComboBox->setObjectName(QStringLiteral("familyComboBox"));

        horizontalLayout_7->addWidget(familyComboBox);

        horizontalSpacer_7 = new QSpacerItem(662, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout->addWidget(familyGroupBox);

        verticalSpacer = new QSpacerItem(20, 475, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        topFrame->raise();
        nameFormWidget->raise();
        imageFormGroupBox->raise();
        activeWidget->raise();
        priceWidget->raise();
        providerGroupBox->raise();
        familyGroupBox->raise();

        retranslateUi(AdminProductItem);

        QMetaObject::connectSlotsByName(AdminProductItem);
    } // setupUi

    void retranslateUi(QWidget *AdminProductItem)
    {
        AdminProductItem->setWindowTitle(QApplication::translate("AdminProductItem", "Form", 0));
        titleLabel->setText(QApplication::translate("AdminProductItem", "Create New Product", 0));
        savePushButton->setText(QApplication::translate("AdminProductItem", "Save", 0));
        nameLabel->setText(QApplication::translate("AdminProductItem", "Name:", 0));
        imageFormGroupBox->setTitle(QApplication::translate("AdminProductItem", "Image", 0));
        imagePushButton->setText(QApplication::translate("AdminProductItem", "Open", 0));
        imageLabel->setText(QApplication::translate("AdminProductItem", "TextLabel", 0));
        activeCheckBox->setText(QApplication::translate("AdminProductItem", "Active", 0));
        priceLabel->setText(QApplication::translate("AdminProductItem", "Price:", 0));
        providerGroupBox->setTitle(QApplication::translate("AdminProductItem", "Provider", 0));
        familyGroupBox->setTitle(QApplication::translate("AdminProductItem", "Family", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminProductItem: public Ui_AdminProductItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPRODUCTITEM_H
