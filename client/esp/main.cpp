#include <QCoreApplication>
#include "mytcpsocket.h"
#include "timetest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//   qint16 startTime= 46;
TimeTest time;


//while(1){

//
//    qint16  minuut = time.myfunction();

//    if(minuut == startTime)
//    {
//        qDebug() << "Tijd: " << minuut;
//        startTime+=1;

//    }
//}
MyTcpSocket s;
s.doConnect();


   return a.exec();
}
