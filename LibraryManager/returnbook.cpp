#include "returnbook.h"
#include "ui_returnbook.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
ReturnBook::ReturnBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);

}

ReturnBook::~ReturnBook()
{
    delete ui;
}
//确定按钮
void ReturnBook::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == NULL || ui->lineEdit_2->text() == NULL)
    {
        QMessageBox::warning(this,tr("警告"),tr("请输入图书编号和学号"),QMessageBox::Yes);
    }
    else if(ui->lineEdit->text() == BookCode && ui->lineEdit_2->text() == StuId)
    {
        QString str = ui->lineEdit_2->text();
        QString str1 = ui->lineEdit->text();

        QSqlQuery q1;//先判断表中是否有对应的人和书
        QString selectInfo = "select * from borrowbookinfo where StuId = '" + str + "' and BookCode = '" + str1 + "'";
        if(!q1.exec(selectInfo))
        {
            QMessageBox::warning(this,tr("警告"),tr("查无此记录"),
                                 QMessageBox::Yes);
        }
        else
        {
    //使用QSqlTableModel进行数据库操作

            /* 对应的学生借书数目减1*/
            model = new QSqlTableModel(this);
            model->setTable("student");
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setFilter("StuId = '" + str + "'");//定位StuId = str 的学生
            model->select();
            //更新记录

            QSqlRecord record = model->record(0);//筛选后，只有一条记录，所以下标为0
            int num = record.value(4).toInt();
            if(num > 0)
            {
                num = num - 1;
                record.setValue("BorrowBookCount",num);
                model->setRecord(0,record);//修改第0行数据
                model->submitAll();//提交修改


                /*对应图书库存加1*/
                model1 = new QSqlTableModel(this);
                model1->setTable("BookInfo");
                model1->setFilter("BookCode = '" + str1 +"'");
                model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
                model1->select();
                QSqlRecord record1 = model1->record(0);
                int num1 = record1.value(6).toInt();
                num1 = num1 + 1;
                record1.setValue("RemainCount",num1);
                model1->setRecord(0,record1);
                model1->submitAll();

                /*借书表删掉一条借书记录*/
                model2 = new QSqlTableModel(this);
                model2->setTable("borrowbookinfo");
                model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
                model2->setFilter("StuId = '" + str + "'" + "and BookCode = '" + str1 + "'");
                model2->select();
                model2->removeRows(0,1);
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
                QMessageBox::warning(this,tr("警告"),tr("查无此记录"),
                                 QMessageBox::Yes);
            }
        }

    }
}

void ReturnBook::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQuery q;
    QString selectInfo = "select * from bookinfo where BookCode = '" + arg1 + "'";
    if(!q.exec(selectInfo))
    {
        qDebug() << q.lastError();
    }
    else {
        while(q.next()){
            BookCode = q.value(0).toString();
        }
    }

}

void ReturnBook::on_lineEdit_2_textChanged(const QString &arg1)
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


void ReturnBook::on_lineEdit_2_editingFinished()
{
    model3 = new QSqlTableModel(this);;
    if(ui->lineEdit_2->text() == StuId)
    {
        model3->setTable("borrowbookinfo");
        model3->setFilter("StuId = '" + StuId + "'");
        model3->select();

        ui->tableView->setModel(model3);
        ui->tableView->setColumnHidden(0,true);//隐藏第一列
    }
}
