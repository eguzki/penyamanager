/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QWidget *penyaLabel;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QWidget *lastInvoiceWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_5;
    QWidget *lastMemberWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *memberNameLabel;
    QWidget *memberIdWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *memberIdFixedLabel;
    QLabel *memberIdLabel;
    QLabel *memberImageLabel;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QWidget *lastInvoiceInfoWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *lastInvoiceDateLabel;
    QTableWidget *lastInvoiceTableWidget;
    QLabel *lastInvoiceTotalLabel;
    QWidget *loginWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *languagePushButton;
    QPushButton *loginPushButton;
    QWidget *versionWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *versionLabel;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(934, 635);
        LoginWindow->setWindowTitle(QStringLiteral(""));
        LoginWindow->setStyleSheet(QLatin1String("QTableWidget{\n"
"background: rgb(189,189,189);\n"
"font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"QListWidget{\n"
"background: rgb(158,158,158);\n"
"font-size: 20px;\n"
"}\n"
"\n"
"#LoginWindow {\n"
"background: rgb(66, 66, 66);\n"
"}\n"
"\n"
"#imageWidget{\n"
"background-image: url(\":/images/alegrialogo.png\");\n"
"}\n"
"\n"
"#penyaLabel * {\n"
"color: white;\n"
"font: 75 46pt \"Navarre\";\n"
"}\n"
"\n"
"#label{\n"
"font: 75 25pt \"Navarre\";\n"
"}\n"
"\n"
"#label_2{\n"
"font: 75 25pt \"Navarre\";\n"
"}\n"
"\n"
"#memberIdFixedLabel{\n"
"font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"#memberIdLabel{\n"
"font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"#memberImageLabel{\n"
"font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"#memberNameLabel{\n"
"font: 18pt \"Calibri\";\n"
"}\n"
"\n"
"#lastInvoiceWidget *{\n"
"color: black;\n"
"}\n"
"\n"
"#languagePushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-radius: 0;\n"
"padding: 3px;\n"
"font: 75 20pt \"Calibri\";\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"m"
                        "in-width: 50px;\n"
"max-width: 100px;\n"
"min-height: 13px;\n"
"max-height: 120px;\n"
"}\n"
"\n"
"#loginPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-radius: 0;\n"
"padding: 3px;\n"
"font: 75 48pt \"Calibri\";\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 50px;\n"
"/*max-width: 800px;*/\n"
"min-height: 13px;\n"
"max-height: 120px;\n"
"}\n"
"\n"
"#lastInvoiceInfoWidget {\n"
"border: 1px solid gray;\n"
"border-radius: 0px;\n"
"background: rgb(158,158,158);\n"
"}\n"
"\n"
"#lastMemberWidget {\n"
"border: 1px solid gray;\n"
"border-radius: 0px;\n"
"background: rgb(158,158,158);\n"
"}\n"
"\n"
"#memberIdLabel {\n"
"font-weight: bold;\n"
"font-size: 15px;\n"
"}\n"
"\n"
"#memberNameLabel {\n"
"font-weight: bold;\n"
"font-size: 15px;\n"
"qproperty-alignment: AlignCenter;\n"
"}\n"
"\n"
"#lastInvoiceTotalLabel {\n"
"font-weight: bold;\n"
"font-size: 35px;\n"
"}\n"
""));
        LoginWindow->setLocale(QLocale(QLocale::Spanish, QLocale::Spain));
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        topFrame = new QFrame(LoginWindow);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        topFrame->setMinimumSize(QSize(0, 180));
        topFrame->setMaximumSize(QSize(16777215, 180));
        horizontalLayout = new QHBoxLayout(topFrame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(30, 17, 30, -1);
        penyaLabel = new QWidget(topFrame);
        penyaLabel->setObjectName(QStringLiteral("penyaLabel"));
        penyaLabel->setMinimumSize(QSize(700, 0));
        QFont font;
        font.setFamily(QStringLiteral("Navarre"));
        font.setPointSize(30);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        penyaLabel->setFont(font);
        verticalLayout_4 = new QVBoxLayout(penyaLabel);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label = new QLabel(penyaLabel);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 35));
        QFont font1;
        font1.setFamily(QStringLiteral("Navarre"));
        font1.setPointSize(25);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label->setFont(font1);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_4->addWidget(label);

        label_3 = new QLabel(penyaLabel);
        label_3->setObjectName(QStringLiteral("label_3"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        label_3->setPalette(palette);
        QFont font2;
        font2.setFamily(QStringLiteral("Navarre"));
        font2.setPointSize(46);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(9);
        label_3->setFont(font2);
        label_3->setText(QString::fromUtf8("Alegr\303\255a de Iru\303\261a"));
        label_3->setTextFormat(Qt::AutoText);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_3);

        label_2 = new QLabel(penyaLabel);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 35));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_4->addWidget(label_2);


        horizontalLayout->addWidget(penyaLabel);


        verticalLayout->addWidget(topFrame);

        lastInvoiceWidget = new QWidget(LoginWindow);
        lastInvoiceWidget->setObjectName(QStringLiteral("lastInvoiceWidget"));
        horizontalLayout_2 = new QHBoxLayout(lastInvoiceWidget);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(30, 3, 30, 3);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        lastMemberWidget = new QWidget(lastInvoiceWidget);
        lastMemberWidget->setObjectName(QStringLiteral("lastMemberWidget"));
        lastMemberWidget->setMinimumSize(QSize(250, 0));
        lastMemberWidget->setMaximumSize(QSize(250, 350));
        verticalLayout_2 = new QVBoxLayout(lastMemberWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, -1, -1, -1);
        memberNameLabel = new QLabel(lastMemberWidget);
        memberNameLabel->setObjectName(QStringLiteral("memberNameLabel"));
        memberNameLabel->setMinimumSize(QSize(0, 30));
        memberNameLabel->setMaximumSize(QSize(16777215, 30));
        memberNameLabel->setText(QStringLiteral("Name"));

        verticalLayout_2->addWidget(memberNameLabel);

        memberIdWidget = new QWidget(lastMemberWidget);
        memberIdWidget->setObjectName(QStringLiteral("memberIdWidget"));
        horizontalLayout_3 = new QHBoxLayout(memberIdWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        memberIdFixedLabel = new QLabel(memberIdWidget);
        memberIdFixedLabel->setObjectName(QStringLiteral("memberIdFixedLabel"));

        horizontalLayout_3->addWidget(memberIdFixedLabel);

        memberIdLabel = new QLabel(memberIdWidget);
        memberIdLabel->setObjectName(QStringLiteral("memberIdLabel"));
        memberIdLabel->setMinimumSize(QSize(0, 0));
        memberIdLabel->setMaximumSize(QSize(16777215, 30));
        memberIdLabel->setText(QStringLiteral("ID"));

        horizontalLayout_3->addWidget(memberIdLabel);


        verticalLayout_2->addWidget(memberIdWidget);

        memberImageLabel = new QLabel(lastMemberWidget);
        memberImageLabel->setObjectName(QStringLiteral("memberImageLabel"));
        memberImageLabel->setMinimumSize(QSize(160, 160));
        memberImageLabel->setMaximumSize(QSize(160, 160));
        memberImageLabel->setText(QStringLiteral("picture"));

        verticalLayout_2->addWidget(memberImageLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout_5->addWidget(lastMemberWidget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        lastInvoiceInfoWidget = new QWidget(lastInvoiceWidget);
        lastInvoiceInfoWidget->setObjectName(QStringLiteral("lastInvoiceInfoWidget"));
        lastInvoiceInfoWidget->setMaximumSize(QSize(450, 16777215));
        verticalLayout_3 = new QVBoxLayout(lastInvoiceInfoWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lastInvoiceDateLabel = new QLabel(lastInvoiceInfoWidget);
        lastInvoiceDateLabel->setObjectName(QStringLiteral("lastInvoiceDateLabel"));
        lastInvoiceDateLabel->setMinimumSize(QSize(0, 30));
        lastInvoiceDateLabel->setMaximumSize(QSize(16777215, 30));
        lastInvoiceDateLabel->setLayoutDirection(Qt::LeftToRight);
        lastInvoiceDateLabel->setText(QStringLiteral("TextLabel"));
        lastInvoiceDateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(lastInvoiceDateLabel);

        lastInvoiceTableWidget = new QTableWidget(lastInvoiceInfoWidget);
        lastInvoiceTableWidget->setObjectName(QStringLiteral("lastInvoiceTableWidget"));
        lastInvoiceTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lastInvoiceTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        lastInvoiceTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(lastInvoiceTableWidget);

        lastInvoiceTotalLabel = new QLabel(lastInvoiceInfoWidget);
        lastInvoiceTotalLabel->setObjectName(QStringLiteral("lastInvoiceTotalLabel"));
        lastInvoiceTotalLabel->setMinimumSize(QSize(0, 30));
        lastInvoiceTotalLabel->setMaximumSize(QSize(16777215, 30));
        lastInvoiceTotalLabel->setText(QStringLiteral("TextLabel"));
        lastInvoiceTotalLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(lastInvoiceTotalLabel);


        horizontalLayout_2->addWidget(lastInvoiceInfoWidget);


        verticalLayout->addWidget(lastInvoiceWidget);

        loginWidget = new QWidget(LoginWindow);
        loginWidget->setObjectName(QStringLiteral("loginWidget"));
        loginWidget->setMinimumSize(QSize(0, 120));
        loginWidget->setMaximumSize(QSize(16777215, 120));
        horizontalLayout_4 = new QHBoxLayout(loginWidget);
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(30, 3, 30, 3);
        horizontalSpacer_2 = new QSpacerItem(260, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        languagePushButton = new QPushButton(loginWidget);
        languagePushButton->setObjectName(QStringLiteral("languagePushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(languagePushButton->sizePolicy().hasHeightForWidth());
        languagePushButton->setSizePolicy(sizePolicy);
        languagePushButton->setMinimumSize(QSize(62, 21));
        languagePushButton->setMaximumSize(QSize(112, 128));
        languagePushButton->setText(QStringLiteral("Euskera"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ikurrina.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/espanola.jpg"), QSize(), QIcon::Normal, QIcon::On);
        languagePushButton->setIcon(icon);
        languagePushButton->setIconSize(QSize(142, 100));
        languagePushButton->setCheckable(true);

        horizontalLayout_4->addWidget(languagePushButton);

        loginPushButton = new QPushButton(loginWidget);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));
        sizePolicy.setHeightForWidth(loginPushButton->sizePolicy().hasHeightForWidth());
        loginPushButton->setSizePolicy(sizePolicy);
        loginPushButton->setMinimumSize(QSize(62, 21));

        horizontalLayout_4->addWidget(loginPushButton);


        verticalLayout->addWidget(loginWidget);

        versionWidget = new QWidget(LoginWindow);
        versionWidget->setObjectName(QStringLiteral("versionWidget"));
        versionWidget->setMinimumSize(QSize(0, 15));
        versionWidget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_5 = new QHBoxLayout(versionWidget);
        horizontalLayout_5->setSpacing(1);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(1, 1, 1, 1);
        versionLabel = new QLabel(versionWidget);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        versionLabel->setLayoutDirection(Qt::LeftToRight);
        versionLabel->setText(QStringLiteral("code build 1.0.0"));
        versionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(versionLabel);


        verticalLayout->addWidget(versionWidget);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        label->setText(QApplication::translate("LoginWindow", "SDRC", 0));
        label_2->setText(QApplication::translate("LoginWindow", "KKAE", 0));
        memberIdFixedLabel->setText(QApplication::translate("LoginWindow", "MemberId", 0));
        loginPushButton->setText(QApplication::translate("LoginWindow", "Login", 0));
        Q_UNUSED(LoginWindow);
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
