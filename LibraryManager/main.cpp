#include "mainwindow.h"
#include <QApplication>
#include <adoconn.h>
#include <login.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ADOConn b;
    b.OnInitADOConn();


    Login login;
    login.show();

    return a.exec();
}
