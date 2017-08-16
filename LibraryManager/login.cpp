#include "login.h"
#include "ui_login.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <student.h>
#include <manager.h>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_stuUserName_textChanged(const QString &name)
{
    QSqlQuery q;
    QString selectInfo = "select * from student where StuId = '" + name + "'";
    //qDebug() << selectInfo;
    if(!q.exec(selectInfo))
    {
        qDebug() << q.lastError();
    }
    else
    {
        while(q.next())
        {
            userName = q.value(0).toString();
            passWord = q.value(1).toString();
           // qDebug()<<QString("name=%1  password=%2").arg(userName).arg(passWord);
        }
    }

}

void Login::on_stuLogin_clicked()
{

    if(ui->stuUserName->text() == NULL && ui->stuPassWord->text() == NULL)
    {
        QMessageBox::warning(this,tr("警告"),tr("请输入用户名和密码"),QMessageBox::Yes);
    }
    else if(ui->stuUserName->text() == userName && ui->stuPassWord->text() == passWord)
    {
        QString str = ui->stuUserName->text();

        QString id, name,sex;
        int borrownum;
        QSqlQuery q;
        QString selectInfo = "select * from student where StuId = '" + str + "'";
        if(!q.exec(selectInfo))
        {
            qDebug() << q.lastError();
        }
        else
        {
            while( q.next())
             {
                 id= q.value(0).toString();
                 name = q.value(2).toString();
                 sex = q.value(3).toString();
                 borrownum = q.value(4).toInt();
             }
        }
        Student stu(id,name,sex,borrownum);
        //登录成功操作，实现页面跳转
       this->hide();//隐藏登录页面
        this->close();
       stu.show();
       stu.exec();
       this->show(); //关闭后显示登录页面
       ui->stuUserName->clear();
       ui->stuPassWord->clear();
    }
    else
    {
        //清空错误输入的内容
        QMessageBox::warning(this, tr("警告"), tr("用户名或密码错误"),QMessageBox::Yes);
        ui->stuUserName->clear();
        ui->stuPassWord->clear();
    }
}



void Login::on_managerName_textChanged(const QString &arg1)
{
    QSqlQuery q;
    QString selectInfo = "select * from manager where UserName = '" + arg1 + "'";
    qDebug() << selectInfo;
    if(!q.exec(selectInfo))
    {
        qDebug() << q.lastError();
    }
    else
    {
        while(q.next())
        {
            userName = q.value(0).toString();
            passWord = q.value(1).toString();
            qDebug()<<QString("name=%1  password=%2").arg(userName).arg(passWord);
        }
    }


}

void Login::on_managerLogin_clicked()
{
    Manager manager;
    if(ui->managerName->text() == NULL && ui->managerPassword->text() == NULL)
    {
        QMessageBox::warning(this,tr("警告"),tr("请输入用户名和密码"),QMessageBox::Yes);
    }
    else if(ui->managerName->text() == userName && ui->managerPassword->text() == passWord)
    {
        //登录成功操作，实现页面跳转
       this->hide();
       this->close();
       manager.show();
       manager.exec();
       this->show();
       ui->stuUserName->clear();
       ui->stuPassWord->clear();

    }
    else
    {
        //清空错误输入的内容
        QMessageBox::warning(this, tr("警告"), tr("用户名或密码错误"),QMessageBox::Yes);
        ui->managerName->clear();
        ui->managerPassword->clear();
    }
}


