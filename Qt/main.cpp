#include "mainwindow.h"
#include "main.h"
#include "./ui_mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <stdio.h>

QSqlDatabase dbRef = QSqlDatabase();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    dbRef = new QSqlDatabase();
    dbRef = QSqlDatabase::addDatabase("QMYSQL");



    w.show();
//        QMessageBox::information(NULL, "AAAAAAAAA", dbRef.driverName().toStdString());
    std::cout << "AAAAAAAA: \"" << dbRef.driverName().toStdString() << "\"\n";
    fflush(0);
    return a.exec();

}
