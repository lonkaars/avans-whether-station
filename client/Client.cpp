#include <stdio.h>

#include "Client.h"
#include "consts.h"
#include "../shared/util.h"


Client::Client(QObject *parent) : QObject(parent)
{
    // initislise timer and socket
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
}
Client::~Client()
{
    // delete if called again
    delete socket;
    delete timer;
}

void Client::ClientEcho()
{

    connect(timer, SIGNAL(timeout()),this,SLOT(timeFunction())); // connect timer to time every minute

    // connect to readyread to receive data;
    connect(socket,&QTcpSocket::readyRead, [&]() {
        QTextStream T(socket);
        QString text = T.readAll(); //  reads all data
       Handlemsg.ParseToSQL(Handlemsg.ParseMessage(text, (totalRecords-'0')));


    });

    timer->start(1000);
}

void Client::timeFunction() {
	if((QTime::currentTime().second() % WS_CLIENT_STATION_POLL_INTERVAL) != 0) return;

	this->missingRecords();
	totalRecords = WS_MAX(1, _missingRecords);

	char* msg = NULL;
	asprintf(&msg, "last-records %x %x\n", totalRecords, offsetRecords);
	QByteArray msgToSend = msg;
	free(msg);

	socket->connectToHost(networkAddress, tcpPortAddress);
	socket->write(msgToSend);
}

void Client::missingRecords() {
	QSqlQuery queryTimeData;
	queryTimeData.exec("select unix_timestamp(now()) - unix_timestamp(time) as delta from WSdb.tblMain order by time desc limit 1");
	queryTimeData.first();
	unsigned int secondsSinceLastRecord = queryTimeData.value(0).toInt();
	_missingRecords = secondsSinceLastRecord / WS_CLIENT_STATION_POLL_INTERVAL;
}

