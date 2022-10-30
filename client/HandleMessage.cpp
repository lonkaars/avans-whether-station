#include "HandleMessage.h"

HandleMessage::HandleMessage(QObject *parent) : QObject(parent) { }

// void HandleMessage::ParseToSQL(QString input) {
// 	QSqlQuery queryInsertData;
// 	QString output = "insert into WSdb.tblMain (temperature, humidity, pressure) values ";
// 	QStringList data;
// 
// 	output.append("(");
// 	data=input.split(",");
// 
// 	for (int i = 1; i < data.size(); i++) {
// 		bool valid;
// 		output.append(QString::number(data[i].toInt(&valid, 16)));
// 		if (i + 1 < data.size()) output.append(",");
// 	}
// 
// 	output.append(")");
// }

void HandleMessage::ParseToSQL(QString input) {
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



