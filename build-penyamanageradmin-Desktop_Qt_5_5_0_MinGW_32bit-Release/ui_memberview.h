/********************************************************************************
** Form generated from reading UI file 'memberview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERVIEW_H
#define UI_MEMBERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemberView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *changePasswordPushButton;
    QPushButton *savePushButton;
    QWidget *memberIdWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *memberIdLabel;
    QLabel *memberIdValueLabel;
    QLabel *regDateLabel;
    QLabel *regDateValueLabel;
    QLabel *lastLoginLabel;
    QLabel *lastLoginValueLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *imageLabel;
    QPushButton *imagePushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_20;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *usernameWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QSpacerItem *horizontalSpacer_5;
    QWidget *nameFormWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QWidget *memberSurnameWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *memberSurnameLabel;
    QLineEdit *memberSurnameLineEdit;
    QSpacerItem *horizontalSpacer_6;
    QWidget *bankAccountWidget;
    QHBoxLayout *horizontalLayout_12;
    QLabel *bankAccountLabel;
    QLineEdit *bankAccountLineEdit;
    QSpacerItem *horizontalSpacer_12;
    QWidget *birthdateWidget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *birthdateLabel;
    QDateEdit *birthdateDateEdit;
    QSpacerItem *horizontalSpacer_8;
    QWidget *emailWidget;
    QHBoxLayout *horizontalLayout_16;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QSpacerItem *horizontalSpacer_16;
    QWidget *addressWidget;
    QHBoxLayout *horizontalLayout_9;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QSpacerItem *horizontalSpacer_9;
    QWidget *zipCodeWidget;
    QHBoxLayout *horizontalLayout_10;
    QLabel *zipCodeLabel;
    QLineEdit *zipCodeLineEdit;
    QSpacerItem *horizontalSpacer_10;
    QWidget *townWidget;
    QHBoxLayout *horizontalLayout_11;
    QLabel *townLabel;
    QLineEdit *townLineEdit;
    QSpacerItem *horizontalSpacer_11;
    QWidget *stateWidget;
    QHBoxLayout *horizontalLayout_13;
    QLabel *stateLabel;
    QLineEdit *stateLineEdit;
    QSpacerItem *horizontalSpacer_13;
    QWidget *phoneWidget;
    QHBoxLayout *horizontalLayout_14;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QSpacerItem *horizontalSpacer_14;
    QWidget *phone2Widget;
    QHBoxLayout *horizontalLayout_15;
    QLabel *phone2Label;
    QLineEdit *phone2LineEdit;
    QSpacerItem *horizontalSpacer_15;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *notesLabelwidget;
    QHBoxLayout *horizontalLayout_19;
    QLabel *notesLabel;
    QSpacerItem *horizontalSpacer_19;
    QWidget *notesWidget;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *notesTextEdit;
    QWidget *activeWidget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *activeCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QWidget *isAdminWidget;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *isAdminCheckBox;
    QSpacerItem *horizontalSpacer_7;
    QWidget *postalSendWidget;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *postalSendCheckBox;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MemberView)
    {
        if (MemberView->objectName().isEmpty())
            MemberView->setObjectName(QStringLiteral("MemberView"));
        MemberView->resize(987, 863);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MemberView->sizePolicy().hasHeightForWidth());
        MemberView->setSizePolicy(sizePolicy);
        MemberView->setMinimumSize(QSize(0, 0));
        MemberView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(MemberView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(MemberView);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy1);
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(topFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(topFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(548, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        changePasswordPushButton = new QPushButton(topFrame);
        changePasswordPushButton->setObjectName(QStringLiteral("changePasswordPushButton"));

        horizontalLayout->addWidget(changePasswordPushButton);

        savePushButton = new QPushButton(topFrame);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));

        horizontalLayout->addWidget(savePushButton);


        verticalLayout->addWidget(topFrame);

        memberIdWidget = new QWidget(MemberView);
        memberIdWidget->setObjectName(QStringLiteral("memberIdWidget"));
        horizontalLayout_4 = new QHBoxLayout(memberIdWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        memberIdLabel = new QLabel(memberIdWidget);
        memberIdLabel->setObjectName(QStringLiteral("memberIdLabel"));
        memberIdLabel->setMinimumSize(QSize(0, 0));
        memberIdLabel->setMaximumSize(QSize(16777215, 16777215));
        memberIdLabel->setText(QStringLiteral("Id:"));

        horizontalLayout_4->addWidget(memberIdLabel);

        memberIdValueLabel = new QLabel(memberIdWidget);
        memberIdValueLabel->setObjectName(QStringLiteral("memberIdValueLabel"));
        memberIdValueLabel->setMinimumSize(QSize(50, 0));
        memberIdValueLabel->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(memberIdValueLabel);

        regDateLabel = new QLabel(memberIdWidget);
        regDateLabel->setObjectName(QStringLiteral("regDateLabel"));

        horizontalLayout_4->addWidget(regDateLabel);

        regDateValueLabel = new QLabel(memberIdWidget);
        regDateValueLabel->setObjectName(QStringLiteral("regDateValueLabel"));
        regDateValueLabel->setMinimumSize(QSize(200, 0));
        regDateValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(regDateValueLabel);

        lastLoginLabel = new QLabel(memberIdWidget);
        lastLoginLabel->setObjectName(QStringLiteral("lastLoginLabel"));

        horizontalLayout_4->addWidget(lastLoginLabel);

        lastLoginValueLabel = new QLabel(memberIdWidget);
        lastLoginValueLabel->setObjectName(QStringLiteral("lastLoginValueLabel"));
        lastLoginValueLabel->setMinimumSize(QSize(200, 0));
        lastLoginValueLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(lastLoginValueLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        imageLabel = new QLabel(memberIdWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy2);
        imageLabel->setMinimumSize(QSize(80, 80));
        imageLabel->setMaximumSize(QSize(80, 80));

        horizontalLayout_4->addWidget(imageLabel);

        imagePushButton = new QPushButton(memberIdWidget);
        imagePushButton->setObjectName(QStringLiteral("imagePushButton"));

        horizontalLayout_4->addWidget(imagePushButton);


        verticalLayout->addWidget(memberIdWidget);

        widget = new QWidget(MemberView);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_20 = new QHBoxLayout(widget);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        usernameWidget = new QWidget(widget_2);
        usernameWidget->setObjectName(QStringLiteral("usernameWidget"));
        horizontalLayout_5 = new QHBoxLayout(usernameWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        usernameLabel = new QLabel(usernameWidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        horizontalLayout_5->addWidget(usernameLabel);

        usernameLineEdit = new QLineEdit(usernameWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        horizontalLayout_5->addWidget(usernameLineEdit);

        horizontalSpacer_5 = new QSpacerItem(436, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_2->addWidget(usernameWidget);

        nameFormWidget = new QWidget(widget_2);
        nameFormWidget->setObjectName(QStringLiteral("nameFormWidget"));
        horizontalLayout_3 = new QHBoxLayout(nameFormWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        nameLabel = new QLabel(nameFormWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout_3->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(nameFormWidget);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setMinimumSize(QSize(500, 0));
        nameLineEdit->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_3->addWidget(nameLineEdit);

        horizontalSpacer_2 = new QSpacerItem(332, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(nameFormWidget);

        memberSurnameWidget = new QWidget(widget_2);
        memberSurnameWidget->setObjectName(QStringLiteral("memberSurnameWidget"));
        horizontalLayout_6 = new QHBoxLayout(memberSurnameWidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        memberSurnameLabel = new QLabel(memberSurnameWidget);
        memberSurnameLabel->setObjectName(QStringLiteral("memberSurnameLabel"));

        horizontalLayout_6->addWidget(memberSurnameLabel);

        memberSurnameLineEdit = new QLineEdit(memberSurnameWidget);
        memberSurnameLineEdit->setObjectName(QStringLiteral("memberSurnameLineEdit"));
        memberSurnameLineEdit->setMinimumSize(QSize(500, 0));
        memberSurnameLineEdit->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_6->addWidget(memberSurnameLineEdit);

        horizontalSpacer_6 = new QSpacerItem(185, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_2->addWidget(memberSurnameWidget);

        bankAccountWidget = new QWidget(widget_2);
        bankAccountWidget->setObjectName(QStringLiteral("bankAccountWidget"));
        horizontalLayout_12 = new QHBoxLayout(bankAccountWidget);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        bankAccountLabel = new QLabel(bankAccountWidget);
        bankAccountLabel->setObjectName(QStringLiteral("bankAccountLabel"));

        horizontalLayout_12->addWidget(bankAccountLabel);

        bankAccountLineEdit = new QLineEdit(bankAccountWidget);
        bankAccountLineEdit->setObjectName(QStringLiteral("bankAccountLineEdit"));
        bankAccountLineEdit->setMinimumSize(QSize(500, 0));
        bankAccountLineEdit->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_12->addWidget(bankAccountLineEdit);

        horizontalSpacer_12 = new QSpacerItem(152, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_12);


        verticalLayout_2->addWidget(bankAccountWidget);

        birthdateWidget = new QWidget(widget_2);
        birthdateWidget->setObjectName(QStringLiteral("birthdateWidget"));
        horizontalLayout_8 = new QHBoxLayout(birthdateWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        birthdateLabel = new QLabel(birthdateWidget);
        birthdateLabel->setObjectName(QStringLiteral("birthdateLabel"));

        horizontalLayout_8->addWidget(birthdateLabel);

        birthdateDateEdit = new QDateEdit(birthdateWidget);
        birthdateDateEdit->setObjectName(QStringLiteral("birthdateDateEdit"));
        birthdateDateEdit->setCalendarPopup(true);

        horizontalLayout_8->addWidget(birthdateDateEdit);

        horizontalSpacer_8 = new QSpacerItem(376, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_2->addWidget(birthdateWidget);

        emailWidget = new QWidget(widget_2);
        emailWidget->setObjectName(QStringLiteral("emailWidget"));
        horizontalLayout_16 = new QHBoxLayout(emailWidget);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        emailLabel = new QLabel(emailWidget);
        emailLabel->setObjectName(QStringLiteral("emailLabel"));

        horizontalLayout_16->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(emailWidget);
        emailLineEdit->setObjectName(QStringLiteral("emailLineEdit"));
        emailLineEdit->setMinimumSize(QSize(500, 0));
        emailLineEdit->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_16->addWidget(emailLineEdit);

        horizontalSpacer_16 = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_16);


        verticalLayout_2->addWidget(emailWidget);

        addressWidget = new QWidget(widget_2);
        addressWidget->setObjectName(QStringLiteral("addressWidget"));
        horizontalLayout_9 = new QHBoxLayout(addressWidget);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        addressLabel = new QLabel(addressWidget);
        addressLabel->setObjectName(QStringLiteral("addressLabel"));

        horizontalLayout_9->addWidget(addressLabel);

        addressLineEdit = new QLineEdit(addressWidget);
        addressLineEdit->setObjectName(QStringLiteral("addressLineEdit"));
        addressLineEdit->setMinimumSize(QSize(500, 0));
        addressLineEdit->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_9->addWidget(addressLineEdit);

        horizontalSpacer_9 = new QSpacerItem(190, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);


        verticalLayout_2->addWidget(addressWidget);

        zipCodeWidget = new QWidget(widget_2);
        zipCodeWidget->setObjectName(QStringLiteral("zipCodeWidget"));
        horizontalLayout_10 = new QHBoxLayout(zipCodeWidget);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        zipCodeLabel = new QLabel(zipCodeWidget);
        zipCodeLabel->setObjectName(QStringLiteral("zipCodeLabel"));

        horizontalLayout_10->addWidget(zipCodeLabel);

        zipCodeLineEdit = new QLineEdit(zipCodeWidget);
        zipCodeLineEdit->setObjectName(QStringLiteral("zipCodeLineEdit"));

        horizontalLayout_10->addWidget(zipCodeLineEdit);

        horizontalSpacer_10 = new QSpacerItem(341, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);


        verticalLayout_2->addWidget(zipCodeWidget);

        townWidget = new QWidget(widget_2);
        townWidget->setObjectName(QStringLiteral("townWidget"));
        horizontalLayout_11 = new QHBoxLayout(townWidget);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        townLabel = new QLabel(townWidget);
        townLabel->setObjectName(QStringLiteral("townLabel"));

        horizontalLayout_11->addWidget(townLabel);

        townLineEdit = new QLineEdit(townWidget);
        townLineEdit->setObjectName(QStringLiteral("townLineEdit"));
        townLineEdit->setMinimumSize(QSize(400, 0));
        townLineEdit->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_11->addWidget(townLineEdit);

        horizontalSpacer_11 = new QSpacerItem(352, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);


        verticalLayout_2->addWidget(townWidget);

        stateWidget = new QWidget(widget_2);
        stateWidget->setObjectName(QStringLiteral("stateWidget"));
        horizontalLayout_13 = new QHBoxLayout(stateWidget);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        stateLabel = new QLabel(stateWidget);
        stateLabel->setObjectName(QStringLiteral("stateLabel"));

        horizontalLayout_13->addWidget(stateLabel);

        stateLineEdit = new QLineEdit(stateWidget);
        stateLineEdit->setObjectName(QStringLiteral("stateLineEdit"));

        horizontalLayout_13->addWidget(stateLineEdit);

        horizontalSpacer_13 = new QSpacerItem(353, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_13);


        verticalLayout_2->addWidget(stateWidget);

        phoneWidget = new QWidget(widget_2);
        phoneWidget->setObjectName(QStringLiteral("phoneWidget"));
        horizontalLayout_14 = new QHBoxLayout(phoneWidget);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        phoneLabel = new QLabel(phoneWidget);
        phoneLabel->setObjectName(QStringLiteral("phoneLabel"));

        horizontalLayout_14->addWidget(phoneLabel);

        phoneLineEdit = new QLineEdit(phoneWidget);
        phoneLineEdit->setObjectName(QStringLiteral("phoneLineEdit"));

        horizontalLayout_14->addWidget(phoneLineEdit);

        horizontalSpacer_14 = new QSpacerItem(349, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_14);


        verticalLayout_2->addWidget(phoneWidget);

        phone2Widget = new QWidget(widget_2);
        phone2Widget->setObjectName(QStringLiteral("phone2Widget"));
        horizontalLayout_15 = new QHBoxLayout(phone2Widget);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        phone2Label = new QLabel(phone2Widget);
        phone2Label->setObjectName(QStringLiteral("phone2Label"));

        horizontalLayout_15->addWidget(phone2Label);

        phone2LineEdit = new QLineEdit(phone2Widget);
        phone2LineEdit->setObjectName(QStringLiteral("phone2LineEdit"));

        horizontalLayout_15->addWidget(phone2LineEdit);

        horizontalSpacer_15 = new QSpacerItem(345, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_15);


        verticalLayout_2->addWidget(phone2Widget);

        usernameWidget->raise();
        nameFormWidget->raise();
        memberSurnameWidget->raise();
        bankAccountWidget->raise();
        birthdateWidget->raise();
        emailWidget->raise();
        addressWidget->raise();
        zipCodeWidget->raise();
        townWidget->raise();
        stateWidget->raise();
        phoneWidget->raise();
        phone2Widget->raise();

        horizontalLayout_20->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(300, 0));
        widget_3->setMaximumSize(QSize(300, 16777215));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        notesLabelwidget = new QWidget(widget_3);
        notesLabelwidget->setObjectName(QStringLiteral("notesLabelwidget"));
        horizontalLayout_19 = new QHBoxLayout(notesLabelwidget);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        notesLabel = new QLabel(notesLabelwidget);
        notesLabel->setObjectName(QStringLiteral("notesLabel"));

        horizontalLayout_19->addWidget(notesLabel);

        horizontalSpacer_19 = new QSpacerItem(910, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_19);


        verticalLayout_3->addWidget(notesLabelwidget);

        notesWidget = new QWidget(widget_3);
        notesWidget->setObjectName(QStringLiteral("notesWidget"));
        verticalLayout_4 = new QVBoxLayout(notesWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        notesTextEdit = new QTextEdit(notesWidget);
        notesTextEdit->setObjectName(QStringLiteral("notesTextEdit"));
        notesTextEdit->setMinimumSize(QSize(0, 300));
        notesTextEdit->setMaximumSize(QSize(16777215, 300));

        verticalLayout_4->addWidget(notesTextEdit);

        activeWidget = new QWidget(notesWidget);
        activeWidget->setObjectName(QStringLiteral("activeWidget"));
        horizontalLayout_2 = new QHBoxLayout(activeWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        activeCheckBox = new QCheckBox(activeWidget);
        activeCheckBox->setObjectName(QStringLiteral("activeCheckBox"));

        horizontalLayout_2->addWidget(activeCheckBox);

        horizontalSpacer_3 = new QSpacerItem(682, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_4->addWidget(activeWidget);

        isAdminWidget = new QWidget(notesWidget);
        isAdminWidget->setObjectName(QStringLiteral("isAdminWidget"));
        horizontalLayout_7 = new QHBoxLayout(isAdminWidget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        isAdminCheckBox = new QCheckBox(isAdminWidget);
        isAdminCheckBox->setObjectName(QStringLiteral("isAdminCheckBox"));

        horizontalLayout_7->addWidget(isAdminCheckBox);

        horizontalSpacer_7 = new QSpacerItem(681, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout_4->addWidget(isAdminWidget);

        postalSendWidget = new QWidget(notesWidget);
        postalSendWidget->setObjectName(QStringLiteral("postalSendWidget"));
        horizontalLayout_17 = new QHBoxLayout(postalSendWidget);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        postalSendCheckBox = new QCheckBox(postalSendWidget);
        postalSendCheckBox->setObjectName(QStringLiteral("postalSendCheckBox"));

        horizontalLayout_17->addWidget(postalSendCheckBox);

        horizontalSpacer_17 = new QSpacerItem(645, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_17);


        verticalLayout_4->addWidget(postalSendWidget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        verticalLayout_3->addWidget(notesWidget);


        horizontalLayout_20->addWidget(widget_3);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(MemberView);

        QMetaObject::connectSlotsByName(MemberView);
    } // setupUi

    void retranslateUi(QWidget *MemberView)
    {
        MemberView->setWindowTitle(QApplication::translate("MemberView", "Member View", 0));
        titleLabel->setText(QApplication::translate("MemberView", "Member Detail View", 0));
        changePasswordPushButton->setText(QApplication::translate("MemberView", "change password", 0));
        savePushButton->setText(QApplication::translate("MemberView", "Save", 0));
        memberIdValueLabel->setText(QApplication::translate("MemberView", "0", 0));
        regDateLabel->setText(QApplication::translate("MemberView", "Registration Date:", 0));
        regDateValueLabel->setText(QApplication::translate("MemberView", "12-01-2015", 0));
        lastLoginLabel->setText(QApplication::translate("MemberView", "Last Login Date:", 0));
        lastLoginValueLabel->setText(QApplication::translate("MemberView", "01-05-2015", 0));
        imageLabel->setText(QApplication::translate("MemberView", "TextLabel", 0));
        imagePushButton->setText(QApplication::translate("MemberView", "Image", 0));
        usernameLabel->setText(QApplication::translate("MemberView", "Username:", 0));
        nameLabel->setText(QApplication::translate("MemberView", "Name:", 0));
        memberSurnameLabel->setText(QApplication::translate("MemberView", "Surname:", 0));
        bankAccountLabel->setText(QApplication::translate("MemberView", "Bank Account:", 0));
        birthdateLabel->setText(QApplication::translate("MemberView", "BirthDate:", 0));
        birthdateDateEdit->setDisplayFormat(QApplication::translate("MemberView", "dd/MM/yyyy", 0));
        emailLabel->setText(QApplication::translate("MemberView", "Email:", 0));
        addressLabel->setText(QApplication::translate("MemberView", "Address:", 0));
        zipCodeLabel->setText(QApplication::translate("MemberView", "Zip Code:", 0));
        townLabel->setText(QApplication::translate("MemberView", "Town:", 0));
        stateLabel->setText(QApplication::translate("MemberView", "State:", 0));
        phoneLabel->setText(QApplication::translate("MemberView", "Phone:", 0));
        phone2Label->setText(QApplication::translate("MemberView", "Phone2:", 0));
        notesLabel->setText(QApplication::translate("MemberView", "Notes:", 0));
        activeCheckBox->setText(QApplication::translate("MemberView", "Active", 0));
        isAdminCheckBox->setText(QApplication::translate("MemberView", "Admin", 0));
        postalSendCheckBox->setText(QApplication::translate("MemberView", "Postal Send", 0));
    } // retranslateUi

};

namespace Ui {
    class MemberView: public Ui_MemberView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERVIEW_H
