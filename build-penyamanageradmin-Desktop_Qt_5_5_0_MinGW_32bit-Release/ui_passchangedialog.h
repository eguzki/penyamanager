/********************************************************************************
** Form generated from reading UI file 'passchangedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSCHANGEDIALOG_H
#define UI_PASSCHANGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PassChangeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *pwdLineEdit;
    QLabel *label_2;
    QLineEdit *repeatedPwdLineEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PassChangeDialog)
    {
        if (PassChangeDialog->objectName().isEmpty())
            PassChangeDialog->setObjectName(QStringLiteral("PassChangeDialog"));
        PassChangeDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(PassChangeDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(PassChangeDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        pwdLineEdit = new QLineEdit(PassChangeDialog);
        pwdLineEdit->setObjectName(QStringLiteral("pwdLineEdit"));
        pwdLineEdit->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(pwdLineEdit);

        label_2 = new QLabel(PassChangeDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        repeatedPwdLineEdit = new QLineEdit(PassChangeDialog);
        repeatedPwdLineEdit->setObjectName(QStringLiteral("repeatedPwdLineEdit"));
        repeatedPwdLineEdit->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(repeatedPwdLineEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(PassChangeDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(PassChangeDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), PassChangeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PassChangeDialog);
    } // setupUi

    void retranslateUi(QDialog *PassChangeDialog)
    {
        PassChangeDialog->setWindowTitle(QApplication::translate("PassChangeDialog", "Dialog", 0));
        label->setText(QApplication::translate("PassChangeDialog", "Password", 0));
        label_2->setText(QApplication::translate("PassChangeDialog", "Repeat Password", 0));
    } // retranslateUi

};

namespace Ui {
    class PassChangeDialog: public Ui_PassChangeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSCHANGEDIALOG_H
