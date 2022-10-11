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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionRefresh;
    QAction *actionLOAD;
    QAction *actionQuerry;
    QAction *actionConnection;
    QAction *actionDisconnenct;
    QAction *actionQuerry_2;
    QAction *actionStatus;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QMenuBar *menubar;
    QMenu *menuAbouy;
    QMenu *menuTEMP;
    QMenu *menuDatabase;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
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
        actionQuerry_2 = new QAction(MainWindow);
        actionQuerry_2->setObjectName(QString::fromUtf8("actionQuerry_2"));
        actionStatus = new QAction(MainWindow);
        actionStatus->setObjectName(QString::fromUtf8("actionStatus"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);
        pushButton->setGeometry(QRect(310, 0, 121, 41));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-10, 40, 801, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuAbouy = new QMenu(menubar);
        menuAbouy->setObjectName(QString::fromUtf8("menuAbouy"));
        menuTEMP = new QMenu(menubar);
        menuTEMP->setObjectName(QString::fromUtf8("menuTEMP"));
        menuDatabase = new QMenu(menubar);
        menuDatabase->setObjectName(QString::fromUtf8("menuDatabase"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuAbouy->menuAction());
        menubar->addAction(menuTEMP->menuAction());
        menubar->addAction(menuDatabase->menuAction());
        menuAbouy->addAction(actionAbout);
        menuAbouy->addAction(actionRefresh);
        menuTEMP->addAction(actionLOAD);
        menuTEMP->addAction(actionQuerry);
        menuDatabase->addAction(actionConnection);
        menuDatabase->addAction(actionDisconnenct);
        menuDatabase->addAction(actionStatus);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        actionLOAD->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        actionQuerry->setText(QCoreApplication::translate("MainWindow", "Query", nullptr));
        actionConnection->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnenct->setText(QCoreApplication::translate("MainWindow", "Disconnenct", nullptr));
        actionQuerry_2->setText(QCoreApplication::translate("MainWindow", "Querry", nullptr));
        actionStatus->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "DoesSomething", nullptr));
        menuAbouy->setTitle(QCoreApplication::translate("MainWindow", "Home", nullptr));
        menuTEMP->setTitle(QCoreApplication::translate("MainWindow", "TEMP", nullptr));
        menuDatabase->setTitle(QCoreApplication::translate("MainWindow", "Database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
