#pragma once

#include <QDialog>

#include <QMessageBox>
//#include <QtSql>
//#include <QSqlDatabase>

#include "database.h"

namespace Ui {
class dbConnector;
}

class dbConnector : public QDialog
{
    Q_OBJECT

public:
    explicit dbConnector(QWidget *parent = nullptr);
    ~dbConnector();

private slots:
//    void on_pushButton_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::dbConnector *ui;

//    Database database;
};
