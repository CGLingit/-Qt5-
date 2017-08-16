#ifndef BOOKINFO_H
#define BOOKINFO_H
#include <QString>
class BookInfo
{
public:
    BookInfo();
    QString getInfo(QString);
    void SqlUpdate(QString);
    QString SqlInsert();
public:
    QString BookCode;
    QString Name;
    QString Author;
    QString Publisher;
    QString PublishYear;
    QString BookCount;
    int RemainCount;

};

#endif // BOOKINFO_H
