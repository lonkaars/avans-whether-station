#include <QSqlDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"
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

    series = new QLineSeries();
    QChart *chart = new QChart();

    if(dbRef.open()){
        QMessageBox::information(this, "Connection", "GREAT SUCCES!");
        QSqlQuery queryGraphData;
        queryGraphData.exec("SELECT id, temp FROM tblMain LIMIT 16 ORDER BY desc;");
//        ui->tableView->setModel(pQueryModel);
        for (int i = 0; queryGraphData.next(); ++i) {
            series->append(queryGraphData.value(0).toInt(), queryGraphData.value(1).toInt());
        }
        chart->legend()->show();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Hellow!");
        chartView = new QChartView(chart);

        MainWindow::setCentralWidget(chartView);

    } else {
        QMessageBox::warning(this, "No connection", "Failed to connect");
    }
}

void MainWindow::on_actionConnection_triggered()
{
    _dbConenctor = new dbConnector(this);
    _dbConenctor->show();
}

