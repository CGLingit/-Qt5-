#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>

namespace Ui {
class Manager;
}

class QSqlTableModel;
class Manager : public QDialog
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();

private slots:
    void on_pushButton_clicked();//查询

    void on_showAll_clicked();

    void on_Insert_clicked();

    void on_Delete_clicked();

    void on_submit_clicked();

    void on_borrowBook_clicked();

    void on_returnBook_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Manager *ui;
public:
    QSqlTableModel *model;
};

#endif // MANAGER_H
