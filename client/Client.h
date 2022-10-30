#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QTextStream>
#include <QTimer>
#include <QDateTime>
#include <QSqlQuery>

#include "HandleMessage.h"

// class client for wheather station
class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent = 0);
    virtual ~Client();

public slots:
    void ClientEcho(); // function to ask data from wheather station
    void timeFunction();  // function to look every second what time currently is en handle if minute is passed

private:
    void missingRecords();

    int _missingRecords;
    QTcpSocket *socket; // tcpsocket for communicating
    QTimer      *timer; // timer to read every second what time it curruntly is.

    // qint16 currentMinute; // timing for currentMinute
    HandleMessage Handlemsg; // add HandleMessage to Client.h

    int tcpPortAddress = 80; // port of communication via tcp
    QString networkAddress = "192.168.137.76"; // network address for commincation via tcp

    QString msg = "last-records "; // part of mesage to send to wheather staion
    char totalRecords = '1';  // total records to ask wheather station
    char offsetRecords = '0'; // offset from reqeusting records



};

#endif // CLIENT_H
