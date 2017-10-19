/********************************************************************************
** Form generated from reading UI file 'productitemwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTITEMWIDGET_H
#define UI_PRODUCTITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *imageQLabel;
    QWidget *infoWidget;
    QVBoxLayout *verticalLayout;
    QLabel *nameQLabel;
    QLabel *priceQLabel;

    void setupUi(QWidget *ProductItemWidget)
    {
        if (ProductItemWidget->objectName().isEmpty())
            ProductItemWidget->setObjectName(QStringLiteral("ProductItemWidget"));
        ProductItemWidget->resize(156, 50);
        ProductItemWidget->setMinimumSize(QSize(156, 50));
        ProductItemWidget->setWindowTitle(QStringLiteral("Form"));
        horizontalLayout = new QHBoxLayout(ProductItemWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        imageQLabel = new QLabel(ProductItemWidget);
        imageQLabel->setObjectName(QStringLiteral("imageQLabel"));
        imageQLabel->setMinimumSize(QSize(40, 0));
        imageQLabel->setMaximumSize(QSize(40, 16777215));
        imageQLabel->setScaledContents(true);

        horizontalLayout->addWidget(imageQLabel);

        infoWidget = new QWidget(ProductItemWidget);
        infoWidget->setObjectName(QStringLiteral("infoWidget"));
        infoWidget->setMinimumSize(QSize(0, 0));
        infoWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(infoWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 3, 0, 3);
        nameQLabel = new QLabel(infoWidget);
        nameQLabel->setObjectName(QStringLiteral("nameQLabel"));
        nameQLabel->setText(QStringLiteral("TextLabel"));

        verticalLayout->addWidget(nameQLabel);

        priceQLabel = new QLabel(infoWidget);
        priceQLabel->setObjectName(QStringLiteral("priceQLabel"));
        priceQLabel->setText(QStringLiteral("TextLabel"));

        verticalLayout->addWidget(priceQLabel);


        horizontalLayout->addWidget(infoWidget);


        retranslateUi(ProductItemWidget);

        QMetaObject::connectSlotsByName(ProductItemWidget);
    } // setupUi

    void retranslateUi(QWidget *ProductItemWidget)
    {
        imageQLabel->setText(QApplication::translate("ProductItemWidget", "TextLabel", 0));
        Q_UNUSED(ProductItemWidget);
    } // retranslateUi

};

namespace Ui {
    class ProductItemWidget: public Ui_ProductItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTITEMWIDGET_H
