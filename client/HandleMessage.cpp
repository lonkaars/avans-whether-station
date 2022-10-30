#include "HandleMessage.h"

HandleMessage::HandleMessage(QObject *parent) : QObject(parent) { }

void HandleMessage::ParseToSQL(QString input) {
	QSqlQuery queryInsertData;
	QString output = "insert into WSdb.tblMain (temperature, humidity, pressure) values ";
	QStringList data;

	output.append("(");
	data=input.split(",");

	for (int i = 1; i < data.size(); i++) {
		bool valid;
		output.append(QString::number(data[i].toInt(&valid, 16)));
		if (i + 1 < data.size()) output.append(",");
	}

	output.append(")");

	queryInsertData.exec(output);
}



