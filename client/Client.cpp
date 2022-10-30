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

void Client::timeFunction()
{
    totalRecords = WS_MAX(1, _missingRecords);

    char* msg = NULL;
    asprintf(&msg, "last-records %x %x\n", totalRecords, offsetRecords);
    QByteArray msgToSend = msg;
    free(msg);

    QTime time = QTime::currentTime();
    qint16 currentSeconds = time.second();
    if((currentSeconds % WS_CLIENT_STATION_POLL_INTERVAL) == 1){

        socket->connectToHost(networkAddress, tcpPortAddress);
        socket->write(msgToSend);
    }
}

void Client::missingRecords()
{
    QSqlQuery queryTimeData;
    queryTimeData.exec("SELECT (unix_timestamp(now()) - unix_timestamp(`time`))/60 as delta FROM `WSdb`.`tblMain` limit 1");

    _missingRecords = queryTimeData.value(0).toInt();

}
