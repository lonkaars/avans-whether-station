#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//    db = QSqlDatabase::addDatabase("QMYSQL");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    dbRef.close();
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::warning(this, "Oops..", "Task Failed succesfully ;)");
}


void MainWindow::on_pushButton_clicked()
{
//    dbRef = QSqlDatabase::addDatabase("QMYSQL");
//    dbRef.setHostName("localhost");
//    dbRef.setUserName("root");
//    dbRef.setPassword("Ab12345!");
//    dbRef.setDatabaseName("thecrapbox");

    if(dbRef.open()){
        QMessageBox::information(this, "Connection", "GREAT SUCCES!");
        pQueryModel = new QSqlQueryModel();
        pQueryModel->setQuery("SELECT * FROM opleiding;");
        ui->tableView->setModel(pQueryModel);
    } else {
        QMessageBox::warning(this, "No connection", "Failed to connect");
    }
}

void MainWindow::on_actionConnection_triggered()
{
    _dbConenctor = new dbConnector(this);
    _dbConenctor->show();
}

