#include "manager.h"
#include "ui_manager.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <returnbook.h>
#include <borrowbook.h>

Manager::Manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("bookInfo");
    model->select();

    //设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}

Manager::~Manager()
{
    delete ui;
}

//查询
void Manager::on_pushButton_clicked()
{
    QString name = ui->selectLineEdit->text();

    //根据姓名进行筛选，一定要使用单引号
    model->setFilter(QString("name = '%1'").arg(name));
    model->select();
}

//显示全部
void Manager::on_showAll_clicked()
{
    model->setTable("bookInfo");
    model->select();
}

//插入
void Manager::on_Insert_clicked()
{
    int rowNum = model->rowCount();
    int BookCode = 1;
    BookCode += rowNum;

    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0), BookCode);

}

//删除
void Manager::on_Delete_clicked()
{
    //获取选中的行数  注：currentIndex().row()为界面用户选中的行
    int curRow = ui->tableView->currentIndex().row();

    //删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this, tr("删除当前行！"),
                                  tr("确定？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        //如果不删除，则回滚
        model->revertAll();
    }
    else
    {
        //否则提交删除操作
        model->submitAll();
    }

}

//提交修改
void Manager::on_submit_clicked()
{
    //开始事务操作
    model->database().transaction();
    if(model->submitAll())
    {
        if(model->database().commit())
        {
            QMessageBox::information(this, tr("tabelModel"),
                                    tr("修改成功！"));
        }
        else
        {
            model->database().rollback();//回滚
            QMessageBox::warning(this, tr("tableModel"),
                                 tr("数据库错误：%1").arg(model->lastError().text()),
                                 QMessageBox::Ok);
        }
    }
}

void Manager::on_borrowBook_clicked()
{
    BorrowBook book;
    this->show();
    book.show();
    book.exec();
}

void Manager::on_returnBook_clicked()
{
    ReturnBook rBook;
    this->show();
    rBook.show();
    rBook.exec();
}

void Manager::on_pushButton_2_clicked()
{
    model->setTable("borrowbookinfo");
    model->select();
    ui->tableView->setColumnHidden(0,true);
}
