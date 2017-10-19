/********************************************************************************
** Form generated from reading UI file 'adminnewprovider.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINNEWPROVIDER_H
#define UI_ADMINNEWPROVIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_AdminNewProvider
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *backPushButton;
    QPushButton *savePushButton;
    QFrame *bottomFrame;
    QHBoxLayout *horizontalLayout_2;
    QFrame *providerDataFrame;
    QVBoxLayout *verticalLayout_2;
    QWidget *nameFormWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QWidget *phoneFormWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *imageFormGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *imagePushButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *imageLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AdminNewProvider)
    {
        if (AdminNewProvider->objectName().isEmpty())
            AdminNewProvider->setObjectName(QStringLiteral("AdminNewProvider"));
        AdminNewProvider->resize(800, 600);
        AdminNewProvider->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(AdminNewProvider);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(AdminNewProvider);
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

        backPushButton = new QPushButton(topFrame);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));

        horizontalLayout->addWidget(backPushButton);

        savePushButton = new QPushButton(topFrame);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));

        horizontalLayout->addWidget(savePushButton);


        verticalLayout->addWidget(topFrame);

        bottomFrame = new QFrame(AdminNewProvider);
        bottomFrame->setObjectName(QStringLiteral("bottomFrame"));
        bottomFrame->setFrameShape(QFrame::StyledPanel);
        bottomFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(bottomFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        providerDataFrame = new QFrame(bottomFrame);
        providerDataFrame->setObjectName(QStringLiteral("providerDataFrame"));
        providerDataFrame->setFrameShape(QFrame::StyledPanel);
        providerDataFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(providerDataFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nameFormWidget = new QWidget(providerDataFrame);
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


        verticalLayout_2->addWidget(nameFormWidget);

        phoneFormWidget = new QWidget(providerDataFrame);
        phoneFormWidget->setObjectName(QStringLiteral("phoneFormWidget"));
        horizontalLayout_4 = new QHBoxLayout(phoneFormWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        phoneLabel = new QLabel(phoneFormWidget);
        phoneLabel->setObjectName(QStringLiteral("phoneLabel"));

        horizontalLayout_4->addWidget(phoneLabel);

        phoneLineEdit = new QLineEdit(phoneFormWidget);
        phoneLineEdit->setObjectName(QStringLiteral("phoneLineEdit"));

        horizontalLayout_4->addWidget(phoneLineEdit);

        horizontalSpacer_3 = new QSpacerItem(330, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(phoneFormWidget);

        imageFormGroupBox = new QGroupBox(providerDataFrame);
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


        verticalLayout_2->addWidget(imageFormGroupBox);

        verticalSpacer = new QSpacerItem(20, 315, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(providerDataFrame);


        verticalLayout->addWidget(bottomFrame);


        retranslateUi(AdminNewProvider);

        QMetaObject::connectSlotsByName(AdminNewProvider);
    } // setupUi

    void retranslateUi(QWidget *AdminNewProvider)
    {
        AdminNewProvider->setWindowTitle(QApplication::translate("AdminNewProvider", "Form", 0));
        titleLabel->setText(QApplication::translate("AdminNewProvider", "Create New Provider", 0));
        backPushButton->setText(QApplication::translate("AdminNewProvider", "Back", 0));
        savePushButton->setText(QApplication::translate("AdminNewProvider", "Save", 0));
        nameLabel->setText(QApplication::translate("AdminNewProvider", "Name:", 0));
        phoneLabel->setText(QApplication::translate("AdminNewProvider", "Phone:", 0));
        imageFormGroupBox->setTitle(QApplication::translate("AdminNewProvider", "Image", 0));
        imagePushButton->setText(QApplication::translate("AdminNewProvider", "Open", 0));
        imageLabel->setText(QApplication::translate("AdminNewProvider", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminNewProvider: public Ui_AdminNewProvider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINNEWPROVIDER_H
