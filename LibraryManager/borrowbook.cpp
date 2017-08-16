#include "borrowbook.h"
#include "ui_borrowbook.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <student.h>
#include <bookinfo.h>
#include <borrowbookinfo.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDateTime>
BorrowBook::BorrowBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrowBook)
{
    ui->setupUi(this);
    QDateTime Time = QDateTime::currentDateTime();//获取系统现在的时间
    QString time = Time.toString("yyyy-MM-dd");
    ui->borrrowTime->setText(time);
}

BorrowBook::~BorrowBook()
{
    delete ui;
}
//确定按钮
void BorrowBook::on_pushButton_clicked()
{
    if(ui->bookIdLineEdit->text() == NULL || ui->stuId->text() == NULL)
    {
        QMessageBox::warning(this,tr("警告"),tr("请输入图书编号和学号"),QMessageBox::Yes);
    }
    else if(ui->bookIdLineEdit->text() == BookCode && ui->stuId->text() == StuId)
    {
        QString str = ui->stuId->text();
        QString str1 = ui->bookIdLineEdit->text();
        QString time = ui->borrrowTime->text();



//使用QSqlTableModel进行数据库操作
        /*对应图书库存减1*/
        model1 = new QSqlTableModel(this);
        model1->setTable("BookInfo");
        model1->setFilter("BookCode = '" + str1 +"'");
        model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model1->select();
        QSqlRecord record1 = model1->record(0);
        //书名
        QString BookName = record1.value(1).toString();
        int num1 = record1.value(6).toInt();//value(6)对应数据库的RemainCount
        if(num1  > 0 )
        {
            num1 = num1 - 1;
            record1.setValue("RemainCount",num1);
            model1->setRecord(0,record1);
            model1->submitAll();

            /* 对应的学生借书数目加1*/
            model = new QSqlTableModel(this);
            model->setTable("student");
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setFilter("StuId = '" + str + "'");//定位StuId = str 的学生
            model->select();
            //更新记录
            QSqlRecord record = model->record(0);//筛选后，只有一条记录，所以下标为0
            int num = record.value(4).toInt();
            num = num + 1;
            record.setValue("BorrowBookCount",num);
            model->setRecord(0,record);//修改第0行数据
            model->submitAll();//提交修改

            /*借书表增加一条借书记录*/
            model2 = new QSqlTableModel(this);
            model2->setTable("borrowbookinfo");
            model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model2->select();
            int rowNum = model2->rowCount();//获取当前表格的行数
            int id = 0;
            id = rowNum + 1;
            model2->insertRow(rowNum);
            qDebug() << rowNum;
            QSqlRecord record2 = model2->record();
            record2.setValue("id",id);
            record2.setValue("BookName",BookName);
            qDebug() << BookName;
            record2.setValue("BookCode",str1);
            record2.setValue("StuId",str);
            record2.setValue("BorrowDate",time);
    //      record2.setValue("ReturnDate",);
            model2->insertRecord(rowNum,record2);
            model2->submitAll();

            model4 = new QSqlTableModel(this);
            model4->setTable("borrowbookinfo");
            model4->setFilter("StuId = '" + str + "'");
            model4->select();
            ui->tableView->setColumnHidden(0,true);
            ui->tableView->setModel(model4);
        }
        else
        {
            QMessageBox::warning(this,tr("警告"),tr("该书库存为0"),QMessageBox::Yes);
        }
/*对象方式操作数据库，失败！！！！*/
//        QString id, name,sex;
//        int borrownum;
//        QSqlQuery q;
//        QString selectInfo = "select * from student where StuId = '" + str + "'";
//        if(!q.exec(selectInfo))
//        {
//            qDebug() << q.lastError();
//        }
//        else
//        {
//            while( q.next())
//             {
//                 id= q.value(0).toString();
//                 name = q.value(2).toString();
//                 sex = q.value(3).toString();
//                 borrownum = q.value(4).toInt();
//             }
//        }
//        Student stu(id,name,sex,borrownum);
//        stu.getInfo(str);
//        //qDebug() << stu.borrowBookCount;
//        stu.borrowBookCount=stu.borrowBookCount+1;
//        //qDebug() << stu.borrowBookCount;
//        stu.SqlUpdate(str);

//        BookInfo book;
//        book.getInfo(str1);
//        book.RemainCount=book.RemainCount-1;
//        book.SqlUpdate(str1);

//        BorrowBookInfo borrowBook;
//        borrowBook.bookCode= str1;
//        borrowBook.stuId = str;
//        borrowBook.SqlInsert();

//      this->close();
    }
}

void BorrowBook::on_bookIdLineEdit_textChanged(const QString &arg1)
{
    QSqlQuery q;
    QString selectInfo = "select * from bookinfo where BookCode = '" + arg1 + "'";
    if(!q.exec(selectInfo))
    {
        qDebug() << q.lastError();
    }
    else
    {
        while(q.next())
        {
            BookCode = q.value(0).toString();
        }
    }
}

void BorrowBook::on_stuId_textChanged(const QString &arg1)
{
    QSqlQuery q;
    QString selectInfo = "select * from student where StuId = '" + arg1 + "'";
    if(!q.exec(selectInfo))
    {
        qDebug() << q.lastError();
    }
    else
    {
        while(q.next())
        {
            StuId = q.value(0).toString();
        }
    }
}

void BorrowBook::on_stuId_editingFinished()
{
    model3 = new QSqlTableModel(this);;
    if(ui->stuId->text() == StuId)
    {
        model3->setTable("borrowbookinfo");
        model3->setFilter("StuId = '" + StuId + "'");
        model3->select();

        ui->tableView->setModel(model3);
        ui->tableView->setColumnHidden(0,true);
    }
}
