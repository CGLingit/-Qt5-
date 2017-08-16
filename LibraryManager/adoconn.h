#ifndef ADOCONN_H
#define ADOCONN_H
#include<QString>
class ADOConn
{
public:
    ADOConn();
    ~ADOConn();
    void OnInitADOConn(); //初始化--连接数据库
public:
    QString host;
    QString database;
    QString user;
    QString pwd;

};

#endif // ADOCONN_H
