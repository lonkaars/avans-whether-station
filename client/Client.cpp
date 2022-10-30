#include "Client.h"



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
    QTime time1 = QTime::currentTime();
    NextMinute = time1.minute()+1;

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
    qint16 currentMinute = time.minute();

    if(currentMinute==NextMinute){
        socket->connectToHost(networkAddress, tcpPortAddress);

        socket->write(msgToSend);
        NextMinute++;
    }
}

void Client::missingRecords()
{
    QSqlQuery queryTimeData;
    queryTimeData.exec("SELECT (unix_timestamp(now()) - unix_timestamp(`time`))/60 as delta FROM `WSdb`.`tblMain` limit 1");

    _missingRecords = queryTimeData.value(0).toInt();

}
