#include "HandleMessage.h"

HandleMessage::HandleMessage(QObject *parent) : QObject(parent)
{

}

QString HandleMessage::ParseMessage(const QString Msg , int totalRecords )
{
    QString message= Msg.section('\n',2,(3+totalRecords));

    return message;

}

void HandleMessage::ParseToSQL(QString input)
{
    QSqlQuery queryInsertData;
    QString output = "INSERT INTO `tblMain` (`temperature`, `humidity`, `pressure`) VALUES ";
    QStringList data;
    QStringList list = input.split("\n");
    for (int i = 0; i < list.size(); ++i) {

        output += "(";

        data=list[i].split(",");

        for (int j = 1; j < data.size(); ++j) {
            bool valid;
            output.append(QString::number(data[j].toInt(&valid, 16)));
            if (j <= data[j].size()) {
                output.append(",");
            }

        }
        output.append(")");

        if (i+1 < list.size()){
            output.append(",");
        }
    }
   queryInsertData.exec(output);
}



