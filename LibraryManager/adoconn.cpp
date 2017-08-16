#include "adoconn.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
ADOConn::ADOConn()
{
    host = "127.0.0.1";
    database = "library";
    user = "root";
    pwd = "";
}

ADOConn::~ADOConn()
{
}

void ADOConn::OnInitADOConn()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(database);
    db.open(user, pwd);
    //qDebug() << "success";
}
