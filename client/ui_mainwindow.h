/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
// #include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRefresh;
    QAction *actionLOAD;
    QAction *actionQuerry;
    QAction *actionConnection;
    QAction *actionDisconnenct;
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuAbouy;
    QMenu *menuDatabase;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        actionLOAD = new QAction(MainWindow);
        actionLOAD->setObjectName(QString::fromUtf8("actionLOAD"));
        actionQuerry = new QAction(MainWindow);
        actionQuerry->setObjectName(QString::fromUtf8("actionQuerry"));
        actionConnection = new QAction(MainWindow);
        actionConnection->setObjectName(QString::fromUtf8("actionConnection"));
        actionDisconnenct = new QAction(MainWindow);
        actionDisconnenct->setObjectName(QString::fromUtf8("actionDisconnenct"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 190, 181, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menuAbouy = new QMenu(menubar);
        menuAbouy->setObjectName(QString::fromUtf8("menuAbouy"));
        menuDatabase = new QMenu(menubar);
        menuDatabase->setObjectName(QString::fromUtf8("menuDatabase"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuAbouy->menuAction());
        menubar->addAction(menuDatabase->menuAction());
        menuAbouy->addAction(actionRefresh);
        menuDatabase->addAction(actionConnection);
        menuDatabase->addAction(actionDisconnenct);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
#if QT_CONFIG(shortcut)
        actionRefresh->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLOAD->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        actionQuerry->setText(QCoreApplication::translate("MainWindow", "Query", nullptr));
        actionConnection->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
#if QT_CONFIG(shortcut)
        actionConnection->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDisconnenct->setText(QCoreApplication::translate("MainWindow", "Disconnenct", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Please load data first", nullptr));
        menuAbouy->setTitle(QCoreApplication::translate("MainWindow", "Home", nullptr));
        menuDatabase->setTitle(QCoreApplication::translate("MainWindow", "Database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
