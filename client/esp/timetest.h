#ifndef TIMETEST_H
#define TIMETEST_H
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QDateTime>

class TimeTest : public QObject
{
    Q_OBJECT
public:
    explicit TimeTest(QObject *parent = 0);

signals:
public slots:
    qint16 myfunction();

private:
    QTimer *timer;




};


#endif // TIMETEST_H
