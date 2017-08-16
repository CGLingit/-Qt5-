#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_stuLogin_clicked();

    void on_stuUserName_textChanged(const QString &name);

    void on_managerName_textChanged(const QString &arg1);

    void on_managerLogin_clicked();

    QString getuserName(){return userName;}

private:
    Ui::Login *ui;
public:
    QString userName;
    QString passWord;
};
#endif // LOGIN_H
