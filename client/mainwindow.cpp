#include <QSqlDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"

//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    dbRef.close();
    delete ui;
}

void MainWindow::on_actionConnection_triggered()
{
    _dbConenctor = new dbConnector(this);
    _dbConenctor->show();
}


void MainWindow::on_actionRefresh_triggered()
{
    QLineSeries *seriesTemperature = new QLineSeries();
    QLineSeries *seriesHumidity = new QLineSeries();
    _pChart = new QChart();

    if(dbRef.open()){
        QSqlQuery queryGraphData;
        queryGraphData.exec("select `tblMain`.`ID`, `temperature`, `humidity`, `pressure` FROM `tblMain` ORDER BY `tblMain`.`ID` DESC limit 16;");
//        queryGraphData.exec("select `tblMain`.`ID`, `temperature`, `humidity`, `pressure` FROM `tblMain`;");

        for (int i = 0; queryGraphData.next(); ++i) {
//            seriesTemp->append(queryGraphData.value(0).toInt(), queryGraphData.value(1).toInt());
            seriesTemperature->append(i, queryGraphData.value(1).toFloat());
            seriesHumidity->append(i, queryGraphData.value(2).toFloat()*100);
        }

        _pChart->legend()->show();
        _pChart->addSeries(seriesTemperature);
        _pChart->addSeries(seriesHumidity);
        _pChart->createDefaultAxes();
        _pChart->setTitle("Weather data:");
        _pChartView = new QChartView(_pChart);

        MainWindow::setCentralWidget(_pChartView);


    } else {
        QMessageBox::warning(this, "No connection", "Failed to connect");
    }
//    delete seriesTemperature;
//    delete seriesHumidity;
}

