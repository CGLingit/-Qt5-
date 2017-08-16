#include "bookinfo.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
BookInfo::BookInfo()
{
}

QString BookInfo::getInfo(QString str)
{
    QSqlQuery q;
    QString selectInfo = "select * from bookinfo where BookCode = '" + str + "'";
    if(!q.exec(selectInfo))
    {
        qDebug() << q.lastError();
    }
    else
    {
        while( q.next())
         {
             BookCode= q.value(0).toString();
             Name = q.value(1).toString();
             Author = q.value(2).toString();
             Publisher = q.value(3).toString();
             PublishYear = q.value(4).toString();
             BookCount = q.value(5).toString();
             RemainCount = q.value(6).toInt();

         }
    }
}
void BookInfo::SqlUpdate(QString BookCode1)
{
    QString Name1;
    QString Author1;
    QString Publisher1;
    QString PublishYear1;
    QString BookCount1;
    QString RemainCount1;

    QSqlQuery q;
    Name1 = Name;
    Author1 = Author;
    Publisher1 = Publisher;
    PublishYear1 = PublishYear;
    BookCount1 = BookCount;
    RemainCount1 = RemainCount;

    QString info = "update student set BookCode = '" + BookCode1 + "', Name = '" + Name1 + "', Publisher = '" + Publisher1 + "', PublishYear = '" + PublishYear1 + "', BookCount = '" + BookCount1 + "', RemainCount = '" + RemainCount1 + "', Author = '" + Author1 + "'where BookCode = " + BookCode1;

    q.exec(info);
}
