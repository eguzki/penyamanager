/********************************************************************************
** Form generated from reading UI file 'adminloginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINLOGINWINDOW_H
#define UI_ADMINLOGINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminLoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *imageWidget;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer_2;
    QWidget *loginWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *loginData;
    QFormLayout *formLayout;
    QLabel *loginLabel;
    QLineEdit *loginInput;
    QLabel *passLabel;
    QLineEdit *passInput;
    QWidget *paddingWidget;
    QWidget *loginwidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *languagePushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loginButton;
    QWidget *versionWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *versionLabel;

    void setupUi(QWidget *AdminLoginWindow)
    {
        if (AdminLoginWindow->objectName().isEmpty())
            AdminLoginWindow->setObjectName(QStringLiteral("AdminLoginWindow"));
        AdminLoginWindow->resize(800, 600);
        AdminLoginWindow->setMinimumSize(QSize(800, 600));
        AdminLoginWindow->setLocale(QLocale(QLocale::Spanish, QLocale::Spain));
        verticalLayout = new QVBoxLayout(AdminLoginWindow);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        topFrame = new QFrame(AdminLoginWindow);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        topFrame->setMinimumSize(QSize(0, 180));
        topFrame->setMaximumSize(QSize(16777215, 180));
        horizontalLayout = new QHBoxLayout(topFrame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        imageWidget = new QWidget(topFrame);
        imageWidget->setObjectName(QStringLiteral("imageWidget"));
        imageWidget->setMinimumSize(QSize(160, 0));
        imageWidget->setMaximumSize(QSize(160, 16777215));
        imageWidget->setStyleSheet(QStringLiteral("background-image: url(\":/images/alegrialogo.jpg\")"));

        horizontalLayout->addWidget(imageWidget);

        logoLabel = new QLabel(topFrame);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        QFont font;
        font.setPointSize(37);
        logoLabel->setFont(font);
        logoLabel->setText(QString::fromUtf8("<html><head/><body><p><span style=\" font-size:14pt;\">SDRC Alegr\303\255a de Iru\303\261ea KKAE</span></p></body></html>"));

        horizontalLayout->addWidget(logoLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(topFrame);

        loginWidget = new QWidget(AdminLoginWindow);
        loginWidget->setObjectName(QStringLiteral("loginWidget"));
        verticalLayout_2 = new QVBoxLayout(loginWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        loginData = new QWidget(loginWidget);
        loginData->setObjectName(QStringLiteral("loginData"));
        loginData->setMinimumSize(QSize(0, 200));
        loginData->setMaximumSize(QSize(16777215, 200));
        formLayout = new QFormLayout(loginData);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignCenter);
        loginLabel = new QLabel(loginData);
        loginLabel->setObjectName(QStringLiteral("loginLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, loginLabel);

        loginInput = new QLineEdit(loginData);
        loginInput->setObjectName(QStringLiteral("loginInput"));
        loginInput->setMaximumSize(QSize(300, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, loginInput);

        passLabel = new QLabel(loginData);
        passLabel->setObjectName(QStringLiteral("passLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, passLabel);

        passInput = new QLineEdit(loginData);
        passInput->setObjectName(QStringLiteral("passInput"));
        passInput->setMaximumSize(QSize(300, 16777215));
        passInput->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passInput);


        verticalLayout_2->addWidget(loginData);

        paddingWidget = new QWidget(loginWidget);
        paddingWidget->setObjectName(QStringLiteral("paddingWidget"));

        verticalLayout_2->addWidget(paddingWidget);

        loginwidget = new QWidget(loginWidget);
        loginwidget->setObjectName(QStringLiteral("loginwidget"));
        horizontalLayout_2 = new QHBoxLayout(loginwidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        languagePushButton = new QPushButton(loginwidget);
        languagePushButton->setObjectName(QStringLiteral("languagePushButton"));
        languagePushButton->setMinimumSize(QSize(0, 0));
        languagePushButton->setMaximumSize(QSize(16777215, 16777215));
        languagePushButton->setText(QStringLiteral("Euskera"));
        languagePushButton->setIconSize(QSize(80, 50));
        languagePushButton->setCheckable(true);

        horizontalLayout_2->addWidget(languagePushButton);

        horizontalSpacer_3 = new QSpacerItem(572, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        loginButton = new QPushButton(loginwidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setMinimumSize(QSize(99, 27));

        horizontalLayout_2->addWidget(loginButton);


        verticalLayout_2->addWidget(loginwidget);


        verticalLayout->addWidget(loginWidget);

        versionWidget = new QWidget(AdminLoginWindow);
        versionWidget->setObjectName(QStringLiteral("versionWidget"));
        versionWidget->setMinimumSize(QSize(0, 30));
        versionWidget->setMaximumSize(QSize(16777215, 20));
        horizontalLayout_3 = new QHBoxLayout(versionWidget);
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 1, 1, 1);
        versionLabel = new QLabel(versionWidget);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        QFont font1;
        font1.setPointSize(7);
        versionLabel->setFont(font1);
        versionLabel->setLayoutDirection(Qt::LeftToRight);
        versionLabel->setText(QStringLiteral("code build 1.0.0"));
        versionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(versionLabel);


        verticalLayout->addWidget(versionWidget);


        retranslateUi(AdminLoginWindow);

        QMetaObject::connectSlotsByName(AdminLoginWindow);
    } // setupUi

    void retranslateUi(QWidget *AdminLoginWindow)
    {
        AdminLoginWindow->setWindowTitle(QApplication::translate("AdminLoginWindow", "Penyamanager Application Manager", 0));
        loginLabel->setText(QApplication::translate("AdminLoginWindow", "Username", 0));
        passLabel->setText(QApplication::translate("AdminLoginWindow", "Password", 0));
        loginButton->setText(QApplication::translate("AdminLoginWindow", "Login", 0));
    } // retranslateUi

};

namespace Ui {
    class AdminLoginWindow: public Ui_AdminLoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINLOGINWINDOW_H
