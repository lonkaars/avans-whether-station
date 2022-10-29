#include "csv_import.h"

CSV_Import::CSV_Import()
{

}


#include <QString>
#include <QVector>

QString CSV_Import::csvToSql(QString input){

    QVector<QString> data;
    QString output = "(";

    data = input.split(",");

    for (int i = 1; i < data.size(); ++i) {

        bool valid;
        output.append(QString::number(data[i].toInt(&valid, 16)));

        if (i <= data[i].size()) {
            output.append(",");
        }

    }
    output.append(")");

    return output;
}
