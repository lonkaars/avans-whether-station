/********************************************************************************
** Form generated from reading UI file 'dbconnector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBCONNECTOR_H
#define UI_DBCONNECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dbConnector
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_adress;
    QLabel *label_4;
    QLineEdit *lineEdit_database;
    QFrame *line;
    QLabel *label;
    QLineEdit *lineEdit_username;
    QLabel *label_2;
    QLineEdit *lineEdit_password;
    QLabel *connectLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_login;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *dbConnector)
    {
        if (dbConnector->objectName().isEmpty())
            dbConnector->setObjectName(QString::fromUtf8("dbConnector"));
        dbConnector->resize(362, 273);
        formLayoutWidget = new QWidget(dbConnector);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(60, 60, 241, 173));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lineEdit_adress = new QLineEdit(formLayoutWidget);
        lineEdit_adress->setObjectName(QString::fromUtf8("lineEdit_adress"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_adress);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        lineEdit_database = new QLineEdit(formLayoutWidget);
        lineEdit_database->setObjectName(QString::fromUtf8("lineEdit_database"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_database);

        line = new QFrame(formLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::SpanningRole, line);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label);

        lineEdit_username = new QLineEdit(formLayoutWidget);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_username);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        lineEdit_password = new QLineEdit(formLayoutWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        QFont font;
        font.setUnderline(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        lineEdit_password->setFont(font);
        lineEdit_password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_password);

        connectLabel = new QLabel(formLayoutWidget);
        connectLabel->setObjectName(QString::fromUtf8("connectLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, connectLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_login = new QPushButton(formLayoutWidget);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));

        horizontalLayout->addWidget(pushButton_login);

        pushButton_cancel = new QPushButton(formLayoutWidget);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);


        formLayout->setLayout(5, QFormLayout::FieldRole, horizontalLayout);


        retranslateUi(dbConnector);

        QMetaObject::connectSlotsByName(dbConnector);
    } // setupUi

    void retranslateUi(QDialog *dbConnector)
    {
        dbConnector->setWindowTitle(QCoreApplication::translate("dbConnector", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("dbConnector", "Adress", nullptr));
        lineEdit_adress->setText(QCoreApplication::translate("dbConnector", "localhost", nullptr));
        lineEdit_adress->setPlaceholderText(QCoreApplication::translate("dbConnector", "Hostname/IP-Adress", nullptr));
        label_4->setText(QCoreApplication::translate("dbConnector", "Database", nullptr));
        lineEdit_database->setPlaceholderText(QCoreApplication::translate("dbConnector", "Database name", nullptr));
        label->setText(QCoreApplication::translate("dbConnector", "Username", nullptr));
        lineEdit_username->setText(QCoreApplication::translate("dbConnector", "root", nullptr));
        lineEdit_username->setPlaceholderText(QCoreApplication::translate("dbConnector", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("dbConnector", "Password", nullptr));
        lineEdit_password->setText(QString());
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("dbConnector", "Password", nullptr));
        connectLabel->setText(QCoreApplication::translate("dbConnector", "Connect", nullptr));
        pushButton_login->setText(QCoreApplication::translate("dbConnector", "Login", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("dbConnector", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dbConnector: public Ui_dbConnector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBCONNECTOR_H
