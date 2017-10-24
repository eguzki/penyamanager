/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 1024);
        MainWindow->setMinimumSize(QSize(1280, 1024));
        MainWindow->setMaximumSize(QSize(1280, 1024));
        MainWindow->setStyleSheet(QLatin1String("#MainWindow {\n"
"background: rgb(66, 66, 66);\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton {\n"
"color: white;\n"
"background-color: rgb(198, 40, 40);\n"
"border-width: 1px;\n"
"border-color: rgb(183, 28, 28);\n"
"border-style: solid;\n"
"border-radius: 0;\n"
"padding: 3px;\n"
"font-size: 27px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"\n"
"}\n"
"QPushButton:pressed {\n"
"background-color: rgb(239,83,80);\n"
"}\n"
"\n"
"\n"
"QLabel{\n"
"font: 12pt \"Calibri\";\n"
"color: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar:vertical {\n"
"    border: 1px solid #999999;\n"
"    background: rgb(158,158,158);\n"
"	width:15px;    \n"
"   margin: 0px 0px 0px 0px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"		stop: 0 rgb(239,83,80), stop: 0.5 rgb(239,83,80), stop:1 rgb(239,83,80));\n"
"        min-height: 0px;\n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"	background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"	stop: 0 rgb(239,83,80), stop: 0.5 rgb(239,83,80),  stop"
                        ":1 rgb(239,83,80));\n"
"	height: 0px;\n"
"	subcontrol-position: bottom;\n"
"	subcontrol-origin: margin;\n"
"}    \n"
"QScrollBar::sub-line:vertical {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"		stop: 0  rgb(239,83,80), stop: 0.5 rgbrgb(239,83,80),  stop:1 rgb(239,83,80));\n"
"        height: 0 px;\n"
"        subcontrol-position: top;\n"
"        subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    border: 1px solid #999999;\n"
"    background: rgb(158,158,158);\n"
"	height:2px;    \n"
"   margin: 0px 0px 0px 0px;\n"
"}\n"
"QScrollBar::handle:horizontal {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"		stop: 0 rgb(239,83,80), stop: 0.5 rgb(239,83,80), stop:1 rgb(239,83,80));\n"
"        min-height: 0px;\n"
"}\n"
"QScrollBar::add-line:horizontal {\n"
"	background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"	stop: 0 rgb(239,83,80), stop: 0.5 rgb(239,83,80),  stop:1 rgb(239,83,80));\n"
"	height: 0px;\n"
"	subcontrol-position: right;\n"
"	subcon"
                        "trol-origin: margin;\n"
"}    \n"
"QScrollBar::sub-line:horizontal {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"		stop: 0  rgb(239,83,80), stop: 0.5 rgbrgb(239,83,80),  stop:1 rgb(239,83,80));\n"
"        height: 0 px;\n"
"        subcontrol-position: left;\n"
"        subcontrol-origin: margin;\n"
"}"));
        MainWindow->setLocale(QLocale(QLocale::Spanish, QLocale::Spain));
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Penyamanager", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
