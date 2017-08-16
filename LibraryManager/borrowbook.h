#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class BorrowBook;
}

class BorrowBook : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowBook(QWidget *parent = 0);
    ~BorrowBook();

private slots:
    void on_pushButton_clicked();

    void on_bookIdLineEdit_textChanged(const QString &arg1);

    void on_stuId_textChanged(const QString &arg1);

    void on_stuId_editingFinished();

private:
    Ui::BorrowBook *ui;
    QSqlTableModel *model;
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlTableModel *model4;


public:
    QString BookCode;
    QString StuId;
};

#endif // BORROWBOOK_H
