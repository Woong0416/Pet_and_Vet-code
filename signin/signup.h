#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_btn_save_clicked();

private:
    Ui::Signup *ui;
    QSqlDatabase mydb;

};

#endif // SIGNUP_H
