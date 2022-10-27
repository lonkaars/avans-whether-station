#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <stdio.h>

//#include "chart.h"
//#include "chartview.h"
#include "mainwindow.h"
#include "main.h"
#include "ui_mainwindow.h"
#include "mytcpsocket.h"
#include "timetest.h"

QSqlDatabase dbRef = QSqlDatabase();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TimeTest time;
	MyTcpSocket s;
	// s.doConnect();
    MainWindow w;

    dbRef = QSqlDatabase::addDatabase("QMYSQL");

	w.show();
	return a.exec();
}

/* QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

//![1]
	QLineSeries *series = new QLineSeries();
	for (int i = 0; i < 500; i++) {
		QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
		p.ry() += QRandomGenerator::global()->bounded(20);
		*series << p;
	}
//![1]

	Chart *chart = new Chart();
	chart->addSeries(series);
	chart->setTitle("Zoom in/out example");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->legend()->hide();
	chart->createDefaultAxes();

	ChartView *chartView = new ChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QMainWindow window;
	window.setCentralWidget(chartView);
	window.resize(400, 300);
	window.grabGesture(Qt::PanGesture);
	window.grabGesture(Qt::PinchGesture);
	window.show();

	return a.exec();
} */
