#pragma once

#include <QDialog>

#include <QMessageBox>
//#include <QtSql>
//#include <QSqlDatabase>


namespace Ui {
class SettingsMenu;
}

class SettingsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsMenu(QWidget *parent = nullptr);
    ~SettingsMenu();

private slots:

    void on_pushButton_cancel_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::SettingsMenu *ui;

    QString _dbName = "";
    QString _dbip = "";
    QString _ESPip = "";
};
