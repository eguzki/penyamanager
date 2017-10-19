/********************************************************************************
** Form generated from reading UI file 'familyitemwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAMILYITEMWIDGET_H
#define UI_FAMILYITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FamilyItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *imageQLabel;
    QLabel *textQLabel;

    void setupUi(QWidget *FamilyItemWidget)
    {
        if (FamilyItemWidget->objectName().isEmpty())
            FamilyItemWidget->setObjectName(QStringLiteral("FamilyItemWidget"));
        FamilyItemWidget->resize(295, 40);
        FamilyItemWidget->setMinimumSize(QSize(295, 40));
        FamilyItemWidget->setMaximumSize(QSize(295, 40));
        horizontalLayout = new QHBoxLayout(FamilyItemWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        imageQLabel = new QLabel(FamilyItemWidget);
        imageQLabel->setObjectName(QStringLiteral("imageQLabel"));
        imageQLabel->setMinimumSize(QSize(40, 0));
        imageQLabel->setMaximumSize(QSize(40, 16777215));
        imageQLabel->setText(QStringLiteral("TextLabel"));
        imageQLabel->setScaledContents(true);

        horizontalLayout->addWidget(imageQLabel);

        textQLabel = new QLabel(FamilyItemWidget);
        textQLabel->setObjectName(QStringLiteral("textQLabel"));

        horizontalLayout->addWidget(textQLabel);


        retranslateUi(FamilyItemWidget);

        QMetaObject::connectSlotsByName(FamilyItemWidget);
    } // setupUi

    void retranslateUi(QWidget *FamilyItemWidget)
    {
        FamilyItemWidget->setWindowTitle(QApplication::translate("FamilyItemWidget", "Form", 0));
        textQLabel->setText(QApplication::translate("FamilyItemWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class FamilyItemWidget: public Ui_FamilyItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAMILYITEMWIDGET_H
