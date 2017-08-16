#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
class Login;
namespace Ui {
class Student;
}
class QSqlTableModel;
class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(QString, QString, QString, int, QWidget *parent = 0);
    void getInfo(QString str);
    //QString getName();
    void SqlInsert();
    void SqlUpdate(QString);
    void showInfo();
    void SqlDelete(QString);
    void setInfo(QString, QString, QString, int);
    ~Student();
    Student();

private:
    Ui::Student *ui;
    QSqlTableModel *model;
public:
    QString studentId;
    QString name;
    QString sex;
    int borrowBookCount;
};

#endif // STUDENT_H
