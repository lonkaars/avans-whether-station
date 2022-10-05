#include "dbconnector.h"
#include "ui_dbconnector.h"
#include "main.h"

//#include "mainwindow.h"

dbConnector::dbConnector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dbConnector)
{
    ui->setupUi(this);
}

dbConnector::~dbConnector()
{
    delete ui;
}

void dbConnector::on_pushButton_cancel_clicked()
{
    dbConnector::~dbConnector();
}

void dbConnector::on_pushButton_login_clicked()
{
    QString hostname = ui->lineEdit_adress->text();
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString databaseName = "thecrapbox";

//    QSqlDatabase db = MainWindow.loginDb(adress, username, password);

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    return;
    dbRef.setHostName(hostname);
    dbRef.setUserName(username);
    dbRef.setPassword(password);
    dbRef.setDatabaseName("thecrapbox");

    if(dbRef.open()){
        QMessageBox::information(this, "Connection", "GREAT SUCCES!");
    } else {
        QMessageBox::warning(this, "No connection", "Failed to connect");
    }
}




