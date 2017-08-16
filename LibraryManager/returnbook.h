#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = 0);
    ~ReturnBook();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_2_editingFinished();

private:
    Ui::ReturnBook *ui;
    QSqlTableModel *model;
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlTableModel *model4;

public:
    QString BookCode;
    QString StuId;
};

#endif // RETURNBOOK_H
