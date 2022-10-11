#include "timetest.h"

TimeTest::TimeTest(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start(5000);
}

qint16 TimeTest::myfunction()
{
    QTime time = QTime::currentTime();
   qint16 time_text = time.minute();

   return time_text;


}
