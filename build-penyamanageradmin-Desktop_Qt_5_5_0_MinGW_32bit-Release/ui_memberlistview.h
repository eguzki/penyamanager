/********************************************************************************
** Form generated from reading UI file 'memberlistview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBERLISTVIEW_H
#define UI_MEMBERLISTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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

class Ui_MemberListView
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *topFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *printPostalMembersPushButton;
    QPushButton *csvPushButton;
    QPushButton *newMemberPushButton;
    QFrame *resultsFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *filterPostalUsersFrame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *filterPostalUsersCheckBox;
    QFrame *pagingFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *totalMembersLabel;
    QLabel *totalMembersValueLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *prevPagePushButton;
    QLabel *pageInfoLabel;
    QPushButton *nextPagePushButton;
    QFrame *memberListFrame;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *memberTableWidget;

    void setupUi(QWidget *MemberListView)
    {
        if (MemberListView->objectName().isEmpty())
            MemberListView->setObjectName(QStringLiteral("MemberListView"));
        MemberListView->resize(800, 600);
        MemberListView->setStyleSheet(QLatin1String("#topFrame {\n"
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
        verticalLayout = new QVBoxLayout(MemberListView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topFrame = new QFrame(MemberListView);
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

        horizontalSpacer_5 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        printPostalMembersPushButton = new QPushButton(topFrame);
        printPostalMembersPushButton->setObjectName(QStringLiteral("printPostalMembersPushButton"));

        horizontalLayout->addWidget(printPostalMembersPushButton);

        csvPushButton = new QPushButton(topFrame);
        csvPushButton->setObjectName(QStringLiteral("csvPushButton"));

        horizontalLayout->addWidget(csvPushButton);

        newMemberPushButton = new QPushButton(topFrame);
        newMemberPushButton->setObjectName(QStringLiteral("newMemberPushButton"));

        horizontalLayout->addWidget(newMemberPushButton);


        verticalLayout->addWidget(topFrame);

        resultsFrame = new QFrame(MemberListView);
        resultsFrame->setObjectName(QStringLiteral("resultsFrame"));
        resultsFrame->setStyleSheet(QStringLiteral(""));
        resultsFrame->setFrameShape(QFrame::StyledPanel);
        resultsFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(resultsFrame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        filterPostalUsersFrame = new QFrame(resultsFrame);
        filterPostalUsersFrame->setObjectName(QStringLiteral("filterPostalUsersFrame"));
        filterPostalUsersFrame->setFrameShape(QFrame::StyledPanel);
        filterPostalUsersFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(filterPostalUsersFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(560, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        filterPostalUsersCheckBox = new QCheckBox(filterPostalUsersFrame);
        filterPostalUsersCheckBox->setObjectName(QStringLiteral("filterPostalUsersCheckBox"));

        horizontalLayout_2->addWidget(filterPostalUsersCheckBox);


        verticalLayout_3->addWidget(filterPostalUsersFrame);

        pagingFrame = new QFrame(resultsFrame);
        pagingFrame->setObjectName(QStringLiteral("pagingFrame"));
        pagingFrame->setFrameShape(QFrame::StyledPanel);
        pagingFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(pagingFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        totalMembersLabel = new QLabel(pagingFrame);
        totalMembersLabel->setObjectName(QStringLiteral("totalMembersLabel"));

        horizontalLayout_3->addWidget(totalMembersLabel);

        totalMembersValueLabel = new QLabel(pagingFrame);
        totalMembersValueLabel->setObjectName(QStringLiteral("totalMembersValueLabel"));
        totalMembersValueLabel->setMinimumSize(QSize(100, 0));
        totalMembersValueLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(totalMembersValueLabel);

        horizontalSpacer_3 = new QSpacerItem(376, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        prevPagePushButton = new QPushButton(pagingFrame);
        prevPagePushButton->setObjectName(QStringLiteral("prevPagePushButton"));

        horizontalLayout_3->addWidget(prevPagePushButton);

        pageInfoLabel = new QLabel(pagingFrame);
        pageInfoLabel->setObjectName(QStringLiteral("pageInfoLabel"));

        horizontalLayout_3->addWidget(pageInfoLabel);

        nextPagePushButton = new QPushButton(pagingFrame);
        nextPagePushButton->setObjectName(QStringLiteral("nextPagePushButton"));

        horizontalLayout_3->addWidget(nextPagePushButton);


        verticalLayout_3->addWidget(pagingFrame);

        memberListFrame = new QFrame(resultsFrame);
        memberListFrame->setObjectName(QStringLiteral("memberListFrame"));
        memberListFrame->setFrameShape(QFrame::StyledPanel);
        memberListFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(memberListFrame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        memberTableWidget = new QTableWidget(memberListFrame);
        memberTableWidget->setObjectName(QStringLiteral("memberTableWidget"));
        memberTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        memberTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        memberTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        memberTableWidget->horizontalHeader()->setVisible(true);
        memberTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(memberTableWidget);


        verticalLayout_3->addWidget(memberListFrame);


        verticalLayout->addWidget(resultsFrame);


        retranslateUi(MemberListView);

        QMetaObject::connectSlotsByName(MemberListView);
    } // setupUi

    void retranslateUi(QWidget *MemberListView)
    {
        MemberListView->setWindowTitle(QApplication::translate("MemberListView", "Form", 0));
        titleLabel->setText(QApplication::translate("MemberListView", "Member List", 0));
        printPostalMembersPushButton->setText(QApplication::translate("MemberListView", "print postal members", 0));
        csvPushButton->setText(QApplication::translate("MemberListView", "export to CSV", 0));
        newMemberPushButton->setText(QApplication::translate("MemberListView", "New Member", 0));
        filterPostalUsersCheckBox->setText(QApplication::translate("MemberListView", "only postal members", 0));
        totalMembersLabel->setText(QApplication::translate("MemberListView", "Total:", 0));
        totalMembersValueLabel->setText(QApplication::translate("MemberListView", "0", 0));
        prevPagePushButton->setText(QApplication::translate("MemberListView", "<", 0));
        pageInfoLabel->setText(QApplication::translate("MemberListView", "page X out of Y", 0));
        nextPagePushButton->setText(QApplication::translate("MemberListView", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class MemberListView: public Ui_MemberListView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBERLISTVIEW_H
