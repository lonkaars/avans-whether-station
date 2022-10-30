#ifndef HANDLEMESSAGE_H
#define HANDLEMESSAGE_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QVector>
#include <QSqlQuery>

class HandleMessage : public QObject
{
    Q_OBJECT
public:
    HandleMessage(QObject *parent = 0);

    QString ParseMessage(const QString  , int);
    void ParseToSQL(QString);

private:

};


#endif // HANDLEMESSAGE_H
