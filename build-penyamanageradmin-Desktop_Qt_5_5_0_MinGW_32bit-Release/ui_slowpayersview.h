/********************************************************************************
** Form generated from reading UI file 'slowpayersview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLOWPAYERSVIEW_H
#define UI_SLOWPAYERSVIEW_H

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

class Ui_SlowPayersView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetAccountsPushButton;
    QPushButton *csvPushButton;
    QFrame *bottonFrame;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *slowPayersTableWidget;

    void setupUi(QWidget *SlowPayersView)
    {
        if (SlowPayersView->objectName().isEmpty())
            SlowPayersView->setObjectName(QStringLiteral("SlowPayersView"));
        SlowPayersView->resize(800, 600);
        SlowPayersView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(SlowPayersView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(SlowPayersView);
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

        resetAccountsPushButton = new QPushButton(topFrame);
        resetAccountsPushButton->setObjectName(QStringLiteral("resetAccountsPushButton"));

        horizontalLayout->addWidget(resetAccountsPushButton);

        csvPushButton = new QPushButton(topFrame);
        csvPushButton->setObjectName(QStringLiteral("csvPushButton"));

        horizontalLayout->addWidget(csvPushButton);


        verticalLayout->addWidget(topFrame);

        bottonFrame = new QFrame(SlowPayersView);
        bottonFrame->setObjectName(QStringLiteral("bottonFrame"));
        bottonFrame->setFrameShape(QFrame::StyledPanel);
        bottonFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(bottonFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        slowPayersTableWidget = new QTableWidget(bottonFrame);
        slowPayersTableWidget->setObjectName(QStringLiteral("slowPayersTableWidget"));
        slowPayersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        slowPayersTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        slowPayersTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);

        verticalLayout_2->addWidget(slowPayersTableWidget);


        verticalLayout->addWidget(bottonFrame);


        retranslateUi(SlowPayersView);

        QMetaObject::connectSlotsByName(SlowPayersView);
    } // setupUi

    void retranslateUi(QWidget *SlowPayersView)
    {
        SlowPayersView->setWindowTitle(QApplication::translate("SlowPayersView", "Form", 0));
        titleLabel->setText(QApplication::translate("SlowPayersView", "Slow Payer List", 0));
        resetAccountsPushButton->setText(QApplication::translate("SlowPayersView", "Reset accounts", 0));
        csvPushButton->setText(QApplication::translate("SlowPayersView", "export to CSV", 0));
    } // retranslateUi

};

namespace Ui {
    class SlowPayersView: public Ui_SlowPayersView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLOWPAYERSVIEW_H
