#include "settingsmenu.h"
//#include "ui_SettingsMenu.h"
#include "main.h"

#include "mainwindow.h"

SettingsMenu::SettingsMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsMenu)
{
    _dbip = "localhost";
    ui->setupUi(this);
}

SettingsMenu::~SettingsMenu()
{
    delete ui;
}

void SettingsMenu::on_pushButton_cancel_clicked()
{
    SettingsMenu::~SettingsMenu();
}

void SettingsMenu::on_pushButton_login_clicked()
{
    _dbip = ui->lineEdit_adress->text();
    _dbName = ui->lineEdit_database->text();
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    dbRef.setHostName(_dbip);
    dbRef.setUserName(username);
    dbRef.setPassword(password);
    dbRef.setDatabaseName(_dbName);

    if(dbRef.open()){
        QMessageBox::information(this, "Connection", "GREAT SUCCES!");
        SettingsMenu::~SettingsMenu();
    } else {
        QMessageBox::warning(this, "No connection", "Failed to connect");
    }
}




