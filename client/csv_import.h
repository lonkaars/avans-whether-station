#include <QString>
#pragma once


class CSV_Import
{
public:
    CSV_Import();

    virtual QString csvToSql(QString input);
};

