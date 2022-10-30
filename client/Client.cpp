#include "Client.h"
#include "consts.h"


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
    if(_missingRecords>1){
        totalRecords = _missingRecords;
    }
    else{
        totalRecords=1;
    }
    QByteArray msgToSend= (msg.toUtf8() + totalRecords + offsetRecords +'\n');

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
