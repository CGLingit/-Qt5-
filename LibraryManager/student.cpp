#include "student.h"
#include "ui_student.h"
#include <QSqlQuery>
#include <login.h>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>

Student::Student(QString stuId, QString Name, QString Sex, int BOBOCO,QWidget *parent) :
    QDialog(parent),studentId(stuId),name(Name),sex(Sex),borrowBookCount(BOBOCO),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    showInfo();

    model = new QSqlTableModel(this);
    model->setTable("borrowbookinfo");
    model->setFilter(QString("StuId = '%1'").arg(studentId));

    model->select();
    //设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //model->removeColumn(),
    ui->BookTableView->setModel(model);
}

Student::~Student()
{
    delete ui;
}

void Student::getInfo(QString str)
{
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
             studentId= q.value(0).toString();
             name = q.value(2).toString();
             sex = q.value(3).toString();
             borrowBookCount = q.value(4).toInt();
         }
    }
}

void Student::showInfo()
{
    ui->label_4->setText(name);
    ui->label_5->setText(studentId);
    ui->label_7->setText(sex);
    QString bookstr = QString("%1").arg(borrowBookCount);
    ui->label_9->setText(bookstr);
}

void Student::SqlUpdate(QString studentId1)
{
    QString name1;
    QString sex1;
    int borrowBookCount1;

    QSqlQuery q;
    name1 = name;
    sex1 = sex;
    borrowBookCount1 = borrowBookCount;

    QString info = "update student set Name = '" + name1 + "', Sex = '" + sex1 + "', BorrowBookCount = '" + borrowBookCount1 + "'where StuId = " + studentId1;

    q.exec(info);
}

void Student::setInfo(QString studentId1, QString name1, QString sex1, int borrowBookCount1)
{
    studentId = studentId1;
    name = name1;
    sex = sex1;
    borrowBookCount = borrowBookCount1;
}
