/********************************************************************************
** Form generated from reading UI file 'memberprofilegroupbox.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERPROFILEGROUPBOX_H
#define UI_MEMBERPROFILEGROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemberProfileGroupBox
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *memberImageLabel;
    QWidget *memberInfoWidget;
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QWidget *memberUsernameWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *memberUsernameLabel;
    QLabel *memberUsernameValueLabel;
    QWidget *memberAccountWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *memberAccountLabel;
    QLabel *memberAccountValueLabel;

    void setupUi(QGroupBox *MemberProfileGroupBox)
    {
        if (MemberProfileGroupBox->objectName().isEmpty())
            MemberProfileGroupBox->setObjectName(QStringLiteral("MemberProfileGroupBox"));
        MemberProfileGroupBox->resize(300, 300);
        MemberProfileGroupBox->setMinimumSize(QSize(300, 0));
        MemberProfileGroupBox->setMaximumSize(QSize(300, 16777215));
        horizontalLayout = new QHBoxLayout(MemberProfileGroupBox);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 4, 4, 4);
        memberImageLabel = new QLabel(MemberProfileGroupBox);
        memberImageLabel->setObjectName(QStringLiteral("memberImageLabel"));
        memberImageLabel->setMinimumSize(QSize(80, 80));
        memberImageLabel->setMaximumSize(QSize(80, 80));
        memberImageLabel->setText(QStringLiteral("TextLabel"));

        horizontalLayout->addWidget(memberImageLabel);

        memberInfoWidget = new QWidget(MemberProfileGroupBox);
        memberInfoWidget->setObjectName(QStringLiteral("memberInfoWidget"));
        verticalLayout = new QVBoxLayout(memberInfoWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        nameLabel = new QLabel(memberInfoWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setText(QStringLiteral("TextLabel"));

        verticalLayout->addWidget(nameLabel);

        memberUsernameWidget = new QWidget(memberInfoWidget);
        memberUsernameWidget->setObjectName(QStringLiteral("memberUsernameWidget"));
        horizontalLayout_3 = new QHBoxLayout(memberUsernameWidget);
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 1, 1, 1);
        memberUsernameLabel = new QLabel(memberUsernameWidget);
        memberUsernameLabel->setObjectName(QStringLiteral("memberUsernameLabel"));

        horizontalLayout_3->addWidget(memberUsernameLabel);

        memberUsernameValueLabel = new QLabel(memberUsernameWidget);
        memberUsernameValueLabel->setObjectName(QStringLiteral("memberUsernameValueLabel"));
        memberUsernameValueLabel->setText(QStringLiteral("TextLabel"));

        horizontalLayout_3->addWidget(memberUsernameValueLabel);


        verticalLayout->addWidget(memberUsernameWidget);

        memberAccountWidget = new QWidget(memberInfoWidget);
        memberAccountWidget->setObjectName(QStringLiteral("memberAccountWidget"));
        horizontalLayout_2 = new QHBoxLayout(memberAccountWidget);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        memberAccountLabel = new QLabel(memberAccountWidget);
        memberAccountLabel->setObjectName(QStringLiteral("memberAccountLabel"));

        horizontalLayout_2->addWidget(memberAccountLabel);

        memberAccountValueLabel = new QLabel(memberAccountWidget);
        memberAccountValueLabel->setObjectName(QStringLiteral("memberAccountValueLabel"));
        memberAccountValueLabel->setText(QStringLiteral("TextLabel"));

        horizontalLayout_2->addWidget(memberAccountValueLabel);


        verticalLayout->addWidget(memberAccountWidget);


        horizontalLayout->addWidget(memberInfoWidget);


        retranslateUi(MemberProfileGroupBox);

        QMetaObject::connectSlotsByName(MemberProfileGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *MemberProfileGroupBox)
    {
        MemberProfileGroupBox->setWindowTitle(QApplication::translate("MemberProfileGroupBox", "GroupBox", 0));
        MemberProfileGroupBox->setTitle(QApplication::translate("MemberProfileGroupBox", "Member", 0));
        memberUsernameLabel->setText(QApplication::translate("MemberProfileGroupBox", "Username:", 0));
        memberAccountLabel->setText(QApplication::translate("MemberProfileGroupBox", "Balance:", 0));
    } // retranslateUi

};

namespace Ui {
    class MemberProfileGroupBox: public Ui_MemberProfileGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERPROFILEGROUPBOX_H
